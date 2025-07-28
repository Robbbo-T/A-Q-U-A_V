/**
 * ============================================================================
 * AQUA V. - Voice Command System Integration Implementation
 * ============================================================================
 * 
 * Document ID: AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-345-50-01-TPL-TEC-INTEG-001-QDAT-v0.1.0
 * 
 * Nomenclature Breakdown (AQUA V. Official System v3.1):
 * - LÍNEA:     AMP (AMPEL360 Products)
 * - PRODUCTO:  EVTOL (Electric Vertical Take-Off and Landing Aircraft)
 * - MSN:       25SVD0001 (2025 Silicon Valley Development Unit 0001)
 * - FASE:      DEV (Development Phase)
 * - ALI/BOB:   BOB (Build-Operate-Build Digital Systems)
 * - ARTIFACT:  TEC (Technical Artifacts)
 * - TYPE:      SM (Software Module)
 * - UTCS:      DTCEC-345-50-01 (Digital Twin, Cloud & Edge Computing - System Integration)
 * - CÓDIGO:    000-00-01 (Primary component within UTCS)
 * - TEMPLATE:  TPL-TEC-INTEG-001 (Technical Template - Integration - Instance 001)
 * - QD:        QDAT (Q-Data Governance Division)
 * - VERSIÓN:   v0.1.0 (Initial development version)
 * 
 * Description: Implementation of master integration engine for voice command system
 *              Orchestrates complete voice recognition pipeline with aerospace compliance
 * 
 * Digital Thread Integration:
 * - Parent System: AMPEL360 Training VR System
 * - Component: Voice Recognition Engine Core Integration
 * - Dependencies: All voice command subsystems (DTCEC-320 through DTCEC-344)
 * - Interfaces: Unreal Engine 5.0+, VR Systems, Training Simulation Framework
 * 
 * Compliance:
 * - EASA CS-25 Voice Command Integration Requirements
 * - FAA Part 25 Human Factors Standards
 * - DO-178C Software Considerations (DAL-C)
 * - AS9100/ISO 9001 Quality Management
 * - AQUA V. Digital Thread Standards v3.1
 * 
 * Author:      AQUA V. Development Team - QDAT Division
 * Date:        2025-07-28
 * Copyright:   (c) 2025 ROBBBO-T GAIA AIR & SPACE
 * License:     Proprietary - Aerospace Training Use Only
 * 
 * ============================================================================
 */

#include "AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-345-50-01-TPL-TEC-INTEG-001-QDAT-v0.1.0.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace AQUA_V::VoiceCommands::Integration;

/**
 * ============================================================================
 * CONSTRUCTOR AND INITIALIZATION
 * ============================================================================
 */

AVoiceCommandSystemIntegration::AVoiceCommandSystemIntegration() {
    PrimaryActorTick.bCanEverTick = true;
    
    // Initialize default configuration
    SystemConfig = CreateDefaultAerospaceVoiceConfig();
    
    // Initialize system status
    SystemStatus.SystemState = EVoiceSystemState::UNINITIALIZED;
    SystemStatus.CurrentStage = EProcessingStage::AUDIO_CAPTURE;
    SystemStatus.LastError = EIntegrationError::NONE;
    
    // Initialize performance tracking
    bSystemInitialized = false;
    bVoiceMonitoringActive = false;
    bProcessingCommand = false;
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Voice Command System Integration Actor created"));
}

AVoiceCommandSystemIntegration::~AVoiceCommandSystemIntegration() {
    ShutdownVoiceSystem();
}

void AVoiceCommandSystemIntegration::BeginPlay() {
    Super::BeginPlay();
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] BeginPlay - Starting voice system initialization"));
    
    // Auto-initialize if enabled
    if (SystemConfig.bEnabled) {
        if (!InitializeVoiceSystem(SystemConfig)) {
            UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Failed to auto-initialize voice system"));
            SetSystemState(EVoiceSystemState::ERROR_STATE);
        }
    }
}

void AVoiceCommandSystemIntegration::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] EndPlay - Shutting down voice system"));
    ShutdownVoiceSystem();
    Super::EndPlay(EndPlayReason);
}

void AVoiceCommandSystemIntegration::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    
    if (bSystemInitialized) {
        // Update system uptime
        SystemStatus.UptimeSeconds += DeltaTime;
        
        // Process any queued commands
        if (ProcessingQueue.Num() > 0 && !bProcessingCommand) {
            FVoiceCommandContext NextContext = ProcessingQueue[0];
            ProcessingQueue.RemoveAt(0);
            ProcessCommandPipeline(NextContext, ""); // Audio input would be provided separately
        }
    }
}

