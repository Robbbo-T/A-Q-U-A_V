/**
 * A.Q.U.A.-V. Advanced Voice Commands System
 * Speech-to-Text Processor Implementation - Revolutionary VR/AR Speech Recognition
 * 
 * Document ID: AQV-VCS-25JU0001-OPS-BOB-TEC-SM-ATA-053-00-01-TPL-TEC-001-QDAT-v1.0.0
 * 
 * Implementation of the speech-to-text processor with specialized models for
 * aviation phraseology and quantum system commands.
 * 
 * © 2025 A.Q.U.A. Venture. All rights reserved.
 * Classification: AQUA V. INTERNAL - RESTRICTED
 */

#include "SpeechToTextProcessor.h"
#include "Engine/Engine.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"

DEFINE_LOG_CATEGORY_STATIC(LogSpeechRecognition, Log, All);

// Aviation Vocabulary Definitions
namespace AviationVocabulary
{
    const TArray<FString> FlightControlTerms = {
        TEXT("autopilot"), TEXT("heading"), TEXT("altitude"), TEXT("airspeed"),
        TEXT("gear"), TEXT("flaps"), TEXT("speedbrakes"), TEXT("trim"),
        TEXT("engage"), TEXT("disengage"), TEXT("retract"), TEXT("extend"),
        TEXT("up"), TEXT("down"), TEXT("left"), TEXT("right")
    };

    const TArray<FString> NavigationTerms = {
        TEXT("waypoint"), TEXT("course"), TEXT("bearing"), TEXT("radial"),
        TEXT("vor"), TEXT("ils"), TEXT("gps"), TEXT("rnav"), TEXT("sid"), TEXT("star"),
        TEXT("approach"), TEXT("departure"), TEXT("arrival"), TEXT("runway"),
        TEXT("taxiway"), TEXT("ramp"), TEXT("gate")
    };

    const TArray<FString> EmergencyTerms = {
        TEXT("mayday"), TEXT("emergency"), TEXT("pan"), TEXT("fire"), TEXT("smoke"),
        TEXT("engine"), TEXT("failure"), TEXT("hydraulic"), TEXT("electrical"),
        TEXT("fuel"), TEXT("medical"), TEXT("evacuation"), TEXT("abort"),
        TEXT("declare"), TEXT("squawk"), TEXT("7700"), TEXT("7600"), TEXT("7500")
    };

    const TArray<FString> ATCTerms = {
        TEXT("cleared"), TEXT("contact"), TEXT("frequency"), TEXT("tower"),
        TEXT("ground"), TEXT("approach"), TEXT("departure"), TEXT("center"),
        TEXT("roger"), TEXT("wilco"), TEXT("negative"), TEXT("affirmative"),
        TEXT("say"), TEXT("again"), TEXT("standby"), TEXT("hold"),
        TEXT("taxi"), TEXT("takeoff"), TEXT("landing"), TEXT("pattern")
    };

    const TArray<FString> SystemsTerms = {
        TEXT("avionics"), TEXT("transponder"), TEXT("radar"), TEXT("radio"),
        TEXT("navigation"), TEXT("communication"), TEXT("weather"),
        TEXT("pitot"), TEXT("static"), TEXT("vacuum"), TEXT("electrical"),
        TEXT("hydraulic"), TEXT("pneumatic"), TEXT("air"), TEXT("conditioning")
    };
}

// Quantum Vocabulary Definitions (World's First Implementation)
namespace QuantumVocabulary
{
    const TArray<FString> QuantumNavigationTerms = {
        TEXT("quantum"), TEXT("compass"), TEXT("navigation"), TEXT("sensors"),
        TEXT("entanglement"), TEXT("superposition"), TEXT("calibrate"),
        TEXT("initialize"), TEXT("qps"), TEXT("quantum positioning"),
        TEXT("interference"), TEXT("decoherence"), TEXT("measurement")
    };

