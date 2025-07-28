/*
 * ============================================================================
 * AQUA V. - Voice Command Plugin Integration Example
 * ============================================================================
 * 
 * Project:     AMPEL360 Training VR System
 * Component:   Voice Command Plugin Integration Example
 * File:        AMP-TRAIN-VR001-DES-BOB-EX-DTCEC-396-01-01-VCEXAMPLE-QHPC-v7.6.0.h/.cpp
 * Version:     v7.6.0
 * 
 * Description: Example implementation showing how to integrate the AQUA V.
 *              Voice Command Plugin into your Unreal Engine project
 * 
 * Author:      AQUA V. Development Team
 * Date:        2025-07-28
 * Copyright:   (c) 2025 ROBBBO-T GAIA AIR & SPACE
 * License:     Proprietary - Aerospace Training Use Only
 * 
 * ============================================================================
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"

// Include the AQUA V. Voice Command Plugin
#include "../../../Integration/UnrealEnginePlugins/VoiceCommandPlugin/Source/AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-01-02-VCPLUGIN-QHPC-v7.6.0.h"

#include "AMP-TRAIN-VR001-DES-BOB-EX-DTCEC-396-01-01-VCEXAMPLE-QHPC-v7.6.0.generated.h"

/*
 * ============================================================================
 * EXAMPLE TRAINING AIRCRAFT ACTOR WITH VOICE COMMANDS
 * ============================================================================
 */

/**
 * Example aircraft actor that demonstrates voice command integration
 * This shows how to use the AQUA V. Voice Command Plugin in a real training scenario
 */
UCLASS(BlueprintType, Blueprintable)
class AQUAV_EXAMPLE_API ATrainingAircraftWithVoiceCommands : public AActor
{
    GENERATED_BODY()

public:
    // Constructor
    ATrainingAircraftWithVoiceCommands();

    // UObject Interface
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaTime) override;

    /*
     * ========================================================================
     * VOICE COMMAND INTEGRATION
     * ========================================================================
     */

    /** The Voice Command Plugin Component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Voice Commands")
    UVoiceCommandPluginComponent* VoiceCommandComponent;

    /** Initialize the voice command system */
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void InitializeVoiceCommands();

    /** Start listening for voice commands */
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void StartVoiceListening();

    /** Stop listening for voice commands */
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void StopVoiceListening();

    /*
     * ========================================================================
     * VOICE COMMAND EVENT HANDLERS
     * ========================================================================
     */

    /** Called when voice recognition state changes */
    UFUNCTION(BlueprintImplementableEvent, Category = "Voice Commands")
    void OnVoiceRecognitionStateChanged(EVoiceRecognitionState NewState);

    /** Called when a voice command is executed */
    UFUNCTION(BlueprintImplementableEvent, Category = "Voice Commands")
    void OnVoiceCommandExecuted(const FVoiceCommandData& CommandData, bool bSuccess);

    /** Called when audio quality changes */
    UFUNCTION(BlueprintImplementableEvent, Category = "Voice Commands")
    void OnAudioQualityChanged(const FAudioQualityMetrics& AudioMetrics);

    /*
     * ========================================================================
     * AIRCRAFT CONTROL METHODS (Called by Voice Commands)
     * ========================================================================
     */

    /** Execute a turn maneuver */
    UFUNCTION(BlueprintCallable, Category = "Flight Control")
    void ExecuteTurnManeuver(const FString& Direction, float Degrees);

    /** Execute climb to altitude */
    UFUNCTION(BlueprintCallable, Category = "Flight Control") 
    void ExecuteClimbToAltitude(int32 TargetAltitude);

    /** Execute descent to altitude */
    UFUNCTION(BlueprintCallable, Category = "Flight Control")
    void ExecuteDescentToAltitude(int32 TargetAltitude);

    /** Execute autoland procedure */
    UFUNCTION(BlueprintCallable, Category = "Flight Control")
    void ExecuteAutolandProcedure();

    /** Set radio frequency */
    UFUNCTION(BlueprintCallable, Category = "Communications")
    void SetRadioFrequency(const FString& Frequency);

    /** Contact ATC station */
    UFUNCTION(BlueprintCallable, Category = "Communications")
    void ContactATCStation(const FString& Station);

    /** Set navigation waypoint */
    UFUNCTION(BlueprintCallable, Category = "Navigation")
    void SetNavigationWaypoint(const FString& WaypointName);

    /** Activate quantum system */
    UFUNCTION(BlueprintCallable, Category = "Quantum Systems")
    void ActivateQuantumSystem(const FString& SystemName);

    /** Execute emergency procedure */
    UFUNCTION(BlueprintCallable, Category = "Emergency")
    void ExecuteEmergencyProcedure(const FString& ProcedureName);

    /*
     * ========================================================================
     * AIRCRAFT STATE PROPERTIES
     * ========================================================================
     */

    /** Current aircraft heading */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aircraft State")
    float CurrentHeading;

    /** Current aircraft altitude */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aircraft State")
    int32 CurrentAltitude;

    /** Current radio frequency */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aircraft State")
    FString CurrentRadioFrequency;

    /** Is autoland active */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aircraft State")
    bool bAutolandActive;

    /** Emergency status */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aircraft State")
    bool bEmergencyStatus;