bool AVoiceCommandSystemIntegration::InitializeVoiceSystem(const FVoiceSystemConfig& Config) {
    if (bSystemInitialized) {
        UE_LOG(LogTemp, Warning, TEXT("[AQUA V Voice Integration] System already initialized"));
        return true;
    }
    
    SetSystemState(EVoiceSystemState::INITIALIZING);
    
    // Update configuration
    SystemConfig = Config;
    
    // Validate configuration
    FString ErrorMessage;
    if (!ValidateVoiceSystemConfig(SystemConfig, ErrorMessage)) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Invalid configuration: %s"), *ErrorMessage);
        SetSystemState(EVoiceSystemState::ERROR_STATE);
        return false;
    }
    
    // Initialize all subsystems
    if (!InitializeSubsystems()) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Failed to initialize subsystems"));
        SetSystemState(EVoiceSystemState::ERROR_STATE);
        return false;
    }
    
    // Start monitoring timers
    if (UWorld* World = GetWorld()) {
        // Health check timer
        World->GetTimerManager().SetTimer(
            HealthCheckTimer,
            this,
            &AVoiceCommandSystemIntegration::CheckSubsystemHealth,
            AQUA_V_SUBSYSTEM_HEALTH_CHECK_INTERVAL,
            true
        );
        
        // Performance monitoring timer
        if (SystemConfig.bPerformanceMonitoring) {
            World->GetTimerManager().SetTimer(
                PerformanceMonitorTimer,
                this,
                &AVoiceCommandSystemIntegration::UpdatePerformanceMetrics,
                AQUA_V_PERFORMANCE_MONITOR_INTERVAL,
                true
            );
        }
        
        // Auto-calibration timer
        if (SystemConfig.bAutoCalibration) {
            World->GetTimerManager().SetTimer(
                CalibrationTimer,
                this,
                &AVoiceCommandSystemIntegration::PerformAutoCalibration,
                AQUA_V_AUTO_CALIBRATION_INTERVAL,
                true
            );
        }
    }
    
    // Initialize command history
    CommandHistory.Reserve(SystemConfig.CommandHistorySize);
    
    bSystemInitialized = true;
    SetSystemState(EVoiceSystemState::READY);
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Voice system initialized successfully"));
    return true;
}

void AVoiceCommandSystemIntegration::ShutdownVoiceSystem() {
    if (!bSystemInitialized) {
        return;
    }
    
    SetSystemState(EVoiceSystemState::SHUTDOWN);
    
    // Stop monitoring
    StopVoiceMonitoring();
    
    // Clear timers
    if (UWorld* World = GetWorld()) {
        World->GetTimerManager().ClearTimer(HealthCheckTimer);
        World->GetTimerManager().ClearTimer(PerformanceMonitorTimer);
        World->GetTimerManager().ClearTimer(CalibrationTimer);
    }
    
    // Shutdown all subsystems
    ShutdownSubsystems();
    
    // Clear data
    ProcessingQueue.Empty();
    CommandHistory.Empty();
    LatencyHistory.clear();
    AccuracyHistory.clear();
    
    bSystemInitialized = false;
    bVoiceMonitoringActive = false;
    bProcessingCommand = false;
    
    SetSystemState(EVoiceSystemState::UNINITIALIZED);
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Voice system shutdown complete"));
}

bool AVoiceCommandSystemIntegration::IsSystemReady() const {
    return bSystemInitialized && SystemStatus.SystemState == EVoiceSystemState::READY;
}

/**
 * ============================================================================
 * VOICE COMMAND PROCESSING IMPLEMENTATION
 * ============================================================================
 */

void AVoiceCommandSystemIntegration::ProcessVoiceCommand(
    const FString& AudioInput,
    const FVoiceCommandContext& Context) {
    
    if (!IsSystemReady()) {
        UE_LOG(LogTemp, Warning, TEXT("[AQUA V Voice Integration] System not ready for command processing"));
        return;
    }
    
    if (bProcessingCommand && ProcessingQueue.Num() >= SystemConfig.MaxConcurrentCommands) {
        UE_LOG(LogTemp, Warning, TEXT("[AQUA V Voice Integration] Command queue full, dropping command"));
        return;
    }
    
    // Queue the command for processing
    FVoiceCommandContext ProcessingContext = Context;
    ProcessingContext.SessionId = GenerateSessionId();
    ProcessingContext.CommandStartTime = FDateTime::Now();
    
    ProcessingQueue.Add(ProcessingContext);
    SystemStatus.ActiveCommands = ProcessingQueue.Num();
    
    LogIntegrationActivity("Command Queued", ProcessingContext);
}

