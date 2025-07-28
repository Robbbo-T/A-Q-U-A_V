/*
 * ============================================================================
 * AQUA V. - Voice Command Plugin Header
 * ============================================================================
 * 
 * Project:     AMPEL360 Training VR System
 * Component:   Voice Command Plugin for Unreal Engine
 * File:        AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-01-02-VCPLUGIN-QHPC-v7.6.0.h
 * Version:     v7.6.0
 * 
 * Description: Main header file for the AQUA V. Voice Command Plugin
 *              Provides voice recognition and natural language processing
 *              capabilities for aerospace training simulations in Unreal Engine
 * 
 * Nomenclature Breakdown:
 * - AMP-TRAIN-VR001: AMPEL360 Training VR System 001
 * - DES: Design Phase
 * - BOB: Build-Operate-Build (Digital System)
 * - TEC-SM: Technical Software Module
 * - DTCEC-351: Digital Twin Command Engine Component 351
 * - QHPC: Quantum High Performance Computing Division
 * 
 * Dependencies:
 * - Unreal Engine 5.0+
 * - Core Voice Recognition Engine (DTCEC-341)
 * - Audio Processing Systems (DTCEC-345)
 * - Command Registry (ACV-771)
 * 
 * Compliance:
 * - EASA CS-25 Voice Command Systems
 * - FAA Part 25 Human Factors
 * - DO-178C Software Considerations
 * 
 * Author:      AQUA V. Development Team
 * Date:        2025-07-28
 * Copyright:   (c) 2025 ROBBBO-T GAIA AIR & SPACE
 * License:     Proprietary - Aerospace Training Use Only
 * 
 * ============================================================================
 */

#pragma once

// Unreal Engine Core Includes
#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Framework/Commands/Commands.h"
#include "Modules/ModuleManager.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

// Audio Processing Includes
#include "Sound/SoundWave.h"
#include "AudioDevice.h"
#include "AudioCaptureCore.h"

// Threading and Async Support
#include "Async/TaskGraphInterfaces.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

// JSON and Configuration Support
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

// Plugin API Macros
#include "VoiceCommandPlugin.generated.h"

// Forward Declarations
class UAudioComponent;
class USoundCue;
class FVoiceRecognitionEngine;
class FNaturalLanguageProcessor;
class FCommandParser;
class FResponseGenerator;

/*
 * ============================================================================
 * CORE ENUMERATIONS AND STRUCTURES
 * ============================================================================
 */

/**
 * Voice Recognition States for the AQUA V. system
 * Following aerospace operational state standards
 */
UENUM(BlueprintType)
enum class EVoiceRecognitionState : uint8
{
    Inactive        UMETA(DisplayName = "Inactive"),
    Initializing    UMETA(DisplayName = "Initializing"),
    Listening       UMETA(DisplayName = "Listening"),
    Processing      UMETA(DisplayName = "Processing"),
    Executing       UMETA(DisplayName = "Executing"),
    Responding      UMETA(DisplayName = "Responding"),
    Error          UMETA(DisplayName = "Error"),
    Maintenance    UMETA(DisplayName = "Maintenance")
};

/**
 * Command Priority Levels for Aerospace Operations
 * Critical safety commands have highest priority
 */
UENUM(BlueprintType)
enum class ECommandPriority : uint8
{
    Emergency      UMETA(DisplayName = "Emergency"),      // Immediate execution required
    Critical       UMETA(DisplayName = "Critical"),       // High priority flight operations
    Normal         UMETA(DisplayName = "Normal"),         // Standard operations
    Training       UMETA(DisplayName = "Training"),       // Training mode commands
    Informational  UMETA(DisplayName = "Informational")   // System status queries
};

/**
 * Voice Command Categories based on ATA Chapters
 * Organized according to aerospace system classifications
 */