private:
    /*
     * ========================================================================
     * PRIVATE METHODS
     * ========================================================================
     */

    /** Bind voice command events */
    void BindVoiceCommandEvents();

    /** Handle voice command execution */
    UFUNCTION()
    void HandleVoiceCommandExecuted(const FVoiceCommandData& CommandData, bool bSuccess);

    /** Handle state change */
    UFUNCTION()
    void HandleVoiceRecognitionStateChanged(EVoiceRecognitionState NewState);

    /** Handle audio quality change */
    UFUNCTION()
    void HandleAudioQualityChanged(const FAudioQualityMetrics& AudioMetrics);

    /** Process flight control voice commands */
    void ProcessFlightControlCommand(const FVoiceCommandData& CommandData);

    /** Process communication voice commands */
    void ProcessCommunicationCommand(const FVoiceCommandData& CommandData);

    /** Process navigation voice commands */
    void ProcessNavigationCommand(const FVoiceCommandData& CommandData);

    /** Process quantum systems voice commands */
    void ProcessQuantumSystemCommand(const FVoiceCommandData& CommandData);

    /** Process emergency voice commands */
    void ProcessEmergencyCommand(const FVoiceCommandData& CommandData);
};

/*
 * ============================================================================
 * IMPLEMENTATION (.cpp file content)
 * ============================================================================
 */

// ATrainingAircraftWithVoiceCommands.cpp Implementation

ATrainingAircraftWithVoiceCommands::ATrainingAircraftWithVoiceCommands()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create the root component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Create and initialize the Voice Command Component
    VoiceCommandComponent = CreateDefaultSubobject<UVoiceCommandPluginComponent>(TEXT("VoiceCommandComponent"));
    VoiceCommandComponent->SetupAttachment(RootComponent);

    // Initialize aircraft state
    CurrentHeading = 0.0f;
    CurrentAltitude = 10000;
    CurrentRadioFrequency = TEXT("121.500");
    bAutolandActive = false;
    bEmergencyStatus = false;
}

void ATrainingAircraftWithVoiceCommands::BeginPlay()
{
    Super::BeginPlay();

    // Initialize voice commands
    InitializeVoiceCommands();
    
    // Bind events
    BindVoiceCommandEvents();

    UE_LOG(LogTemp, Log, TEXT("Training Aircraft with Voice Commands initialized"));
}

void ATrainingAircraftWithVoiceCommands::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Stop voice recognition
    if (VoiceCommandComponent && VoiceCommandComponent->IsVoiceRecognitionActive())
    {
        VoiceCommandComponent->StopVoiceRecognition();
    }

    Super::EndPlay(EndPlayReason);
}