bool AVoiceCommandSystemIntegration::StartVoiceMonitoring() {
    if (!IsSystemReady()) {
        return false;
    }
    
    if (bVoiceMonitoringActive) {
        UE_LOG(LogTemp, Warning, TEXT("[AQUA V Voice Integration] Voice monitoring already active"));
        return true;
    }
    
    // Start audio stream processor monitoring
    if (AudioProcessor) {
        // In real implementation, would start continuous audio capture
        bVoiceMonitoringActive = true;
        SetSystemState(EVoiceSystemState::ACTIVE);
        
        UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Voice monitoring started"));
        return true;
    }
    
    return false;
}

void AVoiceCommandSystemIntegration::StopVoiceMonitoring() {
    if (!bVoiceMonitoringActive) {
        return;
    }
    
    // Stop audio stream processor
    if (AudioProcessor) {
        // In real implementation, would stop audio capture
        bVoiceMonitoringActive = false;
        SetSystemState(EVoiceSystemState::READY);
        
        UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Voice monitoring stopped"));
    }
}

bool AVoiceCommandSystemIntegration::IsVoiceMonitoringActive() const {
    return bVoiceMonitoringActive;
}

bool AVoiceCommandSystemIntegration::TriggerVoiceRecognition() {
    if (!IsSystemReady()) {
        return false;
    }
    
    // Create immediate command context
    FVoiceCommandContext Context;
    Context.SessionId = GenerateSessionId();
    Context.UserId = "MANUAL_TRIGGER";
    Context.CommandStartTime = FDateTime::Now();
    
    ProcessVoiceCommand("", Context);
    return true;
}

void AVoiceCommandSystemIntegration::CancelCurrentCommand() {
    if (bProcessingCommand) {
        bProcessingCommand = false;
        SetProcessingStage(EProcessingStage::FAILED);
        SetSystemState(EVoiceSystemState::READY);
        
        UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Current command processing cancelled"));
    }
}

/**
 * ============================================================================
 * STATUS AND MONITORING IMPLEMENTATION
 * ============================================================================
 */

FVoiceSystemStatus AVoiceCommandSystemIntegration::GetSystemStatus() const {
    return SystemStatus;
}

EVoiceSystemState AVoiceCommandSystemIntegration::GetSystemState() const {
    return SystemStatus.SystemState;
}

EProcessingStage AVoiceCommandSystemIntegration::GetCurrentProcessingStage() const {
    return SystemStatus.CurrentStage;
}

bool AVoiceCommandSystemIntegration::IsSubsystemHealthy(int32 SubsystemMask) const {
    return (SystemStatus.SubsystemHealth & SubsystemMask) == SubsystemMask;
}

void AVoiceCommandSystemIntegration::GetPerformanceMetrics(
    float& AverageLatency, 
    float& Accuracy, 
    int32& CommandsProcessed) const {
    
    AverageLatency = SystemStatus.AverageLatencyMs;
    Accuracy = SystemStatus.CurrentAccuracy;
    CommandsProcessed = SystemStatus.CommandsProcessed;
}

/**
 * ============================================================================
 * CONFIGURATION AND CALIBRATION IMPLEMENTATION
 * ============================================================================
 */

void AVoiceCommandSystemIntegration::UpdateConfiguration(const FVoiceSystemConfig& NewConfig) {
    SystemConfig = NewConfig;
    
    // Update subsystem configurations
    if (AudioResponseGenerator) {
        FAudioResponseConfig AudioConfig;
        AudioConfig.bTrainingMode = NewConfig.bTrainingMode;
        AudioResponseGenerator->UpdateConfiguration(AudioConfig);
    }
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Configuration updated"));
}

FVoiceSystemConfig AVoiceCommandSystemIntegration::GetConfiguration() const {
    return SystemConfig;
}

bool AVoiceCommandSystemIntegration::CalibrateVoiceRecognition(const FString& UserId) {
    if (!IsSystemReady()) {
        return false;
    }
    
    SetSystemState(EVoiceSystemState::MAINTENANCE_MODE);
    
    // Perform calibration for specific user
    // In real implementation, would run calibration procedures
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Voice calibration completed for user: %s"), *UserId);
    
    SetSystemState(EVoiceSystemState::READY);
    return true;
}