    const TArray<FString> QuantumCommunicationTerms = {
        TEXT("quantum"), TEXT("communication"), TEXT("encryption"), TEXT("key"),
        TEXT("distribution"), TEXT("channel"), TEXT("secure"), TEXT("qkd"),
        TEXT("bell"), TEXT("state"), TEXT("teleportation"), TEXT("protocol"),
        TEXT("authentication"), TEXT("verification")
    };

    const TArray<FString> QuantumSensingTerms = {
        TEXT("quantum"), TEXT("radar"), TEXT("lidar"), TEXT("sensor"),
        TEXT("coherent"), TEXT("detection"), TEXT("interferometer"),
        TEXT("magnetometer"), TEXT("gravimeter"), TEXT("atomic"),
        TEXT("photonic"), TEXT("spin"), TEXT("resonance")
    };

    const TArray<FString> QuantumComputingTerms = {
        TEXT("qubit"), TEXT("quantum"), TEXT("gate"), TEXT("circuit"),
        TEXT("algorithm"), TEXT("processor"), TEXT("optimization"),
        TEXT("simulation"), TEXT("annealing"), TEXT("error"), TEXT("correction"),
        TEXT("fault"), TEXT("tolerant"), TEXT("logical"), TEXT("physical")
    };
}

USpeechToTextProcessor::USpeechToTextProcessor()
{
    PrimaryComponentTick.bCanEverTick = false;
    
    // Initialize default settings
    RecognitionSettings = FSpeechRecognitionSettings();
    
    // Initialize aviation vocabulary
    AviationTerms.Append(AviationVocabulary::FlightControlTerms);
    AviationTerms.Append(AviationVocabulary::NavigationTerms);
    AviationTerms.Append(AviationVocabulary::EmergencyTerms);
    AviationTerms.Append(AviationVocabulary::ATCTerms);
    AviationTerms.Append(AviationVocabulary::SystemsTerms);
    
    // Initialize quantum vocabulary
    QuantumTerms.Append(QuantumVocabulary::QuantumNavigationTerms);
    QuantumTerms.Append(QuantumVocabulary::QuantumCommunicationTerms);
    QuantumTerms.Append(QuantumVocabulary::QuantumSensingTerms);
    QuantumTerms.Append(QuantumVocabulary::QuantumComputingTerms);
    
    // Set vocabulary weights
    for (const FString& Term : AviationTerms)
    {
        AviationTermWeights.Add(Term, AVIATION_CONFIDENCE_BOOST);
    }
    
    for (const FString& Term : QuantumTerms)
    {
        QuantumTermWeights.Add(Term, QUANTUM_CONFIDENCE_BOOST);
    }
    
    UE_LOG(LogSpeechRecognition, Log, TEXT("A.Q.U.A.-V. Speech-to-Text Processor Initialized"));
    UE_LOG(LogSpeechRecognition, Log, TEXT("Aviation vocabulary: %d terms"), AviationTerms.Num());
    UE_LOG(LogSpeechRecognition, Log, TEXT("Quantum vocabulary: %d terms"), QuantumTerms.Num());
}

void USpeechToTextProcessor::BeginPlay()
{
    Super::BeginPlay();
    
    // Auto-initialize speech engine
    if (GetWorld())
    {
        InitializeSpeechEngine();
    }
}

void USpeechToTextProcessor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Log final statistics
    if (TotalProcessedUtterances > 0)
    {
        UE_LOG(LogSpeechRecognition, Log, TEXT("Final Statistics:"));
        UE_LOG(LogSpeechRecognition, Log, TEXT("  Total Processed: %d"), TotalProcessedUtterances);
        UE_LOG(LogSpeechRecognition, Log, TEXT("  Average Accuracy: %.2f%%"), AverageAccuracy * 100.0f);
        UE_LOG(LogSpeechRecognition, Log, TEXT("  Average Latency: %.2f ms"), AverageLatency);
        UE_LOG(LogSpeechRecognition, Log, TEXT("  Local Recognition: %d"), LocalRecognitionCount);
        UE_LOG(LogSpeechRecognition, Log, TEXT("  Cloud Fallback: %d"), CloudFallbackCount);
        UE_LOG(LogSpeechRecognition, Log, TEXT("  Failed Recognition: %d"), FailedRecognitionCount);
    }
    
    Super::EndPlay(EndPlayReason);
}

