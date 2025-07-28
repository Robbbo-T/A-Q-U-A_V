/**
 * ============================================================================
 * AQUA V. - Voice Command System Integration Engine
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
 * Description: Master integration engine that orchestrates all voice command components
 *              Provides unified interface for voice recognition, command parsing, and audio response
 *              Designed for complete aerospace training simulation integration
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
 * Integration Standards:
 * - Real-time Processing: <100ms end-to-end latency
 * - Reliability: 99.9% uptime for training sessions
 * - Accuracy: >95% command recognition accuracy
 * - Safety: Full compliance with aviation safety standards
 * - Scalability: Support for multiple concurrent training sessions
 * 
 * Author:      AQUA V. Development Team - QDAT Division
 * Date:        2025-07-28
 * Copyright:   (c) 2025 ROBBBO-T GAIA AIR & SPACE
 * License:     Proprietary - Aerospace Training Use Only
 * 
 * ============================================================================
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Components/ActorComponent.h"

// Include all voice command subsystem headers
#include "../AudioStreamProcessor/AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-341-50-01-TPL-TEC-ASPR-001-QDAT-v0.1.0.h"
#include "../NLPEngine/AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-320-50-01-TPL-TEC-NLPN-001-QDAT-v0.1.0.h"
#include "../CommandParsing/AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-343-50-01-TPL-TEC-CMDP-001-QDAT-v0.1.0.h"
#include "../AudioResponse/AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-344-50-01-TPL-TEC-ARESP-001-QDAT-v0.1.0.h"

#include <memory>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <chrono>

// Generated include
#include "AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-345-50-01-TPL-TEC-INTEG-001-QDAT-v0.1.0.generated.h"

namespace AQUA_V {
namespace VoiceCommands {
namespace Integration {

/**
 * ============================================================================
 * CONSTANTS AND CONFIGURATION
 * ============================================================================
 */

// Performance constants
constexpr float AQUA_V_MAX_END_TO_END_LATENCY_MS = 100.0f;
constexpr float AQUA_V_TARGET_RECOGNITION_ACCURACY = 0.95f;
constexpr float AQUA_V_SYSTEM_UPTIME_REQUIREMENT = 0.999f;
constexpr int32 AQUA_V_MAX_CONCURRENT_COMMANDS = 10;
constexpr int32 AQUA_V_COMMAND_HISTORY_SIZE = 100;

// Integration timing constants
constexpr float AQUA_V_SUBSYSTEM_HEALTH_CHECK_INTERVAL = 5.0f;
constexpr float AQUA_V_PERFORMANCE_MONITOR_INTERVAL = 1.0f;
constexpr float AQUA_V_AUTO_CALIBRATION_INTERVAL = 300.0f; // 5 minutes

/**
 * ============================================================================
 * ENUMERATIONS
 * ============================================================================
 */

/** Overall system state for voice command integration */
UENUM(BlueprintType)
enum class EVoiceSystemState : uint8 {
    UNINITIALIZED       UMETA(DisplayName = "Uninitialized"),
    INITIALIZING        UMETA(DisplayName = "Initializing"),
    READY               UMETA(DisplayName = "Ready"),
    ACTIVE              UMETA(DisplayName = "Active"),
    PROCESSING          UMETA(DisplayName = "Processing"),
    ERROR_STATE         UMETA(DisplayName = "Error"),
    MAINTENANCE_MODE    UMETA(DisplayName = "Maintenance"),
    SHUTDOWN            UMETA(DisplayName = "Shutdown")
};

/** Voice command processing pipeline stages */
UENUM(BlueprintType)
enum class EProcessingStage : uint8 {
    AUDIO_CAPTURE       UMETA(DisplayName = "Audio Capture"),
    STREAM_PROCESSING   UMETA(DisplayName = "Stream Processing"),
    NLP_ANALYSIS        UMETA(DisplayName = "NLP Analysis"),
    COMMAND_PARSING     UMETA(DisplayName = "Command Parsing"),
    VALIDATION          UMETA(DisplayName = "Validation"),
    EXECUTION           UMETA(DisplayName = "Execution"),
    RESPONSE_GENERATION UMETA(DisplayName = "Response Generation"),
    AUDIO_PLAYBACK      UMETA(DisplayName = "Audio Playback"),
    COMPLETED           UMETA(DisplayName = "Completed"),
    FAILED              UMETA(DisplayName = "Failed")
};