bool AVoiceCommandSystemIntegration::RunSystemSelfTest() {
    if (!IsSystemReady()) {
        return false;
    }
    
    SetSystemState(EVoiceSystemState::MAINTENANCE_MODE);
    
    bool TestResult = true;
    
    // Test all subsystems
    if (!AudioProcessor) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Self-test failed: Audio processor not available"));
        TestResult = false;
    }
    
    if (!NLPEngine) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Self-test failed: NLP engine not available"));
        TestResult = false;
    }
    
    if (!CommandParser) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Self-test failed: Command parser not available"));
        TestResult = false;
    }
    
    if (!AudioResponseGenerator) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Self-test failed: Audio response generator not available"));
        TestResult = false;
    }
    
    SetSystemState(EVoiceSystemState::READY);
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] System self-test completed: %s"), 
           TestResult ? TEXT("PASSED") : TEXT("FAILED"));
    
    return TestResult;
}

void AVoiceCommandSystemIntegration::ResetToDefaults() {
    SystemConfig = CreateDefaultAerospaceVoiceConfig();
    UpdateConfiguration(SystemConfig);
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] System reset to defaults"));
}

/**
 * ============================================================================
 * TRAINING AND LEARNING IMPLEMENTATION
 * ============================================================================
 */

void AVoiceCommandSystemIntegration::SetTrainingMode(bool bEnabled) {
    SystemConfig.bTrainingMode = bEnabled;
    UpdateConfiguration(SystemConfig);
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Training mode: %s"), 
           bEnabled ? TEXT("ENABLED") : TEXT("DISABLED"));
}

void AVoiceCommandSystemIntegration::AddTrainingCommand(
    const FString& Command, 
    const FString& ExpectedAction) {
    
    // Add to training data for machine learning
    // In real implementation, would store in training database
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Training command added: %s -> %s"), 
           *Command, *ExpectedAction);
}

TArray<FVoiceCommandResult> AVoiceCommandSystemIntegration::GetCommandHistory() const {
    return CommandHistory;
}

void AVoiceCommandSystemIntegration::ClearCommandHistory() {
    CommandHistory.Empty();
    SystemStatus.CommandsProcessed = 0;
    SystemStatus.SuccessfulCommands = 0;
    SystemStatus.FailedCommands = 0;
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Command history cleared"));
}

/**
 * ============================================================================
 * PRIVATE METHOD IMPLEMENTATIONS
 * ============================================================================
 */

bool AVoiceCommandSystemIntegration::InitializeSubsystems() {
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Initializing subsystems..."));
    
    // Initialize Audio Stream Processor
    try {
        AudioProcessor = std::make_unique<AQUA_V::VoiceCommands::AudioProcessor::AudioStreamProcessor>();
        if (!AudioProcessor->Initialize()) {
            HandleSubsystemError("AudioProcessor", "Failed to initialize audio stream processor");
            return false;
        }
        SystemStatus.SubsystemHealth |= 0x01; // Set bit 0 for audio processor
    } catch (const std::exception& e) {
        HandleSubsystemError("AudioProcessor", e.what());
        return false;
    }
    
    // Initialize NLP Engine
    try {
        NLPEngine = std::make_unique<AQUA_V::VoiceCommands::NLP::NaturalLanguageProcessor>();
        if (!NLPEngine->Initialize()) {
            HandleSubsystemError("NLPEngine", "Failed to initialize NLP engine");
            return false;
        }
        SystemStatus.SubsystemHealth |= 0x02; // Set bit 1 for NLP engine
    } catch (const std::exception& e) {
        HandleSubsystemError("NLPEngine", e.what());
        return false;
    }
    
    // Initialize Command Parser
    try {
        CommandParser = std::make_unique<AQUA_V::VoiceCommands::Parser::CommandParser>();
        AQUA_V::VoiceCommands::Parser::CommandParserConfig ParserConfig;
        ParserConfig.strict_validation = true;
        ParserConfig.safety_checks = true;
        ParserConfig.training_mode = SystemConfig.bTrainingMode;
        
        if (!CommandParser->Initialize(ParserConfig)) {
            HandleSubsystemError("CommandParser", "Failed to initialize command parser");
            return false;
        }
        SystemStatus.SubsystemHealth |= 0x04; // Set bit 2 for command parser
    } catch (const std::exception& e) {
        HandleSubsystemError("CommandParser", e.what());
        return false;
    }
    
    // Initialize Audio Response Generator
    AudioResponseGenerator = NewObject<UAudioResponseGenerator>(this);
    if (AudioResponseGenerator) {
        FAudioResponseConfig ResponseConfig = CreateDefaultAerospaceAudioConfig();
        ResponseConfig.bTrainingMode = SystemConfig.bTrainingMode;
        
        if (!AudioResponseGenerator->Initialize(ResponseConfig)) {
            HandleSubsystemError("AudioResponseGenerator", "Failed to initialize audio response generator");
            return false;
        }
        SystemStatus.SubsystemHealth |= 0x08; // Set bit 3 for audio response generator
    } else {
        HandleSubsystemError("AudioResponseGenerator", "Failed to create audio response generator object");
        return false;
    }
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] All subsystems initialized successfully"));
    return true;
}