UENUM(BlueprintType)
enum class EVoiceCommandCategory : uint8
{
    FlightControl       UMETA(DisplayName = "Flight Control"),        // ATA 27
    Communications      UMETA(DisplayName = "Communications"),       // ATA 23
    Navigation          UMETA(DisplayName = "Navigation"),           // ATA 34
    SystemsManagement   UMETA(DisplayName = "Systems Management"),   // Multiple ATA
    QuantumSystems      UMETA(DisplayName = "Quantum Systems"),      // QCSAA 934-936
    Environmental       UMETA(DisplayName = "Environmental"),        // ATA 21
    Emergency          UMETA(DisplayName = "Emergency"),            // ATA 25
    Training           UMETA(DisplayName = "Training"),             // ACV 778
    Maintenance        UMETA(DisplayName = "Maintenance")           // ATA 05
};

/**
 * Audio Quality Metrics for Voice Recognition
 * Ensures compliance with aerospace audio standards
 */
USTRUCT(BlueprintType)
struct VOICECOMMANDPLUGIN_API FAudioQualityMetrics
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Audio Quality")
    float SignalToNoiseRatio;

    UPROPERTY(BlueprintReadOnly, Category = "Audio Quality")
    float SpeechClarityIndex;

    UPROPERTY(BlueprintReadOnly, Category = "Audio Quality")
    float BackgroundNoiseLevel;

    UPROPERTY(BlueprintReadOnly, Category = "Audio Quality")
    float VoiceActivityDetection;

    UPROPERTY(BlueprintReadOnly, Category = "Audio Quality")
    bool bIsWithinSpecifications;

    FAudioQualityMetrics()
        : SignalToNoiseRatio(0.0f)
        , SpeechClarityIndex(0.0f)
        , BackgroundNoiseLevel(0.0f)
        , VoiceActivityDetection(0.0f)
        , bIsWithinSpecifications(false)
    {}
};

/**
 * Voice Command Data Structure
 * Contains all information for a recognized voice command
 */
USTRUCT(BlueprintType)
struct VOICECOMMANDPLUGIN_API FVoiceCommandData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    FString CommandText;

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    FString RecognizedIntent;

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    TMap<FString, FString> ExtractedEntities;

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    EVoiceCommandCategory Category;

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    ECommandPriority Priority;

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    float ConfidenceScore;

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    FDateTime Timestamp;

    UPROPERTY(BlueprintReadOnly, Category = "Command Data")
    FAudioQualityMetrics AudioMetrics;

    FVoiceCommandData()
        : CommandText("")
        , RecognizedIntent("")
        , Category(EVoiceCommandCategory::Training)
        , Priority(ECommandPriority::Normal)
        , ConfidenceScore(0.0f)
        , Timestamp(FDateTime::Now())
    {}
};

/*
 * ============================================================================
 * DELEGATE DECLARATIONS
 * ============================================================================
 */

// Single-cast delegates for internal system communication
DECLARE_DELEGATE_OneParam(FOnVoiceRecognitionStarted, const FString&);
DECLARE_DELEGATE_TwoParams(FOnVoiceCommandRecognized, const FVoiceCommandData&, bool);
DECLARE_DELEGATE_OneParam(FOnVoiceRecognitionError, const FString&);
DECLARE_DELEGATE_OneParam(FOnVoiceResponseGenerated, const FString&);

// Multi-cast delegates for Blueprint and external system integration
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoiceRecognitionStateChanged, EVoiceRecognitionState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVoiceCommandExecuted, const FVoiceCommandData&, CommandData, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioQualityChanged, const FAudioQualityMetrics&, AudioMetrics);

/*
 * ============================================================================
 * MAIN VOICE COMMAND PLUGIN CLASS
 * ============================================================================
 */