void ATrainingAircraftWithVoiceCommands::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update aircraft systems based on voice commands
    // This would typically interface with your aircraft simulation systems
}

void ATrainingAircraftWithVoiceCommands::InitializeVoiceCommands()
{
    if (VoiceCommandComponent)
    {
        // Initialize with default configuration
        bool bInitialized = VoiceCommandComponent->InitializeVoiceRecognition();
        
        if (bInitialized)
        {
            UE_LOG(LogTemp, Log, TEXT("Voice command system initialized successfully"));
            
            // Set appropriate confidence threshold for training
            VoiceCommandComponent->SetRecognitionThreshold(0.75f);
            
            // Enable relevant command categories
            VoiceCommandComponent->SetCommandCategoryEnabled(EVoiceCommandCategory::FlightControl, true);
            VoiceCommandComponent->SetCommandCategoryEnabled(EVoiceCommandCategory::Communications, true);
            VoiceCommandComponent->SetCommandCategoryEnabled(EVoiceCommandCategory::Navigation, true);
            VoiceCommandComponent->SetCommandCategoryEnabled(EVoiceCommandCategory::QuantumSystems, true);
            VoiceCommandComponent->SetCommandCategoryEnabled(EVoiceCommandCategory::Emergency, true);
            VoiceCommandComponent->SetCommandCategoryEnabled(EVoiceCommandCategory::Training, true);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to initialize voice command system"));
        }
    }
}

void ATrainingAircraftWithVoiceCommands::StartVoiceListening()
{
    if (VoiceCommandComponent)
    {
        bool bStarted = VoiceCommandComponent->StartVoiceRecognition(true);
        UE_LOG(LogTemp, Log, TEXT("Voice listening %s"), bStarted ? TEXT("started") : TEXT("failed to start"));
    }
}

void ATrainingAircraftWithVoiceCommands::StopVoiceListening()
{
    if (VoiceCommandComponent)
    {
        VoiceCommandComponent->StopVoiceRecognition();
        UE_LOG(LogTemp, Log, TEXT("Voice listening stopped"));
    }
}

void ATrainingAircraftWithVoiceCommands::BindVoiceCommandEvents()
{
    if (VoiceCommandComponent)
    {
        // Bind to voice command events
        VoiceCommandComponent->OnVoiceCommandExecuted.AddDynamic(this, &ATrainingAircraftWithVoiceCommands::HandleVoiceCommandExecuted);
        VoiceCommandComponent->OnVoiceRecognitionStateChanged.AddDynamic(this, &ATrainingAircraftWithVoiceCommands::HandleVoiceRecognitionStateChanged);
        VoiceCommandComponent->OnAudioQualityChanged.AddDynamic(this, &ATrainingAircraftWithVoiceCommands::HandleAudioQualityChanged);
    }
}

void ATrainingAircraftWithVoiceCommands::HandleVoiceCommandExecuted(const FVoiceCommandData& CommandData, bool bSuccess)
{
    UE_LOG(LogTemp, Log, TEXT("Voice command executed: %s (Success: %s)"), 
           *CommandData.CommandText, bSuccess ? TEXT("Yes") : TEXT("No"));

    if (bSuccess)
    {
        // Process the command based on category
        switch (CommandData.Category)
        {
            case EVoiceCommandCategory::FlightControl:
                ProcessFlightControlCommand(CommandData);
                break;
            case EVoiceCommandCategory::Communications:
                ProcessCommunicationCommand(CommandData);
                break;
            case EVoiceCommandCategory::Navigation:
                ProcessNavigationCommand(CommandData);
                break;
            case EVoiceCommandCategory::QuantumSystems:
                ProcessQuantumSystemCommand(CommandData);
                break;
            case EVoiceCommandCategory::Emergency:
                ProcessEmergencyCommand(CommandData);
                break;
            default:
                UE_LOG(LogTemp, Warning, TEXT("Unhandled command category"));
                break;
        }
    }

    // Call Blueprint event
    OnVoiceCommandExecuted(CommandData, bSuccess);
}