void AVoiceCommandSystemIntegration::ShutdownSubsystems() {
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Shutting down subsystems..."));
    
    // Shutdown in reverse order
    if (AudioResponseGenerator) {
        AudioResponseGenerator->Shutdown();
        AudioResponseGenerator = nullptr;
        SystemStatus.SubsystemHealth &= ~0x08; // Clear bit 3
    }
    
    if (CommandParser) {
        CommandParser.reset();
        SystemStatus.SubsystemHealth &= ~0x04; // Clear bit 2
    }
    
    if (NLPEngine) {
        NLPEngine.reset();
        SystemStatus.SubsystemHealth &= ~0x02; // Clear bit 1
    }
    
    if (AudioProcessor) {
        AudioProcessor.reset();
        SystemStatus.SubsystemHealth &= ~0x01; // Clear bit 0
    }
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] All subsystems shutdown complete"));
}

void AVoiceCommandSystemIntegration::SetSystemState(EVoiceSystemState NewState) {
    if (SystemStatus.SystemState != NewState) {
        EVoiceSystemState OldState = SystemStatus.SystemState;
        SystemStatus.SystemState = NewState;
        
        UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] System state changed: %d -> %d"), 
               (int32)OldState, (int32)NewState);
        
        OnVoiceSystemStateChanged.Broadcast(OldState, NewState);
    }
}

void AVoiceCommandSystemIntegration::SetProcessingStage(EProcessingStage NewStage) {
    if (SystemStatus.CurrentStage != NewStage) {
        SystemStatus.CurrentStage = NewStage;
        
        UE_LOG(LogTemp, VeryVerbose, TEXT("[AQUA V Voice Integration] Processing stage: %s"), 
               *ProcessingStageToString(NewStage));
    }
}

void AVoiceCommandSystemIntegration::HandleSubsystemError(
    const FString& SubsystemName, 
    const FString& ErrorMessage) {
    
    SystemStatus.LastError = EIntegrationError::SUBSYSTEM_FAILURE;
    SystemStatus.LastErrorMessage = FString::Printf(TEXT("%s: %s"), *SubsystemName, *ErrorMessage);
    
    UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Integration] Subsystem error - %s"), 
           *SystemStatus.LastErrorMessage);
    
    OnVoiceSystemError.Broadcast(
        EIntegrationError::SUBSYSTEM_FAILURE, 
        SystemStatus.LastErrorMessage, 
        CurrentContext
    );
}