/**
 * Main Voice Command Plugin Component for AQUA V. Training System
 * 
 * This component integrates with Unreal Engine to provide:
 * - Real-time voice recognition
 * - Natural language processing
 * - Command parsing and validation
 * - Response generation and TTS
 * - Integration with aerospace training scenarios
 * 
 * Designed for aerospace training compliance and safety standards
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup=(AQUA_V), meta=(BlueprintSpawnableComponent))
class VOICECOMMANDPLUGIN_API UVoiceCommandPluginComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    // Constructor and Destructor
    UVoiceCommandPluginComponent();
    virtual ~UVoiceCommandPluginComponent();

    // UObject Interface
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /*
     * ========================================================================
     * PUBLIC INTERFACE METHODS
     * ========================================================================
     */

    /**
     * Initialize the voice recognition system with configuration
     * @param ConfigurationPath Path to system configuration file
     * @return True if initialization successful, false otherwise
     */
    UFUNCTION(BlueprintCallable, Category = "AQUA V. Voice Commands")
    bool InitializeVoiceRecognition(const FString& ConfigurationPath = TEXT(""));

    /**
     * Start voice recognition listening mode
     * @param bContinuousMode If true, keeps listening continuously
     * @return True if started successfully
     */
    UFUNCTION(BlueprintCallable, Category = "AQUA V. Voice Commands")
    bool StartVoiceRecognition(bool bContinuousMode = true);

    /**
     * Stop voice recognition
     */
    UFUNCTION(BlueprintCallable, Category = "AQUA V. Voice Commands")
    void StopVoiceRecognition();

    /**
     * Process a text command directly (bypass voice recognition)
     * @param CommandText The command text to process
     * @return True if command was processed successfully
     */
    UFUNCTION(BlueprintCallable, Category = "AQUA V. Voice Commands")
    bool ProcessTextCommand(const FString& CommandText);

    /**
     * Get current voice recognition state
     * @return Current state of the voice recognition system
     */
    UFUNCTION(BlueprintPure, Category = "AQUA V. Voice Commands")
    EVoiceRecognitionState GetVoiceRecognitionState() const;

    /**
     * Get last audio quality metrics
     * @return Audio quality metrics from last processing cycle
     */
    UFUNCTION(BlueprintPure, Category = "AQUA V. Voice Commands")
    FAudioQualityMetrics GetAudioQualityMetrics() const;

    /**
     * Check if voice recognition is currently active
     * @return True if voice recognition is listening or processing
     */
    UFUNCTION(BlueprintPure, Category = "AQUA V. Voice Commands")
    bool IsVoiceRecognitionActive() const;

    /**
     * Set voice recognition sensitivity threshold
     * @param Threshold Value between 0.0 and 1.0
     */
    UFUNCTION(BlueprintCallable, Category = "AQUA V. Voice Commands")
    void SetRecognitionThreshold(float Threshold);

    /**
     * Enable or disable specific command categories
     * @param Category The command category to modify
     * @param bEnabled Whether the category should be enabled
     */
    UFUNCTION(BlueprintCallable, Category = "AQUA V. Voice Commands")
    void SetCommandCategoryEnabled(EVoiceCommandCategory Category, bool bEnabled);

    /**
     * Get available command categories and their status
     * @return Map of categories and their enabled status
     */
    UFUNCTION(BlueprintPure, Category = "AQUA V. Voice Commands")
    TMap<EVoiceCommandCategory, bool> GetAvailableCommandCategories() const;

    /*
     * ========================================================================
     * BLUEPRINT EVENTS AND DELEGATES
     * ========================================================================
     */

    /** Called when voice recognition state changes */
    UPROPERTY(BlueprintAssignable, Category = "AQUA V. Voice Commands")
    FOnVoiceRecognitionStateChanged OnVoiceRecognitionStateChanged;

    /** Called when a voice command is successfully executed */
    UPROPERTY(BlueprintAssignable, Category = "AQUA V. Voice Commands")
    FOnVoiceCommandExecuted OnVoiceCommandExecuted;

    /** Called when audio quality metrics change significantly */
    UPROPERTY(BlueprintAssignable, Category = "AQUA V. Voice Commands")
    FOnAudioQualityChanged OnAudioQualityChanged;

    /*
     * ========================================================================
     * CONFIGURATION PROPERTIES
     * ========================================================================
     */

    /** Enable debug logging for voice recognition */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    bool bEnableDebugLogging;

    /** Minimum confidence score required for command execution */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float MinimumConfidenceThreshold;

    /** Maximum audio processing latency in milliseconds */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (ClampMin = "50", ClampMax = "500"))
    int32 MaxProcessingLatencyMs;

    /** Default language model for voice recognition */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FString DefaultLanguageModel;

    /** Audio input device name (empty for default) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FString AudioInputDevice;

    /** Enable Text-to-Speech response generation */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    bool bEnableTextToSpeech;

    /** Voice profile for TTS responses */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
    FString TTSVoiceProfile;

