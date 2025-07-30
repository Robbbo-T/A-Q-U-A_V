// Quantum Software Jenkins Pipeline
// Version: 1.0.0
// ATA-Chapter: CYB-812 (Cybersecurity & DevOps)

@Library('quantum-shared-library') _

pipeline {
    agent {
        dockerfile {
            filename 'build/ci/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-02-TPL-CI-002-QDAT-v1.0.0.dockerfile'
            dir '.'
            label 'quantum-build-node'
            args '-v /var/run/docker.sock:/var/run/docker.sock'
        }
    }
    
    options {
        timestamps()
        timeout(time: 2, unit: 'HOURS')
        buildDiscarder(logRotator(numToKeepStr: '30', artifactNumToKeepStr: '10'))
        disableConcurrentBuilds()
        skipDefaultCheckout()
    }
    
    parameters {
        choice(
            name: 'BUILD_TYPE',
            choices: ['Release', 'Debug', 'RelWithDebInfo'],
            description: 'CMake build type'
        )
        booleanParam(
            name: 'RUN_PERFORMANCE_TESTS',
            defaultValue: false,
            description: 'Run performance tests (time-consuming)'
        )
        booleanParam(
            name: 'DEPLOY_TO_STAGING',
            defaultValue: false,
            description: 'Deploy to staging environment after successful build'
        )
    }
    
    environment {
        // Build environment variables
        BUILD_TYPE = "${params.BUILD_TYPE}"
        QUANTUM_SDK_VERSION = '2.0.0'
        CMAKE_BUILD_PARALLEL_LEVEL = "${sh(script: 'nproc', returnStdout: true).trim()}"
        
        // Artifact paths
        BUILD_DIR = 'build'
        ARTIFACTS_DIR = 'artifacts'
        
        // Version information
        VERSION = "${sh(script: 'git describe --tags --always', returnStdout: true).trim()}"
        COMMIT_SHA = "${sh(script: 'git rev-parse --short HEAD', returnStdout: true).trim()}"
        
        // Credentials
        ARTIFACTORY_CREDS = credentials('artifactory-quantum')
        SONAR_TOKEN = credentials('sonarqube-quantum-token')
    }
    
    stages {
        stage('Checkout') {
            steps {
                cleanWs()
                checkout scm
                script {
                    env.GIT_BRANCH = sh(script: 'git rev-parse --abbrev-ref HEAD', returnStdout: true).trim()
                    env.GIT_COMMIT_MSG = sh(script: 'git log -1 --pretty=%B', returnStdout: true).trim()
                }
            }
        }
        
        stage('Environment Setup') {
            steps {
                sh '''
                    echo "Setting up build environment..."
                    mkdir -p ${BUILD_DIR} ${ARTIFACTS_DIR}
                    
                    # Display environment info
                    echo "Build Type: ${BUILD_TYPE}"
                    echo "Version: ${VERSION}"
                    echo "Commit: ${COMMIT_SHA}"
                    echo "Branch: ${GIT_BRANCH}"
                    
                    # Check tools
                    cmake --version
                    ${CC} --version
                    ${CXX} --version
                '''
            }
        }
        
        stage('Configure') {
            steps {
                dir("${BUILD_DIR}") {
                    sh '''
                        cmake .. \
                            -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
                            -DQUANTUM_SDK_VERSION=${QUANTUM_SDK_VERSION} \
                            -DBUILD_SHARED_LIBS=ON \
                            -DENABLE_TESTING=ON \
                            -DENABLE_COVERAGE=ON \
                            -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
                    '''
                }
            }
        }
        
        stage('Build') {
            steps {
                dir("${BUILD_DIR}") {
                    sh 'cmake --build . --config ${BUILD_TYPE} --target all'
                }
            }
            post {
                success {
                    archiveArtifacts artifacts: "${BUILD_DIR}/bin/*, ${BUILD_DIR}/lib/*", fingerprint: true
                }
            }
        }
        
        stage('Static Analysis') {
            parallel {
                stage('Clang-Tidy') {
                    steps {
                        sh '''
                            find src -name '*.cpp' -o -name '*.h' | \
                            xargs clang-tidy -p ${BUILD_DIR} --config-file=.clang-tidy || true
                        '''
                    }
                }
                stage('CppCheck') {
                    steps {
                        sh '''
                            cppcheck --enable=all --suppress=missingInclude \
                                --xml --xml-version=2 \
                                -I include src/ 2> cppcheck-report.xml || true
                        '''
                        recordIssues(
                            enabledForFailure: true,
                            tool: cppCheck(pattern: 'cppcheck-report.xml')
                        )
                    }
                }
                stage('SonarQube') {
                    steps {
                        withSonarQubeEnv('SonarQube-Quantum') {
                            sh '''
                                sonar-scanner \
                                    -Dsonar.projectKey=quantum-software \
                                    -Dsonar.sources=src \
                                    -Dsonar.tests=tests \
                                    -Dsonar.cfamily.build-wrapper-output=${BUILD_DIR} \
                                    -Dsonar.cfamily.gcov.reportsPath=${BUILD_DIR}
                            '''
                        }
                    }
                }
            }
        }
        
        stage('Unit Tests') {
            steps {
                dir("${BUILD_DIR}") {
                    sh '''
                        ctest -C ${BUILD_TYPE} --label-regex "unit" \
                            --output-on-failure --no-compress-output -T Test
                    '''
                }
            }
            post {
                always {
                    junit "${BUILD_DIR}/Testing/**/*.xml"
                    publishCoverage adapters: [
                        coberturaAdapter("${BUILD_DIR}/coverage.xml")
                    ], sourceFileResolver: sourceFiles('STORE_LAST_BUILD')
                }
            }
        }
        
        stage('Integration Tests') {
            steps {
                dir("${BUILD_DIR}") {
                    sh '''
                        # Setup integration test environment
                        ../tools/scripts/setup-test-env.sh integration
                        
                        # Run integration tests
                        ctest -C ${BUILD_TYPE} --label-regex "integration" \
                            --output-on-failure --timeout 300
                    '''
                }
            }
        }
        
        stage('Performance Tests') {
            when {
                expression { params.RUN_PERFORMANCE_TESTS == true }
            }
            steps {
                dir("${BUILD_DIR}") {
                    sh '''
                        ctest -C ${BUILD_TYPE} --label-regex "performance" \
                            --output-on-failure --verbose
                        
                        # Analyze results
                        python3 ../tools/scripts/analyze-performance.py \
                            --input Testing/Performance \
                            --output ${WORKSPACE}/${ARTIFACTS_DIR}/performance-report.json
                    '''
                }
            }
            post {
                success {
                    archiveArtifacts artifacts: "${ARTIFACTS_DIR}/performance-report.json"
                }
            }
        }
        
        stage('Documentation') {
            steps {
                sh '''
                    # Generate API documentation
                    doxygen Doxyfile
                    
                    # Build documentation site
                    mkdocs build --strict
                    
                    # Validate documentation
                    python3 tools/scripts/validate-docs.py --path site/
                '''
            }
            post {
                success {
                    publishHTML([
                        allowMissing: false,
                        alwaysLinkToLastBuild: true,
                        keepAll: true,
                        reportDir: 'site',
                        reportFiles: 'index.html',
                        reportName: 'Documentation',
                        reportTitles: 'Quantum Software Documentation'
                    ])
                }
            }
        }
        
        stage('Package') {
            steps {
                sh '''
                    # Create release package
                    mkdir -p ${ARTIFACTS_DIR}/release/{bin,lib,config,docs}
                    
                    cp -r ${BUILD_DIR}/bin/* ${ARTIFACTS_DIR}/release/bin/
                    cp -r ${BUILD_DIR}/lib/* ${ARTIFACTS_DIR}/release/lib/
                    cp -r tools/config/* ${ARTIFACTS_DIR}/release/config/
                    cp -r site/* ${ARTIFACTS_DIR}/release/docs/
                    cp QUA-QNS01-25SVD0001-DES-BOB-S&L-TD-ATA-000-00-02-TPL-LIC-001-S&L-v1.0.0.txt ${ARTIFACTS_DIR}/release/LICENSE
                    
                    # Create tarball
                    cd ${ARTIFACTS_DIR}
                    tar -czf quantum-software-${VERSION}.tar.gz release/
                    
                    # Create Docker image
                    cd ${WORKSPACE}
                    docker build -f build/ci/QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-02-TPL-CI-002-QDAT-v1.0.0.dockerfile \
                        -t quantum-software:${VERSION} \
                        -t quantum-software:latest .
                '''
            }
            post {
                success {
                    archiveArtifacts artifacts: "${ARTIFACTS_DIR}/*.tar.gz", fingerprint: true
                }
            }
        }
        
        stage('Deploy to Staging') {
            when {
                allOf {
                    expression { params.DEPLOY_TO_STAGING == true }
                    branch 'develop'
                }
            }
            steps {
                script {
                    input message: 'Deploy to staging?', ok: 'Deploy'
                }
                sh '''
                    ./tools/scripts/deploy.sh staging ${VERSION}
                    ./tools/scripts/smoke-test.sh staging
                '''
            }
        }
        
        stage('Quality Gate') {
            steps {
                timeout(time: 10, unit: 'MINUTES') {
                    waitForQualityGate abortPipeline: true
                }
            }
        }
    }
    
    post {
        always {
            // Clean up
            sh '''
                # Clean up temporary files
                find . -name "*.gcda" -delete
                find . -name "*.gcno" -delete
            '''
            
            // Send notifications
            script {
                def status = currentBuild.result ?: 'SUCCESS'
                def color = status == 'SUCCESS' ? 'good' : 'danger'
                def message = """
                    Build ${env.BUILD_NUMBER} - ${status}
                    Branch: ${env.GIT_BRANCH}
                    Commit: ${env.COMMIT_SHA}
                    Version: ${env.VERSION}
                """
                
                // Send Slack notification (if configured)
                // slackSend(channel: '#quantum-builds', color: color, message: message)
            }
        }
        success {
            echo 'Pipeline completed successfully!'
        }
        failure {
            echo 'Pipeline failed!'
            // Additional failure handling
        }
        cleanup {
            cleanWs()
        }
    }
}
