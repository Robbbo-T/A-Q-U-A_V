// AQUA V. Quantum Navigation System - Jenkins CI/CD Pipeline
// Document: QUA-QNS01-25SVD0001-DES-BOB-CDG-TD-CYB-812-00-03-TPL-CI-003-QDAT-v1.0.1.groovy
// Owner: QDAT (Data Governance Division)
// Site: Silicon Valley (25SVD)
// =============================================================================
// Copyright (C) 2025 GAIA AIR - ROBBBO-T
// Aerospace and Quantum United Advanced Venture (AQUA V.)
// =============================================================================
// Jenkins Pipeline for QNS TRL 6 Flight Testing
// Version 1.1.0 - Enhanced with change detection, optimization,
//                pre-commit, Conan, Artifactory, Ephemeral Env, Canary Deploy,
//                Quantum Telemetry, and Resource Management
// =============================================================================

// Import required libraries and classes
@Library('aqua-v-shared-library@v1.1.0') _

// Pipeline definition
pipeline {
  // Agent configuration - use the AQUA V. QNS Docker image with pinned digest
  agent {
    docker {
      // SECURITY: Pinned to specific SHA256 digest for immutable base image
      image 'registry.aqua-v.aerospace/qns/build-env@sha256:9a0bdde4188b896a372804be2384015e90e3f84906b750c1a53539b585fbbe7f'
      label 'quantum-capable'
      args '''
        -v /var/run/docker.sock:/var/run/docker.sock
        -v ${WORKSPACE}:/workspace
        -v ${HOME}/.ccache:/cache/ccache
        --cap-add SYS_PTRACE
        --security-opt seccomp=unconfined
        --memory=32g
        --cpus=8
      '''
    }
  }
   
  // Environment variables
  environment {
    // AQUA V. Program constants
    AQUA_V_PROGRAM = 'Aerospace and Quantum United Advanced Venture'
    AQUA_V_INVESTMENT = '40B EUR'
    QNS_TRL = '6'
    QNS_STATUS = 'Flight Testing'
    SITE_CODE = '25SVD'
    SITE_NAME = 'Silicon Valley'
     
    // QNS Technical specifications
    QNS_UPDATE_RATE_HZ = '1000'
    QNS_GRAVITOMETER_SENSITIVITY = '1e-12'
    QNS_MAGNETOMETER_RANGE = '1e-9'
    QNS_POSITION_ACCURACY = '0.1'
     
    // Build configuration
    BUILD_DIR = 'build'
    CMAKE_BUILD_TYPE = "${params.BUILD_TYPE ?: 'Release'}"
    CMAKE_GENERATOR = 'Ninja'
    PARALLEL_JOBS = '8'
     
    // Quantum configuration
    QUANTUM_SDK_ROOT = '/opt/aqua-v/quantum-sdk'
    QUANTUM_HARDWARE = "${params.QUANTUM_MODE ?: 'simulator'}"
    ENABLE_ALI_BOB_SYNC = 'ON'
     
    // Security scanning
    SECURITY_SCAN_LEVEL = 'critical'
    QUANTUM_ENCRYPTION = 'enabled'
     
    // Artifact configuration
    ARTIFACT_RETENTION_DAYS = '7'
     
    // Resource constraints
    JAVA_OPTS = '-Xmx4g'
    NODE_OPTIONS = '--max-old-space-size=4096'
     
    // Credentials
    GITLAB_CREDS = credentials('gitlab-api-token')
    DOCKER_REGISTRY_CREDS = credentials('docker-registry') // Renamed for clarity with docker.withRegistry
    ANSIBLE_VAULT_PASS_FILE = credentials('ansible-vault-password') // Renamed for clarity with withCredentials
    SLACK_WEBHOOK = credentials('slack-webhook-url')

    // Added for ephemeral test env and canary
    TEST_ENV_ENDPOINT = ''
    QUANTUM_RESOURCE_ID = '' // To store the provisioned quantum resource ID
    QUANTUM_ENDPOINT = ''    // To store the endpoint of the provisioned quantum resource
    PROMETHEUS_ENDPOINT = 'http://prometheus.aqua-v.aerospace/api/v1' // Example Prometheus endpoint
  }
   
  // Build parameters
  parameters {
    choice(
      name: 'BUILD_TYPE',
      choices: ['Release', 'Debug', 'RelWithDebInfo'],
      description: 'CMake build type'
    )
    choice(
      name: 'QUANTUM_MODE',
      choices: ['simulator', 'hardware'],
      description: 'Quantum execution mode'
    )
    booleanParam(
      name: 'RUN_FLIGHT_SIMULATION',
      defaultValue: true,
      description: 'Run TRL 6 flight simulation tests'
    )
    booleanParam(
      name: 'DEPLOY_TO_STAGING',
      defaultValue: false,
      description: 'Deploy to staging environment after successful build'
    )
    booleanParam(
        name: 'DEPLOY_CANARY',
        defaultValue: false,
        description: 'Deploy to canary environment (main branch only)'
    )
    string(
      name: 'CUSTOM_VERSION',
      defaultValue: '',
      description: 'Custom version tag (leave empty for auto-generation)'
    )
    booleanParam(
      name: 'FORCE_FULL_BUILD',
      defaultValue: false,
      description: 'Force full build ignoring change detection'
    )
  }
   
  // Build triggers
  triggers {
    // Poll SCM every 15 minutes
    pollSCM('H/15 * * * *')
     
    // Nightly builds
    cron(env.BRANCH_NAME == 'main' ? 'H 2 * * *' : '')
     
    // GitLab webhook
    gitlabPush()
  }
   
  // Pipeline options
  options {
    // Keep last 30 builds
    buildDiscarder(logRotator(
      numToKeepStr: '30',
      daysToKeepStr: '90',
      artifactNumToKeepStr: '10'
    ))
     
    // Timeout after 2 hours
    timeout(time: 2, unit: 'HOURS')
     
    // Timestamps in console output
    timestamps()
     
    // ANSI color in console
    ansiColor('xterm')
     
    // Disable concurrent builds on same branch
    disableConcurrentBuilds()
     
    // Retry failed builds once
    retry(1)
     
    // Skip default checkout for change detection (will do manual checkout in Environment Setup)
    skipDefaultCheckout true
  }
   
  // Pipeline stages
  stages {
    // =============================================================================
    // STAGE: Environment Setup
    // =============================================================================
    stage('Environment Setup') {
      steps {
        script {
          // Manual checkout
          checkout scm
           
          echo "=================================================="
          echo "AQUA V. Quantum Navigation System Pipeline"
          echo "TRL ${QNS_TRL} - ${QNS_STATUS}"
          echo "Site ${SITE_CODE} - ${SITE_NAME}"
          echo "=================================================="
           
          // Set build description
          currentBuild.description = "QNS Build - ${CMAKE_BUILD_TYPE} - Quantum: ${QUANTUM_HARDWARE}"
           
          // Generate version number
          env.QNS_VERSION = params.CUSTOM_VERSION ?: generateVersion()
          echo "Building QNS version: ${env.QNS_VERSION}"
           
          // Change detection logic
          def changes = getChanges()
          env.ONLY_DOCS_CHANGED = changes.onlyDocs
          env.MODIFIED_FILES = changes.files.join(',')
           
          if (env.ONLY_DOCS_CHANGED == 'true' && !params.FORCE_FULL_BUILD) {
            env.SKIP_BUILD = 'true'
            echo "Only documentation changes detected. Build steps will be skipped."
          } else {
            env.SKIP_BUILD = 'false'
          }
        }
      }
    }
    
    // =============================================================================
    // STAGE: Pre-Commit Checks (Added)
    // Runs basic linting/formatting for PRs to shift quality left.
    // =============================================================================
    stage('Pre-Commit Checks') {
        when {
            expression { env.CHANGE_ID != null } // Only for PRs
        }
        steps {
            sh '''
                # Assumes pre-commit is installed in the Docker image
                pre-commit install --install-hooks -f # Install hooks if not already
                pre-commit run --all-files --show-diff-on-failure
            '''
        }
    }
    
    // =============================================================================
    // STAGE: Dependency Resolution (Added)
    // Uses Conan to manage C++ dependencies.
    // =============================================================================
    stage('Dependency Resolution') {
        when {
            expression { env.SKIP_BUILD != 'true' }
        }
        steps {
            echo "Resolving Conan dependencies..."
            sh '''
                # Assumes Conan is installed and configured in the Docker image
                conan install . --build=missing \\
                    --profile=quantum_navigation \\
                    --settings compiler.version=11 \\
                    --options quantum_sdk:hardware=${QUANTUM_HARDWARE}
            '''
        }
    }
     
    // =============================================================================
    // STAGE: Quantum Resource Provisioning (Added)
    // Provisions dedicated quantum hardware/simulator for the build.
    // =============================================================================
    stage('Quantum Resource Provisioning') {
        when {
            expression { env.SKIP_BUILD != 'true' && params.QUANTUM_MODE == 'hardware' }
        }
        steps {
            script {
                echo "Provisioning quantum resources for ${QUANTUM_HARDWARE} mode..."
                env.QUANTUM_RESOURCE_ID = provisionQuantumResources() // Shared library function
                env.QUANTUM_ENDPOINT = "https://quantum-${env.QUANTUM_RESOURCE_ID}.aqua-v.aerospace"
                echo "Provisioned quantum resource with ID: ${env.QUANTUM_RESOURCE_ID}"
                echo "Quantum endpoint: ${env.QUANTUM_ENDPOINT}"
            }
        }
    }

    // =============================================================================
    // STAGE: Quantum Readiness Check
    // =============================================================================
    stage('Quantum Readiness') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      steps {
        script {
          echo "Checking quantum ${QUANTUM_HARDWARE} availability at ${QUANTUM_ENDPOINT ?: 'local'}..."
           
          sh '''
            python3 tools/quantum_hardware_check.py --mode=${QUANTUM_HARDWARE} --endpoint=${QUANTUM_ENDPOINT}
             
            if [ "${QUANTUM_HARDWARE}" = "hardware" ]; then
              echo "Verifying gravitometer (sensitivity: ${QNS_GRAVITOMETER_SENSITIVITY})"
              echo "Verifying magnetometer (range: ${QNS_MAGNETOMETER_RANGE})"
              quantum_sdk_verify --sensors --required-trl=${QNS_TRL} --endpoint=${QUANTUM_ENDPOINT}
            fi
          '''
        }
         
        // Archive quantum status
        archiveArtifacts artifacts: 'quantum_status.json', allowEmptyArchive: true
      }
      post {
        failure {
          error "Quantum hardware/simulator not available or failed readiness checks."
        }
      }
    }
     
    // =============================================================================
    // STAGE: Security Scanning
    // =============================================================================
    stage('Security Scan') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      parallel {
        stage('Code Security') {
          steps {
            echo "Running AQUA V. security compliance scan..."
             
            sh '''
              cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml
              python3 tools/quantum_security_audit.py --level=${SECURITY_SCAN_LEVEL}
            '''
             
            // Record issues
            recordIssues(
              enabledForFailure: true,
              tools: [cppCheck(pattern: 'cppcheck_report.xml')]
            )
          }
        }
         
        stage('Dependency Scan') {
          steps {
            echo "Scanning dependencies for vulnerabilities..."
            // Assuming tools for python, but also for C++ Conan deps if available
            sh '''
              safety check --json > dependency_scan.json
              python3 tools/validate_quantum_dependencies.py
              # Add Conan vulnerability scanner here if applicable
            '''
             
            // Archive security reports
            archiveArtifacts artifacts: '*_scan.json', allowEmptyArchive: true
          }
        }
         
        stage('License Compliance') {
          steps {
            echo "Checking license compliance..."
             
            sh '''
              python3 tools/license_checker.py --config=.license-config.yml
            '''
          }
        }
      }
    }
     
    // =============================================================================
    // STAGE: Build
    // =============================================================================
    stage('Build') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      steps {
        script {
          echo "Building QNS in ${CMAKE_BUILD_TYPE} mode..."
           
          // Selective build based on changes
          def buildArgs = "-DENABLE_ALI_BOB_SYNC=${ENABLE_ALI_BOB_SYNC} " +
                          "-DQNS_UPDATE_RATE_HZ=${QNS_UPDATE_RATE_HZ} " +
                          "-DQNS_VERSION=${QNS_VERSION}"
           
          if (env.MODIFIED_FILES.contains('src/quantum/')) {
            buildArgs += " -DBUILD_QUANTUM=ON"
            echo "Quantum module changes detected - full quantum rebuild"
          }
          if (env.MODIFIED_FILES.contains('src/hal/')) {
            buildArgs += " -DBUILD_SENSORS=ON"
            echo "Sensor HAL changes detected - sensor module rebuild"
          }
          // Assuming 'qkf' is a new or existing module not in the original structure
          if (env.MODIFIED_FILES.contains('src/qkf/')) {
            buildArgs += " -DBUILD_QKF=ON"
            echo "Quantum Kalman Filter changes detected - QKF rebuild"
          }
           
          sh """
            mkdir -p ${BUILD_DIR}
            cd ${BUILD_DIR}
             
            cmake .. \\
              -G "${CMAKE_GENERATOR}" \\
              -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \\
              -DENABLE_QUANTUM_HARDWARE_MODE=${QUANTUM_HARDWARE} \\
              -DQUANTUM_HARDWARE_ENDPOINT=${QUANTUM_ENDPOINT} \\ // Pass provisioned endpoint
              ${buildArgs} \\
              -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
             
            # Incremental build with ccache
            cmake --build . --parallel ${PARALLEL_JOBS} --target install
             
            # Save ccache statistics
            ccache -s > ../ccache_stats.log
          """
        }
         
        // Archive build artifacts
        archiveArtifacts artifacts: "${BUILD_DIR}/bin/*, ${BUILD_DIR}/lib/*", fingerprint: true
      }
      post {
        always {
          // Archive compile commands for analysis
          archiveArtifacts artifacts: "${BUILD_DIR}/compile_commands.json", allowEmptyArchive: true
        }
      }
    }
     
    // =============================================================================
    // STAGE: Provision Test Environment (Added)
    // =============================================================================
    stage('Provision Test Environment') {
        when {
            expression { env.SKIP_BUILD != 'true' && (params.RUN_FLIGHT_SIMULATION || params.DEPLOY_TO_STAGING || params.DEPLOY_CANARY) }
        }
        steps {
            script {
                echo "Provisioning ephemeral test environment..."
                def tfDir = 'infrastructure/test-env'
                dir(tfDir) { // Change directory for terraform commands
                    sh """
                        terraform init
                        terraform apply -auto-approve \\
                            -var="build_id=${BUILD_ID}" \\
                            -var="quantum_mode=${QUANTUM_HARDWARE}" \\
                            -var="qns_version=${env.QNS_VERSION}"
                    """
                    env.TEST_ENV_ENDPOINT = sh(
                        script: "terraform output -raw endpoint",
                        returnStdout: true
                    ).trim()
                    echo "Test environment endpoint: ${env.TEST_ENV_ENDPOINT}"
                }
            }
        }
    }

    // =============================================================================
    // STAGE: Testing
    // =============================================================================
    stage('Test') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      parallel {
        stage('Unit Tests') {
          steps {
            echo "Running unit tests..."
             
            sh '''
              cd ${BUILD_DIR}
              ctest -R "unit_" --output-on-failure --output-junit unit_test_results.xml
            '''
          }
          post {
            always {
              junit "${BUILD_DIR}/unit_test_results.xml"
            }
          }
        }
         
        stage('Integration Tests') {
          steps {
            echo "Running integration tests..."
             
            sh '''
              cd ${BUILD_DIR}
              # Pass test environment endpoint if available
              ctest -R "integration_" --output-on-failure --output-junit integration_test_results.xml --env-var TEST_ENV_ENDPOINT=${TEST_ENV_ENDPOINT}
            '''
          }
          post {
            always {
              junit "${BUILD_DIR}/integration_test_results.xml"
            }
          }
        }
         
        stage('Coverage Analysis') {
          when {
            expression { CMAKE_BUILD_TYPE == 'Debug' }
          }
          steps {
            echo "Generating coverage report..."
             
            sh '''
              cd ${BUILD_DIR}
              ctest --output-on-failure
              gcovr --xml-pretty --exclude-unreachable-branches --print-summary -o coverage.xml --root ${WORKSPACE}
              gcovr --html --html-details -o coverage.html --root ${WORKSPACE}
            '''
             
            // Publish coverage
            publishCoverage adapters: [
              coberturaAdapter('${BUILD_DIR}/coverage.xml')
            ], sourceFileResolver: sourceFiles('STORE_LAST_BUILD')
          }
        }
      }
    }
     
    // =============================================================================
    // STAGE: Quantum Validation
    // =============================================================================
    stage('Quantum Validation') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      parallel {
        stage('Algorithm Validation') {
          steps {
            echo "Validating quantum algorithms..."
             
            sh '''
              cd ${BUILD_DIR}
              ./bin/quantum_validator \\
                --trl=${QNS_TRL} \\
                --mode=${QUANTUM_HARDWARE} \\
                --update-rate=${QNS_UPDATE_RATE_HZ} \\
                --endpoint=${QUANTUM_ENDPOINT} \\ // Use provisioned endpoint
                --output=quantum_validation_report.xml
               
              # GPS-denied navigation test
              ./bin/quantum_validator \\
                --test=gps_denied \\
                --iterations=1000 \\
                --target-accuracy=${QNS_POSITION_ACCURACY} \\
                --endpoint=${QUANTUM_ENDPOINT}
            '''
          }
          post {
            always {
              junit "${BUILD_DIR}/quantum_validation_report.xml"
            }
          }
        }
         
        stage('Sensor Validation') {
          steps {
            echo "Validating quantum sensor interfaces..."
             
            sh '''
              cd ${BUILD_DIR}
              ./bin/sensor_test \\
                --gravitometer-sensitivity=${QNS_GRAVITOMETER_SENSITIVITY} \\
                --magnetometer-range=${QNS_MAGNETOMETER_RANGE} \\
                --sample-rate=${QNS_UPDATE_RATE_HZ} \\
                --endpoint=${TEST_ENV_ENDPOINT} // Use test environment endpoint if relevant
            '''
             
            archiveArtifacts artifacts: "${BUILD_DIR}/sensor_validation_data/*", allowEmptyArchive: true
          }
        }
      }
    }
     
    // =============================================================================
    // STAGE: Sensor Calibration
    // =============================================================================
    stage('Sensor Calibration') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      steps {
        echo "Running sensor calibration procedures..."
         
        sh '''
          cd ${BUILD_DIR}
           
          # Gravitometer calibration
          ./bin/qns_calibration \\
            --sensor=gravitometer \\
            --target-sensitivity=${QNS_GRAVITOMETER_SENSITIVITY} \\
            --output=gravitometer_calibration.dat \\
            --endpoint=${TEST_ENV_ENDPOINT}
           
          # Magnetometer calibration
          ./bin/qns_calibration \\
            --sensor=magnetometer \\
            --target-range=${QNS_MAGNETOMETER_RANGE} \\
            --output=magnetometer_calibration.dat \\
            --endpoint=${TEST_ENV_ENDPOINT}
           
          # Generate calibration certificate
          python3 ../tools/generate_calibration_cert.py \\
            --trl=${QNS_TRL} \\
            --site=${SITE_CODE} \\
            --version=${QNS_VERSION}
        '''
         
        archiveArtifacts artifacts: "${BUILD_DIR}/*_calibration.dat, ${BUILD_DIR}/calibration_certificate.pdf"
      }
    }
     
    // =============================================================================
    // STAGE: Quantum Optimization (NEW)
    // =============================================================================
    stage('Quantum Optimization') {
      when {
        expression { 
          env.SKIP_BUILD != 'true' && 
          params.QUANTUM_MODE == 'hardware'
        }
      }
      steps {
        echo "Running quantum circuit optimization..."
         
        sh '''
          cd ${BUILD_DIR}
           
          # Optimize quantum circuits for hardware
          ./bin/quantum_optimizer \\
            --target=nav-algorithm \\
            --platform=quantum-hardware \\
            --optimization-level=O3 \\
            --output=optimized_quantum_circuits.qasm \\
            --endpoint=${QUANTUM_ENDPOINT} // Use provisioned endpoint
           
          # Validate optimized circuits
          ./bin/quantum_validator \\
            --circuits=optimized_quantum_circuits.qasm \\
            --validate-only \\
            --endpoint=${QUANTUM_ENDPOINT}
           
          # Generate optimization report
          python3 ../tools/quantum_optimization_report.py \\
            --input=optimized_quantum_circuits.qasm \\
            --output=quantum_optimization_report.pdf
        '''
         
        archiveArtifacts artifacts: "${BUILD_DIR}/optimized_quantum_circuits.qasm, ${BUILD_DIR}/quantum_optimization_report.pdf"
      }
    }
     
    // =============================================================================
    // STAGE: Quantum Hardware Telemetry (Added)
    // Collects and analyzes real-time telemetry from quantum hardware.
    // =============================================================================
    stage('Quantum Hardware Telemetry') {
        when {
            expression { params.QUANTUM_MODE == 'hardware' }
        }
        steps {
            script {
                echo "Collecting quantum hardware telemetry from ${QUANTUM_ENDPOINT}..."
                def telemetryJobPid = sh(
                    script: """
                        python3 tools/quantum_telemetry_collector.py \\
                            --device=${QUANTUM_RESOURCE_ID} \\
                            --endpoint=${QUANTUM_ENDPOINT} \\
                            --output=quantum_telemetry.json &
                        echo \$!
                    """,
                    returnStdout: true
                ).trim()
                
                // Run tests/validation while telemetry is collecting
                try {
                    // Example: run a quantum test that interacts with the hardware
                    sh """
                        cd ${BUILD_DIR}
                        ./bin/quantum_validator --hardware --telemetry --endpoint=${QUANTUM_ENDPOINT}
                    """
                } finally {
                    // Stop telemetry and analyze
                    echo "Stopping telemetry collector (PID: ${telemetryJobPid}) and analyzing data..."
                    sh """
                        kill ${telemetryJobPid} || true # Ensure the background process is killed
                        python3 tools/analyze_quantum_telemetry.py \\
                            --input=quantum_telemetry.json \\
                            --check-qubit-coherence \\
                            --check-gate-fidelity
                    """
                    archiveArtifacts artifacts: 'quantum_telemetry.json, telemetry_analysis_report.pdf', allowEmptyArchive: true
                }
            }
        }
    }

    // =============================================================================
    // STAGE: Flight Simulation
    // =============================================================================
    stage('Flight Simulation') {
      when {
        expression { 
          env.SKIP_BUILD != 'true' &&
          params.RUN_FLIGHT_SIMULATION == true 
        }
      }
      steps {
        echo "Running TRL 6 flight simulation scenarios..."
         
        sh '''
          cd ${BUILD_DIR}
           
          # GPS-denied navigation scenario
          ./bin/flight_simulator \\
            --scenario=gps_denied \\
            --duration=3600 \\
            --update-rate=${QNS_UPDATE_RATE_HZ} \\
            --endpoint=${TEST_ENV_ENDPOINT} \\ // Use test environment endpoint
            --output=gps_denied_results.json
           
          # Urban canyon navigation
          ./bin/flight_simulator \\
            --scenario=urban_canyon \\
            --duration=1800 \\
            --magnetic-interference=high \\
            --endpoint=${TEST_ENV_ENDPOINT} \\
            --output=urban_canyon_results.json
           
          # Magnetic anomaly navigation
          ./bin/flight_simulator \\
            --scenario=magnetic_anomaly \\
            --anomaly-strength=severe \\
            --endpoint=${TEST_ENV_ENDPOINT} \\
            --output=magnetic_anomaly_results.json
           
          # Generate flight test report
          python3 ../tools/generate_flight_report.py \\
            --trl=${QNS_TRL} \\
            --version=${QNS_VERSION} \\
            --results=*_results.json
        '''
         
        archiveArtifacts artifacts: "${BUILD_DIR}/*_results.json, ${BUILD_DIR}/flight_test_report.pdf"
         
        // Publish test results (assuming this will parse the JSON into Junit XML)
        junit "${BUILD_DIR}/flight_test_results.xml"
      }
    }
     
    // =============================================================================
    // STAGE: ALI-BOB Synchronization
    // =============================================================================
    stage('ALI-BOB Sync') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      steps {
        echo "Testing ALI-BOB synchronization..."
         
        sh '''
          cd ${BUILD_DIR}
           
          # Test synchronization
          ./bin/ali_bob_sync \\
            --mode=test \\
            --sync-rate=${QNS_UPDATE_RATE_HZ} \\
            --verify=quantum_state \\
            --output=ali_bob_sync_report.xml \\
            --endpoint=${TEST_ENV_ENDPOINT}
           
          # Verify digital twin consistency
          ./bin/ali_bob_sync \\
            --mode=verify \\
            --tolerance=1e-9 \\
            --endpoint=${TEST_ENV_ENDPOINT}
        '''
         
        junit "${BUILD_DIR}/ali_bob_sync_report.xml"
      }
    }
     
    // =============================================================================
    // STAGE: Performance Benchmarking
    // =============================================================================
    stage('Performance') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      steps {
        echo "Running performance benchmarks..."
         
        sh '''
          cd ${BUILD_DIR}
           
          # Run all benchmarks
          ./bin/performance_tests \\
            --benchmark_format=json \\
            --benchmark_out=benchmark_results.json \\
            --endpoint=${TEST_ENV_ENDPOINT}
           
          # Run quantum-specific benchmarks
          ./bin/performance_tests \\
            --benchmark_filter="BM_Quantum.*" \\
            --benchmark_format=json \\
            --benchmark_out=quantum_benchmark_results.json \\
            --endpoint=${QUANTUM_ENDPOINT} // Use quantum endpoint if relevant for quantum benchmarks
           
          # Analyze results (assuming analyze_performance.py can handle multiple JSONs)
          python3 ../tools/analyze_performance.py \\
            --results=benchmark_results.json,quantum_benchmark_results.json \\
            --target-rate=${QNS_UPDATE_RATE_HZ} \\
            --trl=${QNS_TRL} \\
            --check-regression
        '''
         
        archiveArtifacts artifacts: "${BUILD_DIR}/*benchmark*.json, ${BUILD_DIR}/performance_analysis.pdf"
         
        // Plot performance trends
        perfReport sourceDataFiles: "${BUILD_DIR}/benchmark_results.json"
         
        // Check for performance regression
        script {
          def regressionDetected = sh(
            script: "grep -q 'REGRESSION' ${BUILD_DIR}/performance_analysis.pdf",
            returnStatus: true
          ) == 0
           
          if (regressionDetected) {
            currentBuild.result = 'UNSTABLE'
            error "Performance regression detected!"
          }
        }
      }
    }
     
    // =============================================================================
    // STAGE: Packaging
    // =============================================================================
    stage('Package') {
      when {
        expression { env.SKIP_BUILD != 'true' }
      }
      parallel {
        stage('Debian Package') {
          steps {
            echo "Creating Debian package..."
             
            sh '''
              cd ${BUILD_DIR}
              cpack -G DEB
              dpkg --info *.deb
              dpkg --contents *.deb
            '''
             
            archiveArtifacts artifacts: "${BUILD_DIR}/*.deb"
          }
        }
         
        stage('Docker Image') {
          steps {
            echo "Building Docker image..."
             
            script {
              docker.withRegistry("https://${DOCKER_REGISTRY_CREDS.url}", DOCKER_REGISTRY_CREDS.id) {
                def image = docker.build(
                  "aqua-v/qns:${env.BUILD_ID}",
                  "--build-arg VERSION=${QNS_VERSION} " +
                  "--build-arg BUILD_DATE=${new Date().format('yyyy-MM-dd')} " +
                  "--build-arg VCS_REF=${env.GIT_COMMIT} " +
                  "."
                )
                 
                image.push()
                image.push('latest')
                 
                if (env.TAG_NAME) {
                  image.push(env.TAG_NAME)
                }
              }
            }
          }
        }
         
        stage('Documentation') {
          steps {
            script {
              // Always build documentation if docs changed
              if (env.ONLY_DOCS_CHANGED == 'true' || env.MODIFIED_FILES.contains('docs/')) {
                echo "Building documentation..."
                 
                sh '''
                  cd ${BUILD_DIR}
                  make docs
                '''
                 
                publishHTML([
                  allowMissing: false,
                  alwaysLinkToLastBuild: true,
                  keepAll: true,
                  reportDir: "${BUILD_DIR}/docs/html",
                  reportFiles: 'index.html',
                  reportName: 'QNS Documentation',
                  reportTitles: 'AQUA V. QNS Documentation'
                ])
              } else {
                echo "Skipping documentation rebuild - no doc changes detected"
              }
            }
          }
        }
      }
    }
    
    // =============================================================================
    // STAGE: Publish to Artifactory (Added)
    // =============================================================================
    stage('Publish to Artifactory') {
        when {
            expression { env.SKIP_BUILD != 'true' }
        }
        steps {
            script {
                echo "Publishing artifacts to Artifactory..."
                def server = Artifactory.server 'aqua-v-artifactory' // Assumes Artifactory server is configured in Jenkins
                def uploadSpec = """{
                    "files": [
                        {
                            "pattern": "${BUILD_DIR}/*.deb",
                            "target": "aqua-v-debian/pool/main/q/qns/"
                        },
                        {
                            "pattern": "${BUILD_DIR}/*_calibration.dat",
                            "target": "aqua-v-calibration/${QNS_VERSION}/"
                        },
                        {
                            "pattern": "${BUILD_DIR}/quantum_optimization_report.pdf",
                            "target": "aqua-v-reports/${QNS_VERSION}/"
                        },
                        {
                            "pattern": "${BUILD_DIR}/flight_test_report.pdf",
                            "target": "aqua-v-reports/${QNS_VERSION}/"
                        }
                    ]
                }"""
                server.upload(uploadSpec)
                echo "Artifacts published to Artifactory."
            }
        }
    }
     
    // =============================================================================
    // STAGE: Deployment
    // =============================================================================
    stage('Deploy to Staging') {
      when {
        expression { 
          params.DEPLOY_TO_STAGING == true && 
          currentBuild.result == null &&
          env.SKIP_BUILD != 'true'
        }
      }
      steps {
        echo "Deploying to Silicon Valley staging environment: ${TEST_ENV_ENDPOINT}"
         
        withCredentials([file(credentialsId: ANSIBLE_VAULT_PASS_FILE.id, variable: 'VAULT_PASS_FILE_PATH')]) {
          sh """
            export ANSIBLE_VAULT_PASSWORD_FILE=${VAULT_PASS_FILE_PATH}
             
            ansible-playbook deploy/staging.yml \\
              -e "site_code=${SITE_CODE}" \\
              -e "qns_version=${QNS_VERSION}" \\
              -e "trl_level=${QNS_TRL}" \\
              -e "build_number=${BUILD_NUMBER}" \\
              -e "target_endpoint=${TEST_ENV_ENDPOINT}"
          """
        }
      }
    }

    // =============================================================================
    // STAGE: Canary Deployment (Added)
    // Progressive rollout to production.
    // =============================================================================
    stage('Canary Deployment') {
        when {
            expression { 
                params.DEPLOY_CANARY == true && 
                currentBuild.result == null && 
                env.BRANCH_NAME == 'main' // Only deploy from main branch
            }
        }
        steps {
            script {
                echo "Initiating canary deployment for QNS version ${QNS_VERSION}..."
                
                // Deploy to a small fraction of the fleet (e.g., 5%)
                // Assumes 'qns-canary' deployment exists in Kubernetes
                sh """
                    kubectl set image deployment/qns-canary \\
                        qns=aqua-v/qns:${QNS_VERSION} \\
                        -n silicon-valley
                    
                    # Scale to desired canary replicas (e.g., 2 for 5% of a 40-replica cluster)
                    kubectl scale deployment/qns-canary --replicas=2 -n silicon-valley
                """
                
                echo "Monitoring canary deployment for 30 minutes..."
                timeout(time: 30, unit: 'MINUTES') {
                    sh """
                        python3 tools/canary_monitor.py \\
                            --metrics-endpoint=${PROMETHEUS_ENDPOINT} \\
                            --threshold-error-rate=0.01 \\
                            --threshold-latency-p99=100ms \\
                            --canary-deployment-name=qns-canary \\
                            --version=${QNS_VERSION}
                    """
                }
                
                echo "Canary deployment stable. Promoting to full production..."
                // Promote if successful (update the main production deployment)
                sh """
                    kubectl set image deployment/qns \\
                        qns=aqua-v/qns:${QNS_VERSION} \\
                        -n silicon-valley
                    
                    kubectl rollout status deployment/qns -n silicon-valley
                """
                echo "Full production deployment complete."
            }
        }
        post {
            failure {
                echo "Canary deployment failed. Rolling back canary."
                sh "kubectl rollout undo deployment/qns-canary -n silicon-valley || true"
                error "Canary deployment failed, rollback initiated for canary."
            }
        }
    }
  }
   
  // Post-build actions
  post {
    always {
      // Enhanced cleanup
      echo "Cleaning up workspace..."
      sh '''
        # Show ccache statistics
        ccache -s
         
        # Clean Docker resources older than 24 hours (or better, use a smarter cleanup based on build history)
        docker system prune -f --filter "until=24h"
         
        # Clean temporary files
        rm -rf ${BUILD_DIR}/tmp
         
        # Save ccache stats
        ccache -s > ccache_stats.log
      '''
       
      // Archive ccache stats
      archiveArtifacts artifacts: 'ccache_stats.log', allowEmptyArchive: true
       
      // Generate build summary
      script {
        def summary = """
        AQUA V. QNS Build Summary
        ========================
        Version: ${env.QNS_VERSION}
        Build Type: ${CMAKE_BUILD_TYPE}
        Quantum Mode: ${QUANTUM_HARDWARE}
        TRL: ${QNS_TRL}
        Site: ${SITE_CODE}
        Duration: ${currentBuild.durationString}
        Status: ${currentBuild.result ?: 'SUCCESS'}
        Changed Files: ${env.MODIFIED_FILES ?: 'N/A'}
        Docs Only: ${env.ONLY_DOCS_CHANGED ?: 'false'}
        Quantum Resource ID: ${env.QUANTUM_RESOURCE_ID ?: 'N/A'}
        Test Env Endpoint: ${env.TEST_ENV_ENDPOINT ?: 'N/A'}
        """
         
        writeFile file: 'build_summary.txt', text: summary
        archiveArtifacts artifacts: 'build_summary.txt'
      }
    }
     
    success {
      echo "✅ AQUA V. QNS Pipeline completed successfully!"
       
      // Send success notification
      script {
        sendSlackNotification(
          color: 'good',
          message: "QNS Build Successful - ${env.QNS_VERSION}"
        )
      }
    }
     
    failure {
      echo "❌ AQUA V. QNS Pipeline failed!"
       
      // Send failure notification
      script {
        sendSlackNotification(
          color: 'danger',
          message: "QNS Build Failed - ${env.QNS_VERSION}"
        )
      }
    }
     
    unstable {
      echo "⚠️ AQUA V. QNS Pipeline completed with warnings"
       
      // Send warning notification
      script {
        sendSlackNotification(
          color: 'warning',
          message: "QNS Build Unstable - ${env.QNS_VERSION}"
        )
      }
    }
     
    // Added for performance regression detection
    regression {
      script {
        sendSlackNotification(
          color: 'warning',
          message: "Performance Regression Detected - ${env.QNS_VERSION}"
        )
         
        // Create regression report
        sh '''
          python3 tools/generate_regression_report.py \\
            --version=${QNS_VERSION} \\
            --benchmarks=${BUILD_DIR}/*benchmark*.json \\
            --output=regression_report.html
        '''
         
        publishHTML([
          allowMissing: false,
          alwaysLinkToLastBuild: true,
          keepAll: false,
          reportDir: '.',
          reportFiles: 'regression_report.html',
          reportName: 'Performance Regression Report'
        ])
      }
    }
     
    // Deprovision resources in cleanup for all outcomes
    cleanup {
      // De-provision Ephemeral Test Environment
      script {
          if (env.TEST_ENV_ENDPOINT != '') {
              echo "De-provisioning ephemeral test environment..."
              def tfDir = 'infrastructure/test-env'
              dir(tfDir) {
                  sh "terraform destroy -auto-approve -var=\"build_id=${BUILD_ID}\""
              }
              echo "Ephemeral test environment destroyed."
          }
      }

      // De-provision Quantum Resources
      script {
          if (env.QUANTUM_RESOURCE_ID != '') {
              echo "De-provisioning quantum resource (ID: ${env.QUANTUM_RESOURCE_ID})..."
              deprovisionQuantumResources(env.QUANTUM_RESOURCE_ID) // Shared library function
              echo "Quantum resource de-provisioned."
          }
      }

      // Clean Docker resources
      sh '''
        docker system prune -f || true
        rm -rf ${BUILD_DIR}/temp || true
      '''
    }
  }
}

