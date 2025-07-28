/**
 * AQUA V. Speech Recognition Engine - Header
 * AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-01-02-SPEECHRECOG-QDAT-v7.6.0.h
 * 
 * Advanced speech-to-text processing engine for aerospace voice commands
 * Optimized for real-time recognition with aerospace terminology
 * 
 * @author AQUA V. Corporation
 * @version 7.6.0
 * @date July 2025
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>

// Forward declarations
class AudioStreamProcessor;
class WaveformAnalyzer;
class LanguageModel;

/**
 * Speech recognition states for aerospace operations
 */
enum class ESpeechRecognitionState : uint8_t
{
    Idle = 0,           // System ready, not actively listening
    Listening,          // Actively capturing audio
    Processing,         // Converting speech to text
    Completed,          // Recognition complete
    Error,              // Recognition failed
    Calibrating,        // Audio calibration in progress
    EmergencyMode       // High-priority emergency recognition
};

/**
 * Audio quality metrics for aerospace compliance
 */
struct FAudioQualityMetrics
{
    float SignalToNoiseRatio = 0.0f;    // SNR in dB
    float BackgroundNoiseLevel = 0.0f;   // Background noise in dB
    float SpeechClarity = 0.0f;          // Speech clarity percentage
    float VoiceActivityLevel = 0.0f;     // Voice activity detection level
    bool IsAerospaceCompliant = false;   // Meets aerospace audio standards
    
    FAudioQualityMetrics() = default;
};

/**
 * Recognition result with confidence and metadata
 */
struct FSpeechRecognitionResult
{
    std::string RecognizedText;          // Recognized speech text
    float ConfidenceScore = 0.0f;        // Recognition confidence (0.0-1.0)
    std::vector<std::string> Alternatives; // Alternative interpretations
    FAudioQualityMetrics AudioMetrics;   // Audio quality data
    double ProcessingTimeMs = 0.0;       // Time taken for recognition
    bool IsEmergencyCommand = false;     // Emergency command flag
    
    FSpeechRecognitionResult() = default;
};

/**
 * Configuration for speech recognition engine
 */
struct FSpeechRecognitionConfig
{
    // Audio Settings
    uint32_t SampleRate = 48000;         // Audio sample rate (Hz)
    uint16_t BitsPerSample = 16;         // Audio bit depth
    uint8_t Channels = 1;                // Mono audio
    uint32_t BufferSizeMs = 100;         // Audio buffer size in milliseconds
    
    // Recognition Settings
    float ConfidenceThreshold = 0.8f;    // Minimum confidence for acceptance
    float NoiseThreshold = -30.0f;       // Background noise threshold (dB)
    uint32_t MaxRecognitionTimeMs = 5000; // Maximum recognition time
    bool EnableContinuousRecognition = true; // Continuous vs command mode
    
    // Aerospace Specific
    bool EnableAerospaceVocabulary = true; // Use aerospace terminology
    bool EnableEmergencyPriority = true;   // Priority for emergency commands
    std::string AerospaceLanguageCode = "en-US-aerospace"; // Language variant
    
    FSpeechRecognitionConfig() = default;
};

/**
 * Delegate for speech recognition events
 */
using FSpeechRecognitionDelegate = std::function<void(const FSpeechRecognitionResult&)>;
using FAudioQualityDelegate = std::function<void(const FAudioQualityMetrics&)>;
using FRecognitionStateDelegate = std::function<void(ESpeechRecognitionState, ESpeechRecognitionState)>;

/**
 * Main Speech Recognition Engine Class
 * Handles real-time speech-to-text conversion for aerospace applications
 */
class AQUA_V_API USpeechRecognitionEngine
{
public:
    USpeechRecognitionEngine();
    virtual ~USpeechRecognitionEngine();

    // === Core Recognition Functions ===
    
    /**
     * Initialize the speech recognition engine
     * @param Config Configuration parameters
     * @return True if initialization successful
     */
    bool Initialize(const FSpeechRecognitionConfig& Config);
    
    /**
     * Start continuous speech recognition
     * @return True if started successfully
     */
    bool StartRecognition();
    
    /**
     * Stop speech recognition
     */
    void StopRecognition();
    
    /**
     * Process single audio command
     * @param AudioData Raw audio data
     * @param DataSize Size of audio data in bytes
     * @return Recognition result
     */
    FSpeechRecognitionResult ProcessAudioCommand(const uint8_t* AudioData, size_t DataSize);
    
    /**
     * Set recognition language model
     * @param ModelPath Path to language model file
     * @return True if model loaded successfully
     */
    bool SetLanguageModel(const std::string& ModelPath);
    
    // === State Management ===
    
    /**
     * Get current recognition state
     */
    ESpeechRecognitionState GetCurrentState() const { return CurrentState.load(); }
    
    /**
     * Check if engine is actively listening
     */
    bool IsListening() const { return CurrentState.load() == ESpeechRecognitionState::Listening; }
    
    /**
     * Enable/disable emergency mode (high priority processing)
     */
    void SetEmergencyMode(bool bEnabled);
    
    // === Audio Quality Management ===
    
    /**
     * Get current audio quality metrics
     */
    FAudioQualityMetrics GetAudioQualityMetrics() const;
    
    /**
     * Calibrate audio input for current environment
     * @param CalibrationTimeMs Duration of calibration in milliseconds
     * @return True if calibration successful
     */
    bool CalibrateAudioInput(uint32_t CalibrationTimeMs = 3000);
    