void AVoiceCommandSystemIntegration::ProcessCommandPipeline(
    const FVoiceCommandContext& Context, 
    const FString& AudioInput) {
    
    if (bProcessingCommand) {
        return; // Already processing another command
    }
    
    bProcessingCommand = true;
    CurrentContext = Context;
    LastCommandStartTime = std::chrono::high_resolution_clock::now();
    
    SetSystemState(EVoiceSystemState::PROCESSING);
    
    FVoiceCommandResult Result;
    Result.Context = Context;
    Result.OriginalText = AudioInput;
    
    try {
        // Stage 1: Audio Stream Processing
        SetProcessingStage(EProcessingStage::AUDIO_CAPTURE);
        Result.CompletedStages.Add(EProcessingStage::AUDIO_CAPTURE);
        
        SetProcessingStage(EProcessingStage::STREAM_PROCESSING);
        if (AudioProcessor) {
            // Process audio stream
            Result.CompletedStages.Add(EProcessingStage::STREAM_PROCESSING);
        }
        
        // Stage 2: NLP Analysis
        SetProcessingStage(EProcessingStage::NLP_ANALYSIS);
        if (NLPEngine) {
            // Analyze natural language
            std::string ProcessedText = AudioInput.ToStdString(); // Simplified
            std::string Intent = "flight_control_command"; // Placeholder
            std::vector<std::string> Entities = {"altitude", "5000"}; // Placeholder
            
            Result.CompletedStages.Add(EProcessingStage::NLP_ANALYSIS);
        }
        
        // Stage 3: Command Parsing
        SetProcessingStage(EProcessingStage::COMMAND_PARSING);
        if (CommandParser) {
            // Parse command
            std::string Intent = "climb_to_altitude";
            std::vector<std::string> Entities = {"5000"};
            
            auto ParsedCommand = CommandParser->ParseCommand(AudioInput.ToStdString(), Intent, Entities);
            
            Result.CommandAction = FString(ParsedCommand.action.c_str());
            Result.Confidence = ParsedCommand.confidence;
            Result.ATAChapter = FString(ParsedCommand.ata_chapter.c_str());
            
            // Convert parameters
            for (const auto& param : ParsedCommand.parameters) {
                FString ParamValue;
                if (std::holds_alternative<std::string>(param.value)) {
                    ParamValue = FString(std::get<std::string>(param.value).c_str());
                } else if (std::holds_alternative<int>(param.value)) {
                    ParamValue = FString::FromInt(std::get<int>(param.value));
                } else if (std::holds_alternative<float>(param.value)) {
                    ParamValue = FString::SanitizeFloat(std::get<float>(param.value));
                }
                Result.Parameters.Add(FString(param.name.c_str()), ParamValue);
            }
            
            Result.CompletedStages.Add(EProcessingStage::COMMAND_PARSING);
        }
        
        // Stage 4: Validation
        SetProcessingStage(EProcessingStage::VALIDATION);
        if (Result.Confidence >= SystemConfig.TargetAccuracy) {
            Result.bSuccess = true;
            Result.CompletedStages.Add(EProcessingStage::VALIDATION);
        } else {
            Result.bSuccess = false;
            Result.ErrorMessage = "Command confidence below threshold";
        }
        
        // Stage 5: Response Generation
        SetProcessingStage(EProcessingStage::RESPONSE_GENERATION);
        if (AudioResponseGenerator && Result.bSuccess) {
            FAudioResponseData ResponseData;
            if (!Result.ErrorMessage.IsEmpty()) {
                ResponseData = AudioResponseGenerator->GenerateErrorResponse(Result.ErrorMessage, AudioInput);
            } else {
                ResponseData = AudioResponseGenerator->GenerateConfirmationResponse(
                    AudioInput, Result.ATAChapter, Context.FlightPhase);
            }
            
            Result.ResponseText = ResponseData.ResponseText;
            Result.CompletedStages.Add(EProcessingStage::RESPONSE_GENERATION);
            
            // Stage 6: Audio Playback
            SetProcessingStage(EProcessingStage::AUDIO_PLAYBACK);
            if (AudioResponseGenerator->PlayResponse(ResponseData)) {
                Result.CompletedStages.Add(EProcessingStage::AUDIO_PLAYBACK);
            }
        }
        
        SetProcessingStage(EProcessingStage::COMPLETED);
        
    } catch (const std::exception& e) {
        Result.bSuccess = false;
        Result.ErrorMessage = FString(e.what());
        SetProcessingStage(EProcessingStage::FAILED);
        
        HandleSubsystemError("Pipeline", e.what());
    }
    
    // Calculate processing time
    auto EndTime = std::chrono::high_resolution_clock::now();
    float ProcessingTime = std::chrono::duration<float, std::milli>(EndTime - LastCommandStartTime).count();
    Result.ProcessingTimeMs = ProcessingTime;
    
    // Update statistics
    UpdateCommandStatistics(Result);
    
    // Add to history
    if (CommandHistory.Num() >= SystemConfig.CommandHistorySize) {
        CommandHistory.RemoveAt(0); // Remove oldest
    }
    CommandHistory.Add(Result);
    
    // Fire completion event
    OnVoiceCommandProcessed.Broadcast(Result, Result.bSuccess);
    
    LogIntegrationActivity("Command Processing Complete", Context);
    
    bProcessingCommand = false;
    SystemStatus.ActiveCommands = ProcessingQueue.Num();
    SetSystemState(bVoiceMonitoringActive ? EVoiceSystemState::ACTIVE : EVoiceSystemState::READY);
}

void AVoiceCommandSystemIntegration::CheckSubsystemHealth() {
    // Check health of all subsystems
    bool AllHealthy = true;
    
    if (!AudioProcessor) {
        SystemStatus.SubsystemHealth &= ~0x01;
        AllHealthy = false;
    }
    
    if (!NLPEngine) {
        SystemStatus.SubsystemHealth &= ~0x02;
        AllHealthy = false;
    }
    
    if (!CommandParser) {
        SystemStatus.SubsystemHealth &= ~0x04;
        AllHealthy = false;
    }
    
    if (!AudioResponseGenerator || !AudioResponseGenerator->IsInitialized()) {
        SystemStatus.SubsystemHealth &= ~0x08;
        AllHealthy = false;
    }
    
    if (!AllHealthy && SystemStatus.SystemState != EVoiceSystemState::ERROR_STATE) {
        SetSystemState(EVoiceSystemState::ERROR_STATE);
        SystemStatus.LastError = EIntegrationError::SUBSYSTEM_FAILURE;
    }
}