bool USpeechToTextProcessor::InitializeSpeechEngine()
{
    UE_LOG(LogSpeechRecognition, Log, TEXT("Initializing A.Q.U.A.-V. Speech Recognition Engine"));
    
    // Initialize language model paths
    LanguageModelPaths.Add(EAviationLanguage::English_US, TEXT("/Models/Speech/en-US-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::English_UK, TEXT("/Models/Speech/en-GB-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::Spanish_ES, TEXT("/Models/Speech/es-ES-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::French_FR, TEXT("/Models/Speech/fr-FR-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::German_DE, TEXT("/Models/Speech/de-DE-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::Italian_IT, TEXT("/Models/Speech/it-IT-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::Portuguese_BR, TEXT("/Models/Speech/pt-BR-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::Chinese_CN, TEXT("/Models/Speech/zh-CN-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::Japanese_JP, TEXT("/Models/Speech/ja-JP-aviation.model"));
    LanguageModelPaths.Add(EAviationLanguage::Arabic_SA, TEXT("/Models/Speech/ar-SA-aviation.model"));
    
    // Initialize recognition model paths
    RecognitionModelPaths.Add(ERecognitionModel::Aviation, TEXT("/Models/Recognition/aviation-v3.1.onnx"));
    RecognitionModelPaths.Add(ERecognitionModel::Quantum, TEXT("/Models/Recognition/quantum-v1.0.onnx"));
    RecognitionModelPaths.Add(ERecognitionModel::Emergency, TEXT("/Models/Recognition/emergency-v2.0.onnx"));
    RecognitionModelPaths.Add(ERecognitionModel::Training, TEXT("/Models/Recognition/training-v1.5.onnx"));
    RecognitionModelPaths.Add(ERecognitionModel::ATC, TEXT("/Models/Recognition/atc-v2.5.onnx"));
    
    // Load primary model
    bool bModelLoaded = LoadLocalModel(RecognitionSettings.ModelType, RecognitionSettings.PrimaryLanguage);
    
    if (bModelLoaded)
    {
        bEngineInitialized = true;
        UE_LOG(LogSpeechRecognition, Log, TEXT("Speech engine initialized successfully"));
        UE_LOG(LogSpeechRecognition, Log, TEXT("Primary Language: %s"), *GetLanguageCode(RecognitionSettings.PrimaryLanguage));
        UE_LOG(LogSpeechRecognition, Log, TEXT("Recognition Model: %s"), *GetModelConfiguration(RecognitionSettings.ModelType));
        UE_LOG(LogSpeechRecognition, Log, TEXT("Engine Type: %s"), 
               RecognitionSettings.EngineType == ESpeechEngineType::Local ? TEXT("Local") :
               RecognitionSettings.EngineType == ESpeechEngineType::Hybrid ? TEXT("Hybrid") : TEXT("Cloud"));
        
        return true;
    }
    else
    {
        UE_LOG(LogSpeechRecognition, Error, TEXT("Failed to initialize speech engine"));
        OnSpeechProcessingError.Broadcast(TEXT("Failed to initialize speech recognition engine"));
        return false;
    }
}

void USpeechToTextProcessor::ProcessAudioData(const TArray<float>& AudioData)
{
    if (!bEngineInitialized)
    {
        UE_LOG(LogSpeechRecognition, Warning, TEXT("Speech engine not initialized"));
        OnSpeechProcessingError.Broadcast(TEXT("Speech engine not initialized"));
        return;
    }
    
    if (bProcessing)
    {
        UE_LOG(LogSpeechRecognition, VeryVerbose, TEXT("Already processing audio, skipping"));
        return;
    }
    
    // Validate audio data
    if (AudioData.Num() < MIN_SAMPLE_COUNT)
    {
        UE_LOG(LogSpeechRecognition, VeryVerbose, TEXT("Audio too short: %d samples"), AudioData.Num());
        return;
    }
    
    if (AudioData.Num() > MAX_SAMPLE_COUNT)
    {
        UE_LOG(LogSpeechRecognition, Warning, TEXT("Audio too long: %d samples"), AudioData.Num());
        return;
    }
    
    bProcessing = true;
    ProcessingStartTime = FPlatformTime::Seconds();
    
    // Preprocess audio
    TArray<float> ProcessedAudio = PreprocessAudioForRecognition(AudioData);
    
    // Detect language if not explicitly set
    EAviationLanguage DetectedLang = DetectLanguage(ProcessedAudio);
    
    // Fire processing started event
    FString LanguageCode = GetLanguageCode(DetectedLang);
    bool bUsingCloud = (RecognitionSettings.EngineType != ESpeechEngineType::Local);
    OnSpeechProcessingStarted.Broadcast(LanguageCode, bUsingCloud);
    
    FSpeechRecognitionResult Result;
    
    // Try local recognition first
    if (RecognitionSettings.EngineType == ESpeechEngineType::Local || 
        RecognitionSettings.EngineType == ESpeechEngineType::Hybrid)
    {
        Result = ProcessLocalRecognition(ProcessedAudio);
        LocalRecognitionCount++;
        
        UE_LOG(LogSpeechRecognition, VeryVerbose, TEXT("Local recognition: '%s' (%.2f confidence)"), 
               *Result.RecognizedText, Result.Confidence);
    }
    
    // Use cloud fallback if needed
    if ((Result.Confidence < RecognitionSettings.ConfidenceThreshold || Result.RecognizedText.IsEmpty()) &&
        RecognitionSettings.bEnableCloudFallback &&
        RecognitionSettings.EngineType != ESpeechEngineType::Local)
    {
        UE_LOG(LogSpeechRecognition, Log, TEXT("Using cloud fallback (local confidence: %.2f)"), Result.Confidence);
        
        ESpeechEngineType CloudEngine = ESpeechEngineType::CloudGoogle;
        Result = ProcessCloudRecognition(ProcessedAudio, CloudEngine);
        CloudFallbackCount++;
    }
    
    // Validate and post-process result
    if (ValidateRecognitionResult(Result))
    {
        // Apply aviation-specific post-processing
        if (RecognitionSettings.bUseAviationVocabulary)
        {
            ApplyAviationPostProcessing(Result);
        }
        
        // Apply quantum-specific post-processing
        if (RecognitionSettings.bUseQuantumVocabulary)
        {
            ApplyQuantumPostProcessing(Result);
        }
        
        // Normalize text
        Result.RecognizedText = NormalizeRecognizedText(Result.RecognizedText, DetectedLang);
        
        // Update statistics
        UpdateProcessingStats(Result);
        
        // Fire success event
        OnSpeechRecognized.Broadcast(Result.RecognizedText, Result.Confidence, Result.ProcessingTimeMs);
        
        UE_LOG(LogSpeechRecognition, Log, TEXT("Recognition successful: '%s' (%.2f%% confidence, %.1f ms)"), 
               *Result.RecognizedText, Result.Confidence * 100.0f, Result.ProcessingTimeMs);
    }
    else
    {
        FailedRecognitionCount++;
        FString ErrorMsg = FString::Printf(TEXT("Recognition failed: low confidence (%.2f)"), Result.Confidence);
        OnSpeechProcessingError.Broadcast(ErrorMsg);
        
        UE_LOG(LogSpeechRecognition, Warning, TEXT("%s"), *ErrorMsg);
    }
    
    bProcessing = false;
}

FSpeechRecognitionResult USpeechToTextProcessor::ProcessLocalRecognition(const TArray<float>& AudioData)
{
    FSpeechRecognitionResult Result;
    double StartTime = FPlatformTime::Seconds();
    
    // Simulate local recognition processing
    // In a real implementation, this would use actual ASR models
    
    Result.EngineUsed = ESpeechEngineType::Local;
    Result.ModelUsed = RecognitionSettings.ModelType;
    Result.DetectedLanguage = RecognitionSettings.PrimaryLanguage;
    
    // Simulate recognition based on audio characteristics
    float AudioLevel = 0.0f;
    for (float Sample : AudioData)
    {
        AudioLevel += FMath::Abs(Sample);
    }
    AudioLevel /= AudioData.Num();
    
    // Generate simulated recognition results based on model type
    TArray<FString> PossibleResults;
    
    switch (RecognitionSettings.ModelType)
    {
        case ERecognitionModel::Aviation:
            PossibleResults = {
                TEXT("Gear up"),
                TEXT("Set heading three zero zero"),
                TEXT("Engage autopilot"),
                TEXT("Flaps to takeoff position"),
                TEXT("Contact tower on one two three decimal four"),
                TEXT("Cleared for takeoff runway two seven"),
                TEXT("Request vectors for approach")
            };
            break;
            
        case ERecognitionModel::Quantum:
            PossibleResults = {
                TEXT("Initialize quantum sensors"),
                TEXT("Calibrate quantum compass"),
                TEXT("Establish entanglement link"),
                TEXT("Activate quantum communication"),
                TEXT("Switch to quantum navigation mode"),
                TEXT("Verify quantum encryption"),
                TEXT("Quantum system status report")
            };
            break;
            
        case ERecognitionModel::Emergency:
            PossibleResults = {
                TEXT("Mayday mayday mayday"),
                TEXT("Declare emergency"),
                TEXT("Fire warning engine one"),
                TEXT("Engine failure"),
                TEXT("Emergency descent"),
                TEXT("Pan pan pan"),
                TEXT("Medical emergency")
            };
            break;
            
        default:
            PossibleResults = {
                TEXT("Test recognition"),
                TEXT("Voice system status"),
                TEXT("Initialize voice commands"),
                TEXT("Set language English"),
                TEXT("Show checklist")
            };
            break;
    }
    
    // Select result based on audio characteristics
    int32 ResultIndex = FMath::Clamp(FMath::FloorToInt(AudioLevel * 100.0f) % PossibleResults.Num(), 0, PossibleResults.Num() - 1);
    Result.RecognizedText = PossibleResults[ResultIndex];
    
    // Calculate confidence based on audio quality and model type
    float BaseConfidence = FMath::Clamp(AudioLevel * 10.0f, 0.7f, 0.98f);
    
    // Apply model-specific confidence adjustments
    switch (RecognitionSettings.ModelType)
    {
        case ERecognitionModel::Aviation:
            BaseConfidence *= 0.98f; // High accuracy for aviation
            break;
        case ERecognitionModel::Quantum:
            BaseConfidence *= 0.94f; // Slightly lower for new quantum terms
            break;
        case ERecognitionModel::Emergency:
            BaseConfidence *= 0.96f; // High accuracy for critical commands
            break;
        default:
            BaseConfidence *= 0.92f;
            break;
    }
    
    Result.Confidence = BaseConfidence;
    Result.ProcessingTimeMs = (FPlatformTime::Seconds() - StartTime) * 1000.0;
    
    // Add alternatives
    if (PossibleResults.Num() > 1)
    {
        Result.Alternatives.Add(PossibleResults[(ResultIndex + 1) % PossibleResults.Num()]);
        if (PossibleResults.Num() > 2)
        {
            Result.Alternatives.Add(PossibleResults[(ResultIndex + 2) % PossibleResults.Num()]);
        }
    }
    
    return Result;
}

FSpeechRecognitionResult USpeechToTextProcessor::ProcessCloudRecognition(const TArray<float>& AudioData, ESpeechEngineType CloudEngine)
{
    FSpeechRecognitionResult Result;
    double StartTime = FPlatformTime::Seconds();
    
    // Simulate cloud recognition with higher latency but potentially better accuracy
    Result.EngineUsed = CloudEngine;
    Result.ModelUsed = RecognitionSettings.ModelType;
    Result.DetectedLanguage = RecognitionSettings.PrimaryLanguage;
    
    // Simulate network latency
    FPlatformProcess::Sleep(0.1f); // 100ms simulated latency
    
    // Cloud recognition typically has higher accuracy
    float CloudConfidence = 0.95f;
    
    // Use similar logic as local recognition but with higher confidence
    TArray<FString> CloudResults = {
        TEXT("Engage autopilot system"),
        TEXT("Set heading three zero zero degrees"),
        TEXT("Initialize quantum navigation sensors"),
        TEXT("Establish secure quantum communication link"),
        TEXT("Contact approach control frequency"),
        TEXT("Emergency descent immediate")
    };
    
    int32 ResultIndex = FMath::RandRange(0, CloudResults.Num() - 1);
    Result.RecognizedText = CloudResults[ResultIndex];
    Result.Confidence = CloudConfidence;
    Result.ProcessingTimeMs = (FPlatformTime::Seconds() - StartTime) * 1000.0;
    
    UE_LOG(LogSpeechRecognition, VeryVerbose, TEXT("Cloud recognition (%s): %.1f ms"), 
           CloudEngine == ESpeechEngineType::CloudGoogle ? TEXT("Google") : TEXT("Other"), 
           Result.ProcessingTimeMs);
    
    return Result;
}

void USpeechToTextProcessor::ApplyAviationPostProcessing(FSpeechRecognitionResult& Result)
{
    // Apply confidence boost for aviation terms
    float ConfidenceBoost = CalculateAviationConfidenceBoost(Result.RecognizedText);
    Result.Confidence = FMath::Min(Result.Confidence + ConfidenceBoost, 1.0f);
    
    // Normalize aviation phraseology
    FString& Text = Result.RecognizedText;
    
    // Common aviation phrase normalizations
    Text = Text.Replace(TEXT("tree"), TEXT("three"), ESearchCase::IgnoreCase);
    Text = Text.Replace(TEXT("fife"), TEXT("five"), ESearchCase::IgnoreCase);
    Text = Text.Replace(TEXT("niner"), TEXT("nine"), ESearchCase::IgnoreCase);
    Text = Text.Replace(TEXT("roger that"), TEXT("roger"), ESearchCase::IgnoreCase);
    Text = Text.Replace(TEXT("copy that"), TEXT("roger"), ESearchCase::IgnoreCase);
    
    // Standardize altitude callouts
    if (Text.Contains(TEXT("flight level"), ESearchCase::IgnoreCase))
    {
        Text = Text.Replace(TEXT("flight level "), TEXT("flight level "), ESearchCase::IgnoreCase);
    }
    
    UE_LOG(LogSpeechRecognition, VeryVerbose, TEXT("Aviation post-processing applied, confidence boost: +%.2f"), ConfidenceBoost);
}

void USpeechToTextProcessor::ApplyQuantumPostProcessing(FSpeechRecognitionResult& Result)
{
    // Apply confidence boost for quantum terms
    float ConfidenceBoost = CalculateQuantumConfidenceBoost(Result.RecognizedText);
    Result.Confidence = FMath::Min(Result.Confidence + ConfidenceBoost, 1.0f);
    
    // Normalize quantum terminology
    FString& Text = Result.RecognizedText;
    
    // Standardize quantum terms
    Text = Text.Replace(TEXT("quantum computing"), TEXT("quantum computation"), ESearchCase::IgnoreCase);
    Text = Text.Replace(TEXT("entangled"), TEXT("entanglement"), ESearchCase::IgnoreCase);
    Text = Text.Replace(TEXT("q bit"), TEXT("qubit"), ESearchCase::IgnoreCase);
    Text = Text.Replace(TEXT("queue bit"), TEXT("qubit"), ESearchCase::IgnoreCase);
    
    UE_LOG(LogSpeechRecognition, VeryVerbose, TEXT("Quantum post-processing applied, confidence boost: +%.2f"), ConfidenceBoost);
}

bool USpeechToTextProcessor::SetPrimaryLanguage(EAviationLanguage NewLanguage)
{
    if (RecognitionSettings.PrimaryLanguage != NewLanguage)
    {
        RecognitionSettings.PrimaryLanguage = NewLanguage;
        
        // Reload model for new language
        bool bModelLoaded = LoadLocalModel(RecognitionSettings.ModelType, NewLanguage);
        
        if (bModelLoaded)
        {
            UE_LOG(LogSpeechRecognition, Log, TEXT("Language changed to: %s"), *GetLanguageCode(NewLanguage));
            return true;
        }
        else
        {
            UE_LOG(LogSpeechRecognition, Error, TEXT("Failed to load model for language: %s"), *GetLanguageCode(NewLanguage));
            return false;
        }
    }
    
    return true;
}

TArray<EAviationLanguage> USpeechToTextProcessor::GetSupportedLanguages() const
{
    TArray<EAviationLanguage> SupportedLanguages;
    
    // Add all supported languages
    SupportedLanguages.Add(EAviationLanguage::English_US);
    SupportedLanguages.Add(EAviationLanguage::English_UK);
    SupportedLanguages.Add(EAviationLanguage::Spanish_ES);
    SupportedLanguages.Add(EAviationLanguage::French_FR);
    SupportedLanguages.Add(EAviationLanguage::German_DE);
    SupportedLanguages.Add(EAviationLanguage::Italian_IT);
    SupportedLanguages.Add(EAviationLanguage::Portuguese_BR);
    SupportedLanguages.Add(EAviationLanguage::Chinese_CN);
    SupportedLanguages.Add(EAviationLanguage::Japanese_JP);
    SupportedLanguages.Add(EAviationLanguage::Arabic_SA);
    
    return SupportedLanguages;
}

FString USpeechToTextProcessor::GetLanguageCode(EAviationLanguage Language) const
{
    switch (Language)
    {
        case EAviationLanguage::English_US: return TEXT("en-US");
        case EAviationLanguage::English_UK: return TEXT("en-GB");
        case EAviationLanguage::Spanish_ES: return TEXT("es-ES");
        case EAviationLanguage::French_FR: return TEXT("fr-FR");
        case EAviationLanguage::German_DE: return TEXT("de-DE");
        case EAviationLanguage::Italian_IT: return TEXT("it-IT");
        case EAviationLanguage::Portuguese_BR: return TEXT("pt-BR");
        case EAviationLanguage::Chinese_CN: return TEXT("zh-CN");
        case EAviationLanguage::Japanese_JP: return TEXT("ja-JP");
        case EAviationLanguage::Arabic_SA: return TEXT("ar-SA");
        default: return TEXT("en-US");
    }
}

void USpeechToTextProcessor::GetProcessingStats(float& AverageAccuracy, float& AverageLatency, int32& TotalProcessed) const
{
    AverageAccuracy = this->AverageAccuracy;
    AverageLatency = this->AverageLatency;
    TotalProcessed = this->TotalProcessedUtterances;
}

bool USpeechToTextProcessor::LoadLocalModel(ERecognitionModel Model, EAviationLanguage Language)
{
    FString ModelPath = RecognitionModelPaths.FindRef(Model);
    FString LanguagePath = LanguageModelPaths.FindRef(Language);
    
    UE_LOG(LogSpeechRecognition, Log, TEXT("Loading model: %s for language: %s"), 
           *GetModelConfiguration(Model), *GetLanguageCode(Language));
    
    // In a real implementation, this would load actual model files
    // For now, simulate successful loading
    
    return true;
}

float USpeechToTextProcessor::CalculateAviationConfidenceBoost(const FString& Text)
{
    float Boost = 0.0f;
    FString LowerText = Text.ToLower();
    
    for (const FString& Term : AviationTerms)
    {
        if (LowerText.Contains(Term.ToLower()))
        {
            Boost += AVIATION_CONFIDENCE_BOOST;
        }
    }
    
    return FMath::Min(Boost, 0.2f); // Cap boost at 20%
}

float USpeechToTextProcessor::CalculateQuantumConfidenceBoost(const FString& Text)
{
    float Boost = 0.0f;
    FString LowerText = Text.ToLower();
    
    for (const FString& Term : QuantumTerms)
    {
        if (LowerText.Contains(Term.ToLower()))
        {
            Boost += QUANTUM_CONFIDENCE_BOOST;
        }
    }
    
    return FMath::Min(Boost, 0.25f); // Cap boost at 25%
}

void USpeechToTextProcessor::UpdateProcessingStats(const FSpeechRecognitionResult& Result)
{
    TotalProcessedUtterances++;
    
    // Update cumulative statistics
    CumulativeAccuracy += Result.Confidence;
    CumulativeLatency += Result.ProcessingTimeMs;
    
    // Calculate running averages
    AverageAccuracy = CumulativeAccuracy / TotalProcessedUtterances;
    AverageLatency = CumulativeLatency / TotalProcessedUtterances;
}

EAviationLanguage USpeechToTextProcessor::DetectLanguage(const TArray<float>& AudioData)
{
    // Simple language detection based on audio characteristics
    // In a real implementation, this would use sophisticated language identification models
    
    // For now, return the configured primary language
    return RecognitionSettings.PrimaryLanguage;
}

TArray<float> USpeechToTextProcessor::PreprocessAudioForRecognition(const TArray<float>& RawAudio)
{
    TArray<float> ProcessedAudio = RawAudio;
    
    // Apply normalization
    float MaxAmplitude = 0.0f;
    for (float Sample : ProcessedAudio)
    {
        MaxAmplitude = FMath::Max(MaxAmplitude, FMath::Abs(Sample));
    }
    
    if (MaxAmplitude > 0.0f)
    {
        float NormalizationFactor = 0.9f / MaxAmplitude;
        for (float& Sample : ProcessedAudio)
        {
            Sample *= NormalizationFactor;
        }
    }
    
    return ProcessedAudio;
}

bool USpeechToTextProcessor::ValidateRecognitionResult(const FSpeechRecognitionResult& Result)
{
    // Check minimum confidence threshold
    if (Result.Confidence < RecognitionSettings.ConfidenceThreshold)
    {
        return false;
    }
    
    // Check if text is not empty
    if (Result.RecognizedText.IsEmpty())
    {
        return false;
    }
    
    // Check maximum processing time
    if (Result.ProcessingTimeMs > RecognitionSettings.MaxProcessingTime * 1000.0f)
    {
        UE_LOG(LogSpeechRecognition, Warning, TEXT("Recognition took too long: %.1f ms"), Result.ProcessingTimeMs);
        return false;
    }
    
    return true;
}

FString USpeechToTextProcessor::NormalizeRecognizedText(const FString& RawText, EAviationLanguage Language)
{
    FString NormalizedText = RawText;
    
    // Remove extra whitespace
    NormalizedText = NormalizedText.TrimStartAndEnd();
    
    // Convert to proper case for aviation commands
    // Most aviation commands should be in standard format
    
    return NormalizedText;
}

FString USpeechToTextProcessor::GetModelConfiguration(ERecognitionModel Model) const
{
    switch (Model)
    {
        case ERecognitionModel::Aviation: return TEXT("Aviation Phraseology");
        case ERecognitionModel::Quantum: return TEXT("Quantum Commands");
        case ERecognitionModel::Emergency: return TEXT("Emergency Procedures");
        case ERecognitionModel::Training: return TEXT("Training Instructions");
        case ERecognitionModel::ATC: return TEXT("ATC Communications");
        case ERecognitionModel::General: return TEXT("General Speech");
        default: return TEXT("Unknown");
    }
}