private:
    /*
     * ========================================================================
     * PRIVATE MEMBER VARIABLES
     * ========================================================================
     */

    /** Current state of the voice recognition system */
    EVoiceRecognitionState CurrentState;

    /** Voice recognition engine instance */
    TSharedPtr<FVoiceRecognitionEngine> VoiceRecognitionEngine;

    /** Natural language processing engine */
    TSharedPtr<FNaturalLanguageProcessor> NLPEngine;

    /** Command parser for syntax analysis */
    TSharedPtr<FCommandParser> CommandParser;

    /** Response generator for TTS output */
    TSharedPtr<FResponseGenerator> ResponseGenerator;

    /** Audio capture component */
    UPROPERTY()
    UAudioComponent* AudioCaptureComponent;

    /** Current audio quality metrics */
    FAudioQualityMetrics CurrentAudioMetrics;

    /** Map of enabled command categories */
    TMap<EVoiceCommandCategory, bool> EnabledCommandCategories;

    /** Configuration data loaded from JSON */
    TSharedPtr<FJsonObject> ConfigurationData;

    /** Background processing thread */
    TSharedPtr<FRunnableThread> ProcessingThread;

    /** Thread-safe command queue */
    TQueue<FVoiceCommandData> CommandQueue;

    /** Critical section for thread safety */
    FCriticalSection AudioProcessingCriticalSection;

    /*
     * ========================================================================
     * PRIVATE METHODS
     * ========================================================================
     */

    /** Load configuration from file or defaults */
    bool LoadConfiguration(const FString& ConfigPath);

    /** Initialize audio processing subsystems */
    bool InitializeAudioSystems();

    /** Set the current voice recognition state */
    void SetVoiceRecognitionState(EVoiceRecognitionState NewState);

    /** Process audio data from capture buffer */
    void ProcessAudioData(const TArray<float>& AudioBuffer);

    /** Execute a validated voice command */
    bool ExecuteVoiceCommand(const FVoiceCommandData& CommandData);

    /** Update audio quality metrics */
    void UpdateAudioQualityMetrics(const TArray<float>& AudioBuffer);

    /** Handle system errors and recovery */
    void HandleSystemError(const FString& ErrorMessage);

    /** Cleanup resources on shutdown */
    void CleanupResources();

    /*
     * ========================================================================
     * CALLBACK METHODS
     * ========================================================================
     */

    /** Called when voice recognition starts */
    void OnVoiceRecognitionStarted(const FString& SessionInfo);

    /** Called when speech-to-text conversion completes */
    void OnSpeechRecognitionComplete(const FString& RecognizedText, float Confidence);

    /** Called when NLP processing completes */
    void OnNLPProcessingComplete(const FString& Intent, const TMap<FString, FString>& Entities);

    /** Called when command parsing completes */
    void OnCommandParsingComplete(const FVoiceCommandData& ParsedCommand, bool bIsValid);

    /** Called when TTS response is generated */
    void OnResponseGenerated(const FString& ResponseText, USoundWave* ResponseAudio);

    /*
     * ========================================================================
     * COMMAND EXECUTION METHODS
     * ========================================================================
     */

    /** Execute flight control commands (ATA 27) */
    bool ExecuteFlightControlCommand(const FVoiceCommandData& CommandData);

    /** Execute communication commands (ATA 23) */
    bool ExecuteCommunicationCommand(const FVoiceCommandData& CommandData);

    /** Execute navigation commands (ATA 34) */
    bool ExecuteNavigationCommand(const FVoiceCommandData& CommandData);

    /** Execute systems management commands */
    bool ExecuteSystemsCommand(const FVoiceCommandData& CommandData);

    /** Execute quantum systems commands (QCSAA 934-936) */
    bool ExecuteQuantumCommand(const FVoiceCommandData& CommandData);

    /** Execute emergency procedure commands (ATA 25) */
    bool ExecuteEmergencyCommand(const FVoiceCommandData& CommandData);

    /** Execute training scenario commands (ACV 778) */
    bool ExecuteTrainingCommand(const FVoiceCommandData& CommandData);
};

