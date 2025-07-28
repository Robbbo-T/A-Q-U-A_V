/**
 * A.Q.U.A.-V. Advanced Voice Commands System
 * Command Parser - Revolutionary VR/AR Speech Recognition
 * 
 * Document ID: AQV-VCS-25JU0001-OPS-BOB-TEC-SM-ATA-053-00-01-TPL-TEC-001-QDAT-v1.0.0
 * 
 * This component parses recognized text into executable commands for aircraft systems,
 * quantum navigation, and training scenarios with ICAO phraseology compliance.
 * 
 * © 2025 A.Q.U.A. Venture. All rights reserved.
 * Classification: AQUA V. INTERNAL - RESTRICTED
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Engine.h"
#include "CommandParser.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCommandParsed, const FString&, CommandType, const FString&, CommandParameters, float, Confidence);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuantumCommandDetected, const FString&, QuantumCommand, const FString&, Parameters);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEmergencyCommandDetected, const FString&, EmergencyType, const FString&, Details);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCommandParsingError, const FString&, ErrorMessage);

/**
 * Command Categories for Aviation Systems
 */
UENUM(BlueprintType)
enum class ECommandCategory : uint8
{
    FlightControl       UMETA(DisplayName = "Flight Control"),
    Navigation          UMETA(DisplayName = "Navigation"),
    Communication       UMETA(DisplayName = "Communication"),
    SystemsManagement   UMETA(DisplayName = "Systems Management"),
    Emergency           UMETA(DisplayName = "Emergency"),
    Training            UMETA(DisplayName = "Training"),
    QuantumNavigation   UMETA(DisplayName = "Quantum Navigation"),
    QuantumCommunication UMETA(DisplayName = "Quantum Communication"),
    QuantumSensing      UMETA(DisplayName = "Quantum Sensing"),
    Unknown             UMETA(DisplayName = "Unknown")
};

/**
 * Command Priority Levels
 */
UENUM(BlueprintType)
enum class ECommandPriority : uint8
{
    Emergency       UMETA(DisplayName = "Emergency (Immediate)"),
    Critical        UMETA(DisplayName = "Critical (High)"),
    Normal          UMETA(DisplayName = "Normal (Medium)"),
    Information     UMETA(DisplayName = "Information (Low)")
};

/**
 * Parsed Command Structure
 */
USTRUCT(BlueprintType)
struct VOICECOMMANDS_API FParsedCommand
{
    GENERATED_BODY()

    // Command category
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    ECommandCategory Category = ECommandCategory::Unknown;

    // Command type (e.g., "SET_HEADING", "GEAR_UP", "QUANTUM_INIT")
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    FString CommandType;

    // Primary action verb
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    FString Action;

    // Target system or object
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    FString Target;

    // Command parameters (values, settings, etc.)
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    TMap<FString, FString> Parameters;

    // Numerical values extracted from command
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    TMap<FString, float> NumericValues;

    // Command priority
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    ECommandPriority Priority = ECommandPriority::Normal;

    // Parsing confidence (0.0-1.0)
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    float Confidence = 0.0f;

    // Original recognized text
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    FString OriginalText;

    // Whether command requires confirmation
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    bool bRequiresConfirmation = false;

    // Whether this is a quantum command (unique feature)
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    bool bIsQuantumCommand = false;

    // Timestamp when command was parsed
    UPROPERTY(BlueprintReadOnly, Category = "Parsed Command")
    FDateTime ParsedTimestamp;

    FParsedCommand()
    {
        Category = ECommandCategory::Unknown;
        CommandType = TEXT("");
        Action = TEXT("");
        Target = TEXT("");
        Priority = ECommandPriority::Normal;
        Confidence = 0.0f;
        OriginalText = TEXT("");
        bRequiresConfirmation = false;
        bIsQuantumCommand = false;
        ParsedTimestamp = FDateTime::Now();
    }
};

/**
 * Grammar Rule for Command Parsing
 */
USTRUCT(BlueprintType)
struct VOICECOMMANDS_API FGrammarRule
{
    GENERATED_BODY()

    // Rule name/identifier
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    FString RuleName;

    // Command pattern (regex-like)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    FString Pattern;

    // Keywords that must be present
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    TArray<FString> RequiredKeywords;

    // Optional keywords
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    TArray<FString> OptionalKeywords;

    // Command category this rule produces
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    ECommandCategory Category = ECommandCategory::Unknown;

    // Command type this rule produces
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    FString CommandType;

    // Priority of commands matching this rule
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    ECommandPriority Priority = ECommandPriority::Normal;

    // Rule confidence weight
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grammar Rule")
    float Weight = 1.0f;

    FGrammarRule()
    {
        RuleName = TEXT("");
        Pattern = TEXT("");
        Category = ECommandCategory::Unknown;
        CommandType = TEXT("");
        Priority = ECommandPriority::Normal;
        Weight = 1.0f;
    }
};