    /**
     * Set audio quality thresholds
     * @param MinSNR Minimum signal-to-noise ratio
     * @param MaxBackgroundNoise Maximum background noise level
     */
    void SetAudioQualityThresholds(float MinSNR, float MaxBackgroundNoise);
    
    // === Vocabulary Management ===
    
    /**
     * Add aerospace-specific vocabulary
     * @param VocabularyTerms List of aerospace terms
     * @return True if vocabulary added successfully
     */
    bool AddAerospaceVocabulary(const std::vector<std::string>& VocabularyTerms);
    
    /**
     * Load emergency command vocabulary
     * @param EmergencyTerms Emergency command terms
     * @return True if loaded successfully
     */
    bool LoadEmergencyVocabulary(const std::vector<std::string>& EmergencyTerms);
    
    // === Delegate Management ===
    
    /**
     * Set recognition result delegate
     */
    void SetRecognitionDelegate(FSpeechRecognitionDelegate InDelegate) 
    { 
        RecognitionDelegate = InDelegate; 
    }
    
    /**
     * Set audio quality monitoring delegate
     */
    void SetAudioQualityDelegate(FAudioQualityDelegate InDelegate) 
    { 
        AudioQualityDelegate = InDelegate; 
    }
    
    /**
     * Set state change delegate
     */
    void SetStateChangeDelegate(FRecognitionStateDelegate InDelegate) 
    { 
        StateChangeDelegate = InDelegate; 
    }
    
    // === Performance Monitoring ===
    
    /**
     * Get recognition performance statistics
     */
    struct FPerformanceStats
    {
        uint32_t TotalRecognitions = 0;
        uint32_t SuccessfulRecognitions = 0;
        float AverageProcessingTime = 0.0f;
        float AverageConfidence = 0.0f;
        uint32_t EmergencyCommandsProcessed = 0;
    };
    
    FPerformanceStats GetPerformanceStatistics() const;
    
    /**
     * Reset performance statistics
     */
    void ResetPerformanceStatistics();

protected:
    // === Internal Processing ===
    
    /**
     * Audio processing thread function
     */
    void AudioProcessingThread();
    
    /**
     * Recognition processing thread function
     */
    void RecognitionProcessingThread();
    
    /**
     * Update recognition state
     */
    void SetRecognitionState(ESpeechRecognitionState NewState);
    
    /**
     * Process raw audio data
     */
    void ProcessRawAudioData(const uint8_t* AudioData, size_t DataSize);
    
    /**
     * Execute recognition on preprocessed audio
     */
    FSpeechRecognitionResult ExecuteRecognition(const std::vector<float>& AudioSamples);

private:
    // === Configuration ===
    FSpeechRecognitionConfig Configuration;
    
    // === State Management ===
    std::atomic<ESpeechRecognitionState> CurrentState;
    std::atomic<bool> bIsEmergencyMode;
    std::atomic<bool> bShouldStop;
    
    // === Audio Processing ===
    std::unique_ptr<AudioStreamProcessor> AudioProcessor;
    std::unique_ptr<WaveformAnalyzer> WaveformAnalyzer;
    std::unique_ptr<LanguageModel> CurrentLanguageModel;
    
    // === Threading ===
    std::thread AudioThread;
    std::thread RecognitionThread;
    std::mutex AudioDataMutex;
    std::mutex StateMutex;
    
    // === Audio Data Queue ===
    std::queue<std::vector<uint8_t>> AudioDataQueue;
    std::mutex AudioQueueMutex;
    
    // === Delegates ===
    FSpeechRecognitionDelegate RecognitionDelegate;
    FAudioQualityDelegate AudioQualityDelegate;
    FRecognitionStateDelegate StateChangeDelegate;
    
    // === Performance Monitoring ===
    mutable std::mutex PerformanceMutex;
    FPerformanceStats PerformanceStatistics;
    
    // === Audio Quality ===
    FAudioQualityMetrics CurrentAudioMetrics;
    float MinimumSNR = 15.0f;
    float MaximumBackgroundNoise = -20.0f;
    
    // === Vocabulary ===
    std::vector<std::string> AerospaceVocabulary;
    std::vector<std::string> EmergencyVocabulary;
    
    // === Internal Helpers ===
    bool InitializeAudioProcessor();
    bool InitializeLanguageModel();
    void CleanupResources();
};

/**
 * Aerospace-specific speech recognition utilities
 */
namespace AerospaceVoiceUtils
{
    /**
     * Check if text contains aerospace terminology
     */
    bool ContainsAerospaceTerminology(const std::string& Text);
    
    /**
     * Check if command is emergency-related
     */
    bool IsEmergencyCommand(const std::string& Command);
    
    /**
     * Normalize aerospace terminology in text
     */
    std::string NormalizeAerospaceText(const std::string& Input);
    
    /**
     * Get confidence adjustment for aerospace context
     */
    float GetAerospaceConfidenceAdjustment(const std::string& Text);
}

// === Compile-time Configuration ===
#ifndef SPEECH_RECOGNITION_MAX_THREADS
#define SPEECH_RECOGNITION_MAX_THREADS 4
#endif

#ifndef SPEECH_RECOGNITION_BUFFER_SIZE
#define SPEECH_RECOGNITION_BUFFER_SIZE 4096
#endif

#ifndef AEROSPACE_VOCABULARY_SIZE
#define AEROSPACE_VOCABULARY_SIZE 10000
#endif

#endif // SPEECHRECOGNITIONENGINE_H