void ATrainingAircraftWithVoiceCommands::HandleVoiceRecognitionStateChanged(EVoiceRecognitionState NewState)
{
    UE_LOG(LogTemp, Log, TEXT("Voice recognition state changed to: %s"), 
           *UEnum::GetValueAsString(NewState));

    // Call Blueprint event
    OnVoiceRecognitionStateChanged(NewState);
}

void ATrainingAircraftWithVoiceCommands::HandleAudioQualityChanged(const FAudioQualityMetrics& AudioMetrics)
{
    UE_LOG(LogTemp, Log, TEXT("Audio quality: SNR=%.1f, Clarity=%.1f, Noise=%.1f"), 
           AudioMetrics.SignalToNoiseRatio, AudioMetrics.SpeechClarityIndex, AudioMetrics.BackgroundNoiseLevel);

    // Call Blueprint event
    OnAudioQualityChanged(AudioMetrics);
}

void ATrainingAircraftWithVoiceCommands::ProcessFlightControlCommand(const FVoiceCommandData& CommandData)
{
    // Extract entities and execute appropriate flight control action
    if (CommandData.RecognizedIntent.Contains(TEXT("turn")))
    {
        FString Direction = CommandData.ExtractedEntities.FindRef(TEXT("direction"));
        FString DegreesStr = CommandData.ExtractedEntities.FindRef(TEXT("degrees"));
        float Degrees = FCString::Atof(*DegreesStr);
        
        ExecuteTurnManeuver(Direction, Degrees);
    }
    else if (CommandData.RecognizedIntent.Contains(TEXT("climb")))
    {
        FString AltitudeStr = CommandData.ExtractedEntities.FindRef(TEXT("altitude"));
        int32 Altitude = FCString::Atoi(*AltitudeStr);
        
        ExecuteClimbToAltitude(Altitude);
    }
    else if (CommandData.RecognizedIntent.Contains(TEXT("descend")))
    {
        FString AltitudeStr = CommandData.ExtractedEntities.FindRef(TEXT("altitude"));
        int32 Altitude = FCString::Atoi(*AltitudeStr);
        
        ExecuteDescentToAltitude(Altitude);
    }
    else if (CommandData.RecognizedIntent.Contains(TEXT("autoland")))
    {
        ExecuteAutolandProcedure();
    }
}

void ATrainingAircraftWithVoiceCommands::ProcessCommunicationCommand(const FVoiceCommandData& CommandData)
{
    if (CommandData.RecognizedIntent.Contains(TEXT("frequency")))
    {
        FString Frequency = CommandData.ExtractedEntities.FindRef(TEXT("frequency"));
        SetRadioFrequency(Frequency);
    }
    else if (CommandData.RecognizedIntent.Contains(TEXT("contact")))
    {
        FString Station = CommandData.ExtractedEntities.FindRef(TEXT("station"));
        ContactATCStation(Station);
    }
}

void ATrainingAircraftWithVoiceCommands::ProcessNavigationCommand(const FVoiceCommandData& CommandData)
{
    if (CommandData.RecognizedIntent.Contains(TEXT("waypoint")))
    {
        FString WaypointName = CommandData.ExtractedEntities.FindRef(TEXT("waypoint_name"));
        SetNavigationWaypoint(WaypointName);
    }
}

void ATrainingAircraftWithVoiceCommands::ProcessQuantumSystemCommand(const FVoiceCommandData& CommandData)
{
    if (CommandData.RecognizedIntent.Contains(TEXT("activate")))
    {
        if (CommandData.RecognizedIntent.Contains(TEXT("QNS")))
        {
            ActivateQuantumSystem(TEXT("QNS"));
        }
        else if (CommandData.RecognizedIntent.Contains(TEXT("QPU")))
        {
            ActivateQuantumSystem(TEXT("QPU"));
        }
    }
}