/** Integration error types */
UENUM(BlueprintType)
enum class EIntegrationError : uint8 {
    NONE                    UMETA(DisplayName = "No Error"),
    SUBSYSTEM_FAILURE       UMETA(DisplayName = "Subsystem Failure"),
    COMMUNICATION_ERROR     UMETA(DisplayName = "Communication Error"),
    PERFORMANCE_DEGRADATION UMETA(DisplayName = "Performance Degradation"),
    CONFIGURATION_ERROR     UMETA(DisplayName = "Configuration Error"),
    RESOURCE_EXHAUSTION     UMETA(DisplayName = "Resource Exhaustion"),
    SECURITY_VIOLATION      UMETA(DisplayName = "Security Violation"),
    UNKNOWN_ERROR           UMETA(DisplayName = "Unknown Error")
};

/**
 * ============================================================================
 * STRUCTURE DEFINITIONS
 * ============================================================================
 */

/** Configuration for the complete voice command system */
USTRUCT(BlueprintType)
struct AQUA_V_API FVoiceSystemConfig {
    GENERATED_BODY()

    /** Enable voice command system */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
    bool bEnabled = true;

    /** Enable training mode with additional feedback */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training")
    bool bTrainingMode = false;

    /** Enable performance monitoring */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    bool bPerformanceMonitoring = true;

    /** Enable automatic calibration */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration")
    bool bAutoCalibration = true;

    /** Target recognition accuracy (0.0 - 1.0) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float TargetAccuracy = AQUA_V_TARGET_RECOGNITION_ACCURACY;

    /** Maximum end-to-end latency in milliseconds */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float MaxLatencyMs = AQUA_V_MAX_END_TO_END_LATENCY_MS;

    /** Maximum concurrent commands */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    int32 MaxConcurrentCommands = AQUA_V_MAX_CONCURRENT_COMMANDS;

    /** Command history size for learning */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learning")
    int32 CommandHistorySize = AQUA_V_COMMAND_HISTORY_SIZE;

    /** Configuration file path */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FString ConfigurationPath = "/Config/VoiceCommands/";

    /** Debug logging level (0=None, 1=Basic, 2=Verbose, 3=All) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    int32 DebugLevel = 1;

    FVoiceSystemConfig() {}
};

/** Comprehensive status information for the voice system */
USTRUCT(BlueprintType)
struct AQUA_V_API FVoiceSystemStatus {
    GENERATED_BODY()

    /** Current system state */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    EVoiceSystemState SystemState = EVoiceSystemState::UNINITIALIZED;

    /** Current processing stage */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing")
    EProcessingStage CurrentStage = EProcessingStage::AUDIO_CAPTURE;

    /** Last error encountered */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Error")
    EIntegrationError LastError = EIntegrationError::NONE;

    /** System uptime in seconds */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float UptimeSeconds = 0.0f;

    /** Average end-to-end latency in milliseconds */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float AverageLatencyMs = 0.0f;

    /** Current recognition accuracy (0.0 - 1.0) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float CurrentAccuracy = 0.0f;

    /** Number of commands processed in current session */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
    int32 CommandsProcessed = 0;

    /** Number of successful commands */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
    int32 SuccessfulCommands = 0;

    /** Number of failed commands */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
    int32 FailedCommands = 0;

    /** Currently active commands */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing")
    int32 ActiveCommands = 0;

    /** Subsystem health status (bitmask) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    int32 SubsystemHealth = 0;

    /** Last error message */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Error")
    FString LastErrorMessage;

    /** System initialization time */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
    FDateTime InitializationTime;

    FVoiceSystemStatus() {
        InitializationTime = FDateTime::Now();
    }
};

/** Voice command processing context */
USTRUCT(BlueprintType)
struct AQUA_V_API FVoiceCommandContext {
    GENERATED_BODY()