// =============================================================================
// Helper Functions (Assumed to be in aqua-v-shared-library@v1.1.0)
// For illustrative purposes, including them here.
// =============================================================================

/**
 * Generates a version string based on current date and build number.
 * @return String The generated version string.
 */
def generateVersion() {
  def date = new Date().format('yyyy.MM.dd')
  def buildNum = env.BUILD_NUMBER.padLeft(4, '0')
  return "${date}.${buildNum}"
}

/**
 * Sends a Slack notification.
 * @param args Map containing message, color, and other details for Slack.
 */
def sendSlackNotification(Map args) {
  if (env.SLACK_WEBHOOK) {
    def attachments = [[
      color: args.color,
      title: "AQUA V. QNS Pipeline ${env.BUILD_NUMBER}",
      text: args.message,
      fields: [
        [title: "Project", value: env.JOB_NAME, short: true],
        [title: "Branch", value: env.BRANCH_NAME, short: true],
        [title: "TRL", value: env.QNS_TRL, short: true],
        [title: "Site", value: env.SITE_CODE, short: true],
        [title: "Version", value: env.QNS_VERSION, short: true],
        [title: "Duration", value: currentBuild.durationString, short: true]
      ],
      footer: "AQUA V. CI/CD",
      ts: System.currentTimeMillis() / 1000
    ]]
     
    slackSend(
      channel: '#qns-builds',
      webhookUrl: env.SLACK_WEBHOOK,
      attachments: attachments
    )
  }
}