/*
 * ============================================================================
 * PLUGIN MODULE CLASS
 * ============================================================================
 */

/**
 * Main module class for the AQUA V. Voice Command Plugin
 * Handles plugin lifecycle and integration with Unreal Engine
 */
class VOICECOMMANDPLUGIN_API FVoiceCommandPluginModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    /** Get the singleton instance of this module */
    static FVoiceCommandPluginModule& Get();

    /** Check if the module is loaded and ready */
    static bool IsAvailable();

private:
    /** Initialize plugin-wide resources */
    void InitializePluginResources();

    /** Cleanup plugin-wide resources */
    void CleanupPluginResources();

    /** Register voice command categories with the system */
    void RegisterCommandCategories();

    /** Load plugin configuration and settings */
    void LoadPluginConfiguration();
};

/*
 * ============================================================================
 * UTILITY MACROS AND CONSTANTS
 * ============================================================================
 */

// Plugin identification
#define VOICE_COMMAND_PLUGIN_VERSION TEXT("7.6.0")
#define VOICE_COMMAND_PLUGIN_NAME TEXT("AQUA V. Voice Command Plugin")

// Audio processing constants
#define VOICE_SAMPLE_RATE 48000
#define VOICE_CHANNELS 1
#define VOICE_BUFFER_SIZE 1024
#define VOICE_MIN_SNR_DB 10.0f

// Recognition thresholds
#define MIN_CONFIDENCE_THRESHOLD 0.6f
#define MAX_PROCESSING_TIME_MS 300
#define VOICE_ACTIVITY_THRESHOLD 0.3f

// Command categories bit flags for efficient processing
#define VOICE_CATEGORY_FLIGHT_CONTROL    (1 << 0)
#define VOICE_CATEGORY_COMMUNICATIONS    (1 << 1)
#define VOICE_CATEGORY_NAVIGATION        (1 << 2)
#define VOICE_CATEGORY_SYSTEMS           (1 << 3)
#define VOICE_CATEGORY_QUANTUM           (1 << 4)
#define VOICE_CATEGORY_ENVIRONMENTAL     (1 << 5)
#define VOICE_CATEGORY_EMERGENCY         (1 << 6)
#define VOICE_CATEGORY_TRAINING          (1 << 7)
#define VOICE_CATEGORY_MAINTENANCE       (1 << 8)

/*
 * ============================================================================
 * END OF HEADER FILE
 * ============================================================================
 * 
 * This header file provides the complete interface for the AQUA V. Voice
 * Command Plugin, designed for aerospace training applications in Unreal Engine.
 * 
 * The implementation follows:
 * - Unreal Engine coding standards
 * - Aerospace software development practices (DO-178C)
 * - AQUA V. nomenclature and documentation standards
 * - Thread-safe design patterns for real-time audio processing
 * - Comprehensive error handling and recovery mechanisms
 * 
 * For implementation details, see the corresponding .cpp file:
 * AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-01-01-VCPLUGIN-QHPC-v7.6.0.cpp
 * 
 * ============================================================================
 */