void ATrainingAircraftWithVoiceCommands::ProcessEmergencyCommand(const FVoiceCommandData& CommandData)
{
    ExecuteEmergencyProcedure(CommandData.RecognizedIntent);
    bEmergencyStatus = true;
}

// Aircraft control method implementations
void ATrainingAircraftWithVoiceCommands::ExecuteTurnManeuver(const FString& Direction, float Degrees)
{
    UE_LOG(LogTemp, Log, TEXT("Executing turn: %s %f degrees"), *Direction, Degrees);
    
    if (Direction.Contains(TEXT("left")) || Direction.Contains(TEXT("port")))
    {
        CurrentHeading -= Degrees;
    }
    else if (Direction.Contains(TEXT("right")) || Direction.Contains(TEXT("starboard")))
    {
        CurrentHeading += Degrees;
    }
    
    // Normalize heading
    while (CurrentHeading < 0) CurrentHeading += 360;
    while (CurrentHeading >= 360) CurrentHeading -= 360;
}

void ATrainingAircraftWithVoiceCommands::ExecuteClimbToAltitude(int32 TargetAltitude)
{
    UE_LOG(LogTemp, Log, TEXT("Climbing to altitude: %d feet"), TargetAltitude);
    CurrentAltitude = TargetAltitude;
}

void ATrainingAircraftWithVoiceCommands::ExecuteDescentToAltitude(int32 TargetAltitude)
{
    UE_LOG(LogTemp, Log, TEXT("Descending to altitude: %d feet"), TargetAltitude);
    CurrentAltitude = TargetAltitude;
}

void ATrainingAircraftWithVoiceCommands::ExecuteAutolandProcedure()
{
    UE_LOG(LogTemp, Log, TEXT("Executing autoland procedure"));
    bAutolandActive = true;
}

void ATrainingAircraftWithVoiceCommands::SetRadioFrequency(const FString& Frequency)
{
    UE_LOG(LogTemp, Log, TEXT("Setting radio frequency to: %s"), *Frequency);
    CurrentRadioFrequency = Frequency;
}

void ATrainingAircraftWithVoiceCommands::ContactATCStation(const FString& Station)
{
    UE_LOG(LogTemp, Log, TEXT("Contacting ATC station: %s"), *Station);
}

void ATrainingAircraftWithVoiceCommands::SetNavigationWaypoint(const FString& WaypointName)
{
    UE_LOG(LogTemp, Log, TEXT("Setting navigation waypoint: %s"), *WaypointName);
}

void ATrainingAircraftWithVoiceCommands::ActivateQuantumSystem(const FString& SystemName)
{
    UE_LOG(LogTemp, Log, TEXT("Activating quantum system: %s"), *SystemName);
}

void ATrainingAircraftWithVoiceCommands::ExecuteEmergencyProcedure(const FString& ProcedureName)
{
    UE_LOG(LogTemp, Error, TEXT("EMERGENCY: Executing procedure: %s"), *ProcedureName);
}

/*
 * ============================================================================
 * BLUEPRINT INTEGRATION EXAMPLE
 * ============================================================================
 * 
 * To use this in Blueprints:
 * 
 * 1. Create a Blueprint based on ATrainingAircraftWithVoiceCommands
 * 2. In BeginPlay, call "Initialize Voice Commands" and "Start Voice Listening"
 * 3. Implement the Blueprint events:
 *    - OnVoiceRecognitionStateChanged
 *    - OnVoiceCommandExecuted  
 *    - OnAudioQualityChanged
 * 4. Use the aircraft control functions to update your simulation
 * 
 * Example Blueprint setup:
 * - Event BeginPlay -> Initialize Voice Commands -> Start Voice Listening
 * - Event OnVoiceCommandExecuted -> Branch based on CommandData.Category
 * - Update UI elements based on voice recognition state
 * - Display audio quality indicators
 * 
 * ============================================================================
 */