    /** Unique command session ID */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identification")
    FString SessionId;

    /** User/pilot ID */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User")
    FString UserId;

    /** Training scenario ID */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training")
    FString ScenarioId;

    /** Aircraft configuration */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aircraft")
    FString AircraftType;

    /** Current flight phase */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
    FString FlightPhase;

    /** Weather conditions */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
    FString WeatherConditions;

    /** Airport/location information */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
    FString AirportCode;

    /** Training difficulty level */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training")
    int32 DifficultyLevel = 1;

    /** Command start timestamp */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timing")
    FDateTime CommandStartTime;

    /** Additional context data */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context")
    TMap<FString, FString> AdditionalData;

    FVoiceCommandContext() {
        CommandStartTime = FDateTime::Now();
    }
};

/** Complete command processing result */
USTRUCT(BlueprintType)
struct AQUA_V_API FVoiceCommandResult {
    GENERATED_BODY()

    /** Command processing context */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context")
    FVoiceCommandContext Context;

    /** Original audio input text */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    FString OriginalText;

    /** Processed command action */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command")
    FString CommandAction;

    /** Command parameters */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
    TMap<FString, FString> Parameters;

    /** Recognition confidence (0.0 - 1.0) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality")
    float Confidence = 0.0f;

    /** Processing success flag */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result")
    bool bSuccess = false;

    /** Processing stages completed */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Processing")
    TArray<EProcessingStage> CompletedStages;

    /** Total processing time in milliseconds */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float ProcessingTimeMs = 0.0f;

    /** Error information (if failed) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Error")
    FString ErrorMessage;

    /** Response audio generated */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Response")
    FString ResponseText;

    /** ATA chapter classification */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classification")
    FString ATAChapter;

    FVoiceCommandResult() {}
};

/**
 * ============================================================================
 * DELEGATE DECLARATIONS
 * ============================================================================
 */

/** Delegate for voice command processing completion */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVoiceCommandProcessed, const FVoiceCommandResult&, Result, bool, bSuccess);

/** Delegate for system state changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVoiceSystemStateChanged, EVoiceSystemState, OldState, EVoiceSystemState, NewState);

/** Delegate for integration errors */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVoiceSystemError, EIntegrationError, ErrorType, const FString&, ErrorMessage, const FVoiceCommandContext&, Context);

/** Delegate for performance metrics updates */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerformanceMetricsUpdated, const FVoiceSystemStatus&, Status);

/**
 * ============================================================================
 * MAIN VOICE SYSTEM INTEGRATION CLASS
 * ============================================================================
 */

/**
 * Voice Command System Integration Engine
 * Master orchestrator for all voice command subsystems in aerospace training
 */
UCLASS(BlueprintType, Blueprintable, Category = "AQUA V|Voice Commands|Integration")
class AQUA_V_API AVoiceCommandSystemIntegration : public AActor {
    GENERATED_BODY()

public:
    /**
     * ========================================================================
     * CONSTRUCTOR AND INITIALIZATION
     * ========================================================================
     */

    AVoiceCommandSystemIntegration();
    virtual ~AVoiceCommandSystemIntegration() override;

