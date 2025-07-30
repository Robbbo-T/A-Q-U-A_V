// Jenkins Pipeline for AQUA V. QNS

pipeline {
    agent {
        dockerfile {
            filename 'build/ci/QUA-QNS01-25SVD0001-DES-BOB-TEC-TD-QCSAA-914-000-00-01-TPL-DOCKER-001-QSTR-v1.0.0.dockerfile'
        }
    }
    
    environment {
        BUILD_DIR = 'build'
        QUANTUM_VALIDATION = 'true'
    }
    
    stages {
        stage('Checkout') {
            steps {
                checkout scm
                sh 'git submodule update --init --recursive'
            }
        }
        
        stage('Configure') {
            steps {
                sh """
                    mkdir -p ${BUILD_DIR}
                    cd ${BUILD_DIR}
                    cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja
                """
            }
        }
        
        stage('Build') {
            steps {
                sh "cd ${BUILD_DIR} && ninja -j${env.PARALLEL_JOBS ?: '8'}"
            }
        }
        
        stage('Test') {
            parallel {
                stage('Unit Tests') {
                    steps {
                        sh "cd ${BUILD_DIR} && ./tests/unit_tests"
                    }
                }
                stage('Integration Tests') {
                    steps {
                        sh "cd ${BUILD_DIR} && ./tests/integration_tests"
                    }
                }
                stage('Performance Tests') {
                    steps {
                        sh "cd ${BUILD_DIR} && ./tests/performance_tests"
                    }
                }
            }
        }
        
        stage('Quantum Validation') {
            when {
                expression { env.QUANTUM_VALIDATION == 'true' }
            }
            steps {
                sh "cd ${BUILD_DIR} && ./tools/quantum_validator"
            }
        }
        
        stage('Code Analysis') {
            parallel {
                stage('Static Analysis') {
                    steps {
                        sh 'cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck.xml'
                    }
                }
                stage('Code Coverage') {
                    steps {
                        sh """
                            cd ${BUILD_DIR}
                            cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
                            make coverage
                        """
                    }
                }
            }
        }
        
        stage('Package') {
            steps {
                sh "cd ${BUILD_DIR} && cpack -G DEB"
                archiveArtifacts artifacts: "${BUILD_DIR}/*.deb", fingerprint: true
            }
        }
    }
    
    post {
        always {
            junit "${BUILD_DIR}/**/test_results.xml"
            publishHTML([
                allowMissing: false,
                alwaysLinkToLastBuild: true,
                keepAll: true,
                reportDir: "${BUILD_DIR}/coverage",
                reportFiles: 'index.html',
                reportName: 'Code Coverage Report'
            ])
        }
        success {
            echo 'AQUA V. QNS Build Successful!'
        }
        failure {
            echo 'Build Failed - Check logs'
        }
    }
}