/**
 * Command Parser for A.Q.U.A.-V. Voice Commands System
 * 
 * Features:
 * - ICAO phraseology parsing
 * - Quantum command recognition (world's first)
 * - Emergency command prioritization
 * - Multi-language support
 * - Context-aware parsing
 * - Ambiguity resolution
 */
UCLASS(ClassGroup=(VoiceCommands), meta=(BlueprintSpawnableComponent))
class VOICECOMMANDS_API UCommandParser : public UActorComponent
{
    GENERATED_BODY()

public:
    UCommandParser();

protected:
    virtual void BeginPlay() override;

public:
    // Initialize command parser with grammar rules
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    bool InitializeParser();

    // Parse recognized text into command
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    FParsedCommand ParseCommand(const FString& RecognizedText, float RecognitionConfidence = 1.0f);

    // Add custom grammar rule
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    void AddGrammarRule(const FGrammarRule& Rule);

    // Load grammar rules from file
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    bool LoadGrammarRules(const FString& GrammarFilePath);

    // Get all supported command types
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    TArray<FString> GetSupportedCommandTypes() const;

    // Get command examples for category
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    TArray<FString> GetCommandExamples(ECommandCategory Category) const;

    // Validate parsed command
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    bool ValidateCommand(const FParsedCommand& Command) const;

    // Get parsing statistics
    UFUNCTION(BlueprintCallable, Category = "Command Parser")
    void GetParsingStats(int32& TotalParsed, int32& SuccessfulParsed, float& AverageConfidence) const;

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Command Parser")
    FOnCommandParsed OnCommandParsed;

    UPROPERTY(BlueprintAssignable, Category = "Command Parser")
    FOnQuantumCommandDetected OnQuantumCommandDetected;

    UPROPERTY(BlueprintAssignable, Category = "Command Parser")
    FOnEmergencyCommandDetected OnEmergencyCommandDetected;

    UPROPERTY(BlueprintAssignable, Category = "Command Parser")
    FOnCommandParsingError OnCommandParsingError;

protected:
    // Parse flight control commands
    FParsedCommand ParseFlightControlCommand(const FString& Text) const;

    // Parse navigation commands
    FParsedCommand ParseNavigationCommand(const FString& Text) const;

    // Parse quantum commands (unique feature)
    FParsedCommand ParseQuantumCommand(const FString& Text) const;

    // Parse emergency commands
    FParsedCommand ParseEmergencyCommand(const FString& Text) const;

    // Parse training commands
    FParsedCommand ParseTrainingCommand(const FString& Text) const;

    // Extract numerical values from text
    TMap<FString, float> ExtractNumericalValues(const FString& Text) const;

    // Normalize text for parsing
    FString NormalizeTextForParsing(const FString& Text) const;

    // Calculate command confidence based on grammar rules
    float CalculateCommandConfidence(const FString& Text, const FGrammarRule& Rule) const;

    // Resolve ambiguous commands
    FParsedCommand ResolveAmbiguity(const TArray<FParsedCommand>& CandidateCommands) const;

    // Check if text contains keywords
    bool ContainsKeywords(const FString& Text, const TArray<FString>& Keywords) const;

    // Apply ICAO phraseology rules
    FParsedCommand ApplyICAOPhraseology(const FParsedCommand& Command) const;

    // Convert spoken numbers to numeric values
    float ConvertSpokenNumber(const FString& SpokenNumber) const;

    // Parse heading values
    float ParseHeading(const FString& Text) const;

    // Parse altitude values
    float ParseAltitude(const FString& Text) const;

    // Parse speed values
    float ParseSpeed(const FString& Text) const;

    // Parse frequency values
    float ParseFrequency(const FString& Text) const;

private:
    // Grammar rules database
    UPROPERTY(EditAnywhere, Category = "Grammar")
    TArray<FGrammarRule> GrammarRules;

    // Command templates for each category
    TMap<ECommandCategory, TArray<FString>> CommandTemplates;

    // Parsing statistics
    int32 TotalCommandsParsed = 0;
    int32 SuccessfullyParsed = 0;
    float CumulativeConfidence = 0.0f;

    // Constants for parsing
    static constexpr float MIN_CONFIDENCE_THRESHOLD = 0.6f;
    static constexpr float QUANTUM_COMMAND_BOOST = 0.1f;
    static constexpr float EMERGENCY_COMMAND_BOOST = 0.15f;
    static constexpr float ICAO_PHRASEOLOGY_BOOST = 0.05f;
};

/**
 * Utility functions for command parsing
 */
namespace CommandParsingUtils
{
    // Convert command category to string
    FString CommandCategoryToString(ECommandCategory Category);
    
    // Convert command priority to string
    FString CommandPriorityToString(ECommandPriority Priority);
    
    // Check if command is critical
    bool IsCommandCritical(const FParsedCommand& Command);
    
    // Get required confirmation message
    FString GetConfirmationMessage(const FParsedCommand& Command);
    
    // Format command for display
    FString FormatCommandForDisplay(const FParsedCommand& Command);
}