    /** Actor lifecycle overrides */
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaTime) override;

    /** Initialize the complete voice command system */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Initialization")
    bool InitializeVoiceSystem(const FVoiceSystemConfig& Config);

    /** Shutdown the voice command system */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Initialization")
    void ShutdownVoiceSystem();

    /** Check if the system is fully initialized and ready */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Status")
    bool IsSystemReady() const;

    /**
     * ========================================================================
     * VOICE COMMAND PROCESSING
     * ========================================================================
     */

    /** Process voice command from start to finish */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Processing")
    void ProcessVoiceCommand(
        const FString& AudioInput,
        const FVoiceCommandContext& Context
    );

    /** Start continuous voice monitoring */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Processing")
    bool StartVoiceMonitoring();

    /** Stop continuous voice monitoring */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Processing")
    void StopVoiceMonitoring();

    /** Check if voice monitoring is active */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Status")
    bool IsVoiceMonitoringActive() const;

    /** Manually trigger voice recognition */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Processing")
    bool TriggerVoiceRecognition();

    /** Cancel current voice command processing */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Processing")
    void CancelCurrentCommand();

    /**
     * ========================================================================
     * SYSTEM STATUS AND MONITORING
     * ========================================================================
     */

    /** Get comprehensive system status */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Status")
    FVoiceSystemStatus GetSystemStatus() const;

    /** Get current system state */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Status")
    EVoiceSystemState GetSystemState() const;

    /** Get current processing stage */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Status")
    EProcessingStage GetCurrentProcessingStage() const;

    /** Get subsystem health status */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Health")
    bool IsSubsystemHealthy(int32 SubsystemMask) const;

    /** Get performance metrics */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Performance")
    void GetPerformanceMetrics(float& AverageLatency, float& Accuracy, int32& CommandsProcessed) const;

    /**
     * ========================================================================
     * CONFIGURATION AND CALIBRATION
     * ========================================================================
     */

    /** Update system configuration */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Configuration")
    void UpdateConfiguration(const FVoiceSystemConfig& NewConfig);

    /** Get current system configuration */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Configuration")
    FVoiceSystemConfig GetConfiguration() const;

    /** Calibrate voice recognition for current user */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Calibration")
    bool CalibrateVoiceRecognition(const FString& UserId);

    /** Run system self-test */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Testing")
    bool RunSystemSelfTest();

    /** Reset system to default settings */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Configuration")
    void ResetToDefaults();

    /**
     * ========================================================================
     * TRAINING AND LEARNING
     * ========================================================================
     */

    /** Enable/disable training mode */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Training")
    void SetTrainingMode(bool bEnabled);

    /** Add training command for learning */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Training")
    void AddTrainingCommand(const FString& Command, const FString& ExpectedAction);

    /** Get command history for analysis */
    UFUNCTION(BlueprintPure, Category = "AQUA V|Voice System|Analytics")
    TArray<FVoiceCommandResult> GetCommandHistory() const;

    /** Clear command history */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Analytics")
    void ClearCommandHistory();

    /**
     * ========================================================================
     * EVENT DELEGATES
     * ========================================================================
     */

    /** Event fired when voice command processing is complete */
    UPROPERTY(BlueprintAssignable, Category = "AQUA V|Voice System|Events")
    FOnVoiceCommandProcessed OnVoiceCommandProcessed;

    /** Event fired when system state changes */
    UPROPERTY(BlueprintAssignable, Category = "AQUA V|Voice System|Events")
    FOnVoiceSystemStateChanged OnVoiceSystemStateChanged;

    /** Event fired on system errors */
    UPROPERTY(BlueprintAssignable, Category = "AQUA V|Voice System|Events")
    FOnVoiceSystemError OnVoiceSystemError;

    /** Event fired when performance metrics are updated */
    UPROPERTY(BlueprintAssignable, Category = "AQUA V|Voice System|Events")
    FOnPerformanceMetricsUpdated OnPerformanceMetricsUpdated;

protected:
    /**
     * ========================================================================
     * PROTECTED MEMBER VARIABLES
     * ========================================================================
     */

    /** System configuration */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FVoiceSystemConfig SystemConfig;

    /** Current system status */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
    FVoiceSystemStatus SystemStatus;

    /** Command processing queue */
    UPROPERTY()
    TArray<FVoiceCommandContext> ProcessingQueue;

    /** Command history for analytics */
    UPROPERTY()
    TArray<FVoiceCommandResult> CommandHistory;

    /** Timer handles for system monitoring */
    FTimerHandle HealthCheckTimer;
    FTimerHandle PerformanceMonitorTimer;
    FTimerHandle CalibrationTimer;