/**
 * Analyzes SCM changes to determine if only documentation files were modified.
 * @return Map containing 'files' (list of modified paths) and 'onlyDocs' (boolean).
 */
def getChanges() {
  def changeLogSets = currentBuild.changeSets
  def modifiedFiles = []
  def onlyDocs = true
   
  for (changeLogSet in changeLogSets) {
    for (entry in changeLogSet.items) {
      for (file in entry.affectedFiles) {
        modifiedFiles.add(file.path)
        if (!file.path.startsWith('docs/') && 
            !file.path.endsWith('.md') && 
            !file.path.endsWith('.rst') && // Assuming RST is also doc
            !file.path.contains('LICENSE') && // Licenses are also docs
            !file.path.contains('.gitignore') // .gitignore changes shouldn't trigger full build
            ) {
          onlyDocs = false
        }
      }
    }
  }
  // If no files modified (e.g., triggered manually without SCM changes, but with force_full_build=false)
  // Or if it's a first build, onlyDocs should be false to force a full build.
  if (modifiedFiles.isEmpty()) {
      onlyDocs = false
  }
   
  return [
    files: modifiedFiles,
    onlyDocs: onlyDocs
  ]
}

/**
 * Provisions a quantum simulator or hardware instance.
 * @return String The ID of the provisioned resource.
 */
def provisionQuantumResources() {
    echo "Simulating AWS Quantum resource provisioning..."
    // In a real scenario, this would call AWS CLI or SDK
    // Example: aws quantum provision-simulator --instance-type=sv1.xlarge --duration=2h ...
    return UUID.randomUUID().toString() // Generate a dummy ID for illustration
}

/**
 * De-provisions a quantum simulator or hardware instance.
 * @param resourceId The ID of the resource to de-provision.
 */
def deprovisionQuantumResources(resourceId) {
    echo "Simulating AWS Quantum resource de-provisioning for ID: ${resourceId}..."
    // In a real scenario, this would call AWS CLI or SDK
    // Example: aws quantum terminate-instance --instance-id=${resourceId}
}

// EOF