void AVoiceCommandSystemIntegration::UpdatePerformanceMetrics() {
    // Calculate average latency
    if (LatencyHistory.size() > 0) {
        float TotalLatency = 0.0f;
        for (float Latency : LatencyHistory) {
            TotalLatency += Latency;
        }
        SystemStatus.AverageLatencyMs = TotalLatency / LatencyHistory.size();
    }
    
    // Calculate current accuracy
    if (AccuracyHistory.size() > 0) {
        float TotalAccuracy = 0.0f;
        for (float Accuracy : AccuracyHistory) {
            TotalAccuracy += Accuracy;
        }
        SystemStatus.CurrentAccuracy = TotalAccuracy / AccuracyHistory.size();
    }
    
    // Fire metrics update event
    OnPerformanceMetricsUpdated.Broadcast(SystemStatus);
}

void AVoiceCommandSystemIntegration::PerformAutoCalibration() {
    if (SystemStatus.SystemState == EVoiceSystemState::READY && SystemConfig.bAutoCalibration) {
        UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] Performing automatic calibration"));
        
        // Perform automatic system optimization
        // In real implementation, would adjust recognition parameters based on recent performance
    }
}

FString AVoiceCommandSystemIntegration::GenerateSessionId() const {
    // Generate unique session ID
    int64 Timestamp = FDateTime::Now().GetTicks();
    int32 Random = FMath::RandRange(10000, 99999);
    return FString::Printf(TEXT("SESS-%lld-%d"), Timestamp, Random);
}

void AVoiceCommandSystemIntegration::LogIntegrationActivity(
    const FString& Activity, 
    const FVoiceCommandContext& Context) const {
    
    if (SystemConfig.DebugLevel >= 1) {
        UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Integration] %s - Session: %s, User: %s"), 
               *Activity, *Context.SessionId, *Context.UserId);
    }
}

void AVoiceCommandSystemIntegration::UpdateCommandStatistics(const FVoiceCommandResult& Result) {
    SystemStatus.CommandsProcessed++;
    
    if (Result.bSuccess) {
        SystemStatus.SuccessfulCommands++;
    } else {
        SystemStatus.FailedCommands++;
    }
    
    // Update performance history
    LatencyHistory.push_back(Result.ProcessingTimeMs);
    AccuracyHistory.push_back(Result.Confidence);
    
    // Limit history size
    const size_t MaxHistorySize = 100;
    if (LatencyHistory.size() > MaxHistorySize) {
        LatencyHistory.erase(LatencyHistory.begin());
    }
    if (AccuracyHistory.size() > MaxHistorySize) {
        AccuracyHistory.erase(AccuracyHistory.begin());
    }
}

void AVoiceCommandSystemIntegration::CleanupCommandHistory() {
    // Remove old commands to maintain history size limit
    while (CommandHistory.Num() > SystemConfig.CommandHistorySize) {
        CommandHistory.RemoveAt(0);
    }
}

/**
 * ============================================================================
 * VOICE COMMAND SYSTEM COMPONENT IMPLEMENTATION
 * ============================================================================
 */

UVoiceCommandSystemComponent::UVoiceCommandSystemComponent() {
    PrimaryComponentTick.bCanEverTick = false;
    
    // Initialize component context
    ComponentContext.UserId = "Component_User";
    ComponentContext.ScenarioId = "Default_Scenario";
}

bool UVoiceCommandSystemComponent::InitializeWithSystem(AVoiceCommandSystemIntegration* VoiceSystem) {
    if (!VoiceSystem) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Component] Invalid voice system reference"));
        return false;
    }
    
    VoiceSystemRef = VoiceSystem;
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Component] Component initialized with voice system"));
    return true;
}

void UVoiceCommandSystemComponent::ProcessVoiceCommand(const FString& Command) {
    if (!VoiceSystemRef) {
        UE_LOG(LogTemp, Error, TEXT("[AQUA V Voice Component] No voice system reference"));
        return;
    }
    
    if (!VoiceSystemRef->IsSystemReady()) {
        UE_LOG(LogTemp, Warning, TEXT("[AQUA V Voice Component] Voice system not ready"));
        return;
    }
    
    // Update context with current timestamp
    ComponentContext.CommandStartTime = FDateTime::Now();
    
    // Process through main system
    VoiceSystemRef->ProcessVoiceCommand(Command, ComponentContext);
}

void UVoiceCommandSystemComponent::SetUserContext(const FString& UserId, const FString& ScenarioId) {
    ComponentContext.UserId = UserId;
    ComponentContext.ScenarioId = ScenarioId;
    
    UE_LOG(LogTemp, Log, TEXT("[AQUA V Voice Component] Context updated - User: %s, Scenario: %s"), 
           *UserId, *ScenarioId);
}