private:
    /**
     * ========================================================================
     * PRIVATE MEMBER VARIABLES
     * ========================================================================
     */

    /** Subsystem component instances */
    std::unique_ptr<AQUA_V::VoiceCommands::AudioProcessor::AudioStreamProcessor> AudioProcessor;
    std::unique_ptr<AQUA_V::VoiceCommands::NLP::NaturalLanguageProcessor> NLPEngine;
    std::unique_ptr<AQUA_V::VoiceCommands::Parser::CommandParser> CommandParser;
    
    /** Audio response generator component */
    UPROPERTY()
    TObjectPtr<UAudioResponseGenerator> AudioResponseGenerator;

    /** Current processing context */
    FVoiceCommandContext CurrentContext;

    /** Performance tracking */
    std::chrono::high_resolution_clock::time_point LastCommandStartTime;
    std::vector<float> LatencyHistory;
    std::vector<float> AccuracyHistory;

    /** System flags */
    bool bSystemInitialized = false;
    bool bVoiceMonitoringActive = false;
    bool bProcessingCommand = false;

    /**
     * ========================================================================
     * PRIVATE METHODS
     * ========================================================================
     */

    /** Initialize all subsystems */
    bool InitializeSubsystems();

    /** Shutdown all subsystems */
    void ShutdownSubsystems();

    /** Set system state with event notification */
    void SetSystemState(EVoiceSystemState NewState);

    /** Set current processing stage */
    void SetProcessingStage(EProcessingStage NewStage);

    /** Handle subsystem errors */
    void HandleSubsystemError(const FString& SubsystemName, const FString& ErrorMessage);

    /** Process command through complete pipeline */
    void ProcessCommandPipeline(const FVoiceCommandContext& Context, const FString& AudioInput);

    /** Monitor subsystem health */
    UFUNCTION()
    void CheckSubsystemHealth();

    /** Monitor performance metrics */
    UFUNCTION()
    void UpdatePerformanceMetrics();

    /** Perform automatic calibration */
    UFUNCTION()
    void PerformAutoCalibration();

    /** Generate unique session ID */
    FString GenerateSessionId() const;

    /** Log integration activity */
    void LogIntegrationActivity(const FString& Activity, const FVoiceCommandContext& Context) const;

    /** Update command statistics */
    void UpdateCommandStatistics(const FVoiceCommandResult& Result);

    /** Clean up old command history */
    void CleanupCommandHistory();
};

/**
 * ============================================================================
 * UTILITY COMPONENT CLASS
 * ============================================================================
 */

/**
 * Voice Command System Component
 * Simplified component interface for easy integration with other actors
 */
UCLASS(BlueprintType, Blueprintable, Category = "AQUA V|Voice Commands|Components")
class AQUA_V_API UVoiceCommandSystemComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UVoiceCommandSystemComponent();

    /** Initialize component with system reference */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice Component")
    bool InitializeWithSystem(AVoiceCommandSystemIntegration* VoiceSystem);

    /** Process voice command through the system */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice Component")
    void ProcessVoiceCommand(const FString& Command);

    /** Set user context for commands */
    UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice Component")
    void SetUserContext(const FString& UserId, const FString& ScenarioId);

protected:
    /** Reference to the main voice system */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
    TObjectPtr<AVoiceCommandSystemIntegration> VoiceSystemRef;

    /** Component-specific context */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context")
    FVoiceCommandContext ComponentContext;
};

/**
 * ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================
 */

/** Create default voice system configuration for aerospace training */
UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Utilities")
FVoiceSystemConfig CreateDefaultAerospaceVoiceConfig();

/** Validate voice system configuration */
UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Utilities")
bool ValidateVoiceSystemConfig(const FVoiceSystemConfig& Config, FString& ErrorMessage);

/** Convert processing stage to display string */
UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Utilities")
FString ProcessingStageToString(EProcessingStage Stage);

/** Calculate system health score */
UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Utilities")
float CalculateSystemHealthScore(const FVoiceSystemStatus& Status);

/** Get recommended configuration for training scenario */
UFUNCTION(BlueprintCallable, Category = "AQUA V|Voice System|Utilities")
FVoiceSystemConfig GetRecommendedConfigForScenario(const FString& ScenarioType);

} // namespace Integration
} // namespace VoiceCommands
} // namespace AQUA_V