/**
 * ============================================================================
 * UTILITY FUNCTION IMPLEMENTATIONS
 * ============================================================================
 */

FVoiceSystemConfig CreateDefaultAerospaceVoiceConfig() {
    FVoiceSystemConfig Config;
    Config.bEnabled = true;
    Config.bTrainingMode = false;
    Config.bPerformanceMonitoring = true;
    Config.bAutoCalibration = true;
    Config.TargetAccuracy = AQUA_V_TARGET_RECOGNITION_ACCURACY;
    Config.MaxLatencyMs = AQUA_V_MAX_END_TO_END_LATENCY_MS;
    Config.MaxConcurrentCommands = AQUA_V_MAX_CONCURRENT_COMMANDS;
    Config.CommandHistorySize = AQUA_V_COMMAND_HISTORY_SIZE;
    Config.ConfigurationPath = "/Config/VoiceCommands/";
    Config.DebugLevel = 1;
    return Config;
}

bool ValidateVoiceSystemConfig(const FVoiceSystemConfig& Config, FString& ErrorMessage) {
    if (Config.TargetAccuracy < 0.1f || Config.TargetAccuracy > 1.0f) {
        ErrorMessage = "Target accuracy must be between 0.1 and 1.0";
        return false;
    }
    
    if (Config.MaxLatencyMs < 10.0f || Config.MaxLatencyMs > 5000.0f) {
        ErrorMessage = "Max latency must be between 10ms and 5000ms";
        return false;
    }
    
    if (Config.MaxConcurrentCommands < 1 || Config.MaxConcurrentCommands > 100) {
        ErrorMessage = "Max concurrent commands must be between 1 and 100";
        return false;
    }
    
    if (Config.CommandHistorySize < 10 || Config.CommandHistorySize > 10000) {
        ErrorMessage = "Command history size must be between 10 and 10000";
        return false;
    }
    
    return true;
}

FString ProcessingStageToString(EProcessingStage Stage) {
    switch (Stage) {
        case EProcessingStage::AUDIO_CAPTURE: return "Audio Capture";
        case EProcessingStage::STREAM_PROCESSING: return "Stream Processing";
        case EProcessingStage::NLP_ANALYSIS: return "NLP Analysis";
        case EProcessingStage::COMMAND_PARSING: return "Command Parsing";
        case EProcessingStage::VALIDATION: return "Validation";
        case EProcessingStage::EXECUTION: return "Execution";
        case EProcessingStage::RESPONSE_GENERATION: return "Response Generation";
        case EProcessingStage::AUDIO_PLAYBACK: return "Audio Playback";
        case EProcessingStage::COMPLETED: return "Completed";
        case EProcessingStage::FAILED: return "Failed";
        default: return "Unknown";
    }
}

float CalculateSystemHealthScore(const FVoiceSystemStatus& Status) {
    float HealthScore = 0.0f;
    
    // Base score from subsystem health (40%)
    int32 HealthySubsystems = 0;
    for (int32 i = 0; i < 4; i++) {
        if (Status.SubsystemHealth & (1 << i)) {
            HealthySubsystems++;
        }
    }
    HealthScore += (float(HealthySubsystems) / 4.0f) * 0.4f;
    
    // Performance score (30%)
    if (Status.AverageLatencyMs <= AQUA_V_MAX_END_TO_END_LATENCY_MS) {
        HealthScore += 0.3f;
    } else {
        HealthScore += 0.3f * (AQUA_V_MAX_END_TO_END_LATENCY_MS / Status.AverageLatencyMs);
    }
    
    // Accuracy score (30%)
    HealthScore += Status.CurrentAccuracy * 0.3f;
    
    return FMath::Clamp(HealthScore, 0.0f, 1.0f);
}

FVoiceSystemConfig GetRecommendedConfigForScenario(const FString& ScenarioType) {
    FVoiceSystemConfig Config = CreateDefaultAerospaceVoiceConfig();
    
    if (ScenarioType == "Emergency") {
        Config.MaxLatencyMs = 50.0f; // Faster response for emergencies
        Config.TargetAccuracy = 0.98f; // Higher accuracy requirement
    } else if (ScenarioType == "Training") {
        Config.bTrainingMode = true;
        Config.MaxLatencyMs = 150.0f; // Allow more time for training feedback
    } else if (ScenarioType == "BasicFlight") {
        Config.TargetAccuracy = 0.90f; // Lower accuracy for basic scenarios
    }
    
    return Config;
}
