/**
 * AQUA V. Audio Stream Processor - Header
 * AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-02-02-AUDIOSTREAM-QDAT-v7.6.0.h
 * 
 * Real-time audio stream processing for aerospace voice recognition
 * Handles audio capture, buffering, and preprocessing
 * 
 * @author AQUA V. Corporation
 * @version 7.6.0
 * @date July 2025
 */

#pragma once

#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

// Platform-specific includes
#ifdef _WIN32
    #include <windows.h>
    #include <mmdeviceapi.h>
    #include <audioclient.h>
    #include <functiondiscoverykeys_devpkey.h>
#elif __linux__
    #include <alsa/asoundlib.h>
    #include <pulse/pulseaudio.h>
#elif __APPLE__
    #include <CoreAudio/CoreAudio.h>
    #include <AudioUnit/AudioUnit.h>
    #include <AudioToolbox/AudioToolbox.h>
#endif

// Aerospace compliance definitions
#define AQUA_V_API __declspec(dllexport)
#define AEROSPACE_AUDIO_QUALITY_THRESHOLD 0.85f
#define EMERGENCY_RESPONSE_LATENCY_MS 300
#define DO_178C_COMPLIANCE_LEVEL_C 1

/**
 * Audio stream configuration
 */
struct FAudioStreamConfig
{
    uint32_t SampleRate = 48000;        // Sample rate in Hz
    uint16_t BitsPerSample = 16;        // Bit depth
    uint8_t Channels = 1;               // Number of audio channels
    uint32_t BufferSizeMs = 100;        // Buffer size in milliseconds
    uint32_t MaxBuffers = 10;           // Maximum number of buffers
    bool EnableNoiseGate = true;        // Enable noise gate processing
    float NoiseGateThreshold = -40.0f;  // Noise gate threshold in dB
    bool EnableEchoCancellation = true; // Enable echo cancellation
    bool EnableNoiseReduction = true;   // Enable noise reduction
    bool EnableAutomaticGainControl = true; // Enable automatic gain control
    
    // Aerospace-specific settings
    bool AerospaceCompliantMode = true;
    float EmergencyPriorityGain = 2.0f;
    uint32_t EmergencyDetectionLatencyMs = 200;
    
    FAudioStreamConfig() = default;
};

/**
 * Audio quality metrics
 */
struct FAudioQualityMetrics
{
    float SignalToNoiseRatio = 0.0f;     // SNR in dB
    float BackgroundNoiseLevel = 0.0f;   // Background noise level in dB
    float SpeechClarity = 0.0f;          // Speech clarity index (0-1)
    float VoiceActivityLevel = 0.0f;     // Voice activity detection level (0-1)
    float SpectralCentroid = 0.0f;       // Spectral centroid in Hz
    float ZeroCrossingRate = 0.0f;       // Zero crossing rate
    float MeanSquaredEnergy = 0.0f;      // Mean squared energy
    
    // Compliance metrics
    bool IsAerospaceCompliant = false;   // Meets aerospace audio standards
    bool IsEmergencyQuality = false;     // Meets emergency communication standards
    bool PassesQualityThreshold = false; // Passes minimum quality threshold
    
    uint64_t Timestamp = 0;              // Timestamp of measurement
    uint32_t FrameNumber = 0;            // Audio frame number
    
    FAudioQualityMetrics() = default;
};

/**
 * Audio frame data structure
 */
struct FAudioFrame
{
    std::vector<uint8_t> RawData;        // Raw audio data
    std::vector<float> ProcessedSamples; // Processed floating-point samples
    FAudioQualityMetrics QualityMetrics; // Quality metrics for this frame
    uint64_t Timestamp = 0;              // Frame timestamp
    uint32_t FrameNumber = 0;            // Sequential frame number
    bool IsEmergencyFrame = false;       // Emergency priority flag
    
    FAudioFrame() = default;
};

/**
 * Audio processing callback interface
 */
class IAudioProcessingCallback
{
public:
    virtual ~IAudioProcessingCallback() = default;
    virtual void OnAudioFrameReady(const FAudioFrame& Frame) = 0;
    virtual void OnQualityAlert(const FAudioQualityMetrics& Metrics) = 0;
    virtual void OnEmergencyDetected(const FAudioFrame& Frame) = 0;
};

/**
 * Audio stream processor class
 * 
 * High-performance real-time audio processing for aerospace voice recognition
 * Features:
 * - Multi-threaded audio capture and processing
 * - Real-time quality monitoring
 * - Emergency audio prioritization
 * - Aerospace compliance validation
 * - Low-latency processing (<300ms)
 */
class AQUA_V_API AudioStreamProcessor
{
public:
    AudioStreamProcessor();
    virtual ~AudioStreamProcessor();
    
    // Core initialization and control
    
    /**
     * Initialize audio stream processor with configuration
     * @param Config Audio configuration parameters
     * @return true if initialization successful
     */
    bool Initialize(const FAudioStreamConfig& Config);
    
    /**
     * Start audio capture and processing
     * @return true if capture started successfully
     */
    bool StartCapture();
    
    /**
     * Stop audio capture and processing
     */
    void StopCapture();
    
    /**
     * Check if processor is currently capturing audio
     * @return true if capturing
     */
    bool IsCapturing() const;
    
    /**
     * Check if audio data is available for processing
     * @return true if data available
     */
    bool IsDataAvailable() const;
    
    // Audio data access
    
    /**
     * Get next audio frame from the processing queue
     * @return Audio frame with raw data and quality metrics
     */
    FAudioFrame GetNextAudioFrame();
    
    /**
     * Get next raw audio block (legacy interface)
     * @return Raw audio data block
     */
    std::vector<uint8_t> GetNextAudioBlock();
    
    /**
     * Peek at next audio frame without removing from queue
     * @return Copy of next audio frame
     */
    FAudioFrame PeekNextAudioFrame() const;
    
    // Configuration and calibration
    
    /**
     * Calibrate audio input for optimal performance
     * @param CalibrationTimeMs Duration of calibration in milliseconds
     * @return true if calibration successful
     */
    bool Calibrate(uint32_t CalibrationTimeMs = 5000);
    
    /**
     * Auto-calibrate based on current environment
     * @return true if auto-calibration successful
     */
    bool AutoCalibrate();
    
    /**
     * Update audio configuration at runtime
     * @param Config New configuration parameters
     * @return true if configuration updated successfully
     */
    bool UpdateConfiguration(const FAudioStreamConfig& Config);
    
    // Quality monitoring and control
    
    /**
     * Get current audio quality metrics
     * @return Current quality metrics
     */
    FAudioQualityMetrics GetQualityMetrics() const;
    
    /**
     * Get average quality metrics over specified duration
     * @param DurationMs Duration to average over in milliseconds
     * @return Average quality metrics
     */
    FAudioQualityMetrics GetAverageQualityMetrics(uint32_t DurationMs = 1000) const;
    
    /**
     * Set noise gate parameters
     * @param bEnabled Enable/disable noise gate
     * @param ThresholdDb Threshold in decibels
     */
    void SetNoiseGate(bool bEnabled, float ThresholdDb = -40.0f);
    
    /**
     * Set automatic gain control parameters
     * @param bEnabled Enable/disable AGC
     * @param TargetLevel Target level in dB
     * @param MaxGain Maximum gain in dB
     */
    void SetAutomaticGainControl(bool bEnabled, float TargetLevel = -20.0f, float MaxGain = 30.0f);
    
    // Callback management
    
    /**
     * Register callback for audio processing events
     * @param Callback Callback interface implementation
     */
    void RegisterCallback(IAudioProcessingCallback* Callback);
    
    /**
     * Unregister audio processing callback
     * @param Callback Callback to remove
     */
    void UnregisterCallback(IAudioProcessingCallback* Callback);
    
    // Emergency and aerospace features
    
    /**
     * Enable emergency audio prioritization mode
     * @param bEnabled Enable/disable emergency mode
     * @param LatencyMs Maximum latency for emergency audio
     */
    void SetEmergencyMode(bool bEnabled, uint32_t LatencyMs = 200);
    
    /**
     * Check if current audio meets aerospace compliance standards
     * @return true if compliant with aerospace standards
     */
    bool IsAerospaceCompliant() const;
    
    /**
     * Get compliance status for specific standards
     * @param Standard Standard to check (EASA_CS25, FAA_PART25, DO_178C)
     * @return true if compliant with specified standard
     */
    bool GetComplianceStatus(const std::string& Standard) const;
    
    // Performance monitoring
    
    /**
     * Get current processing latency
     * @return Latency in milliseconds
     */
    uint32_t GetProcessingLatency() const;
    
    /**
     * Get audio buffer usage statistics
     * @return Buffer usage percentage (0-100)
     */
    float GetBufferUsage() const;
    
    /**
     * Get audio dropout statistics
     * @return Number of audio dropouts in last minute
     */
    uint32_t GetDropoutCount() const;
    
    /**
     * Reset performance statistics
     */
    void ResetStatistics();
    
    // Advanced features
    
    /**
     * Apply real-time audio effects
     * @param EffectType Type of effect to apply
     * @param Parameters Effect parameters
     * @return true if effect applied successfully
     */
    bool ApplyAudioEffect(const std::string& EffectType, const std::map<std::string, float>& Parameters);
    
    /**
     * Enable/disable real-time spectrum analysis
     * @param bEnabled Enable spectrum analysis
     * @param WindowSize FFT window size
     */
    void SetSpectrumAnalysis(bool bEnabled, uint32_t WindowSize = 1024);
    
    /**
     * Get current audio spectrum data
     * @return Frequency spectrum data
     */
    std::vector<float> GetSpectrumData() const;

private:
    // Configuration and state
    FAudioStreamConfig Configuration;
    std::atomic<bool> bIsInitialized;
    std::atomic<bool> bIsCapturing;
    std::atomic<bool> bShouldStop;
    std::atomic<bool> bEmergencyMode;
    std::atomic<uint32_t> ProcessingLatency;
    
    // Threading
    std::thread CaptureThread;
    std::thread ProcessingThread;
    std::thread QualityMonitorThread;
    
    // Audio data management
    std::queue<FAudioFrame> AudioFrameQueue;
    std::queue<std::vector<uint8_t>> AudioBufferQueue; // Legacy interface
    mutable std::mutex BufferMutex;
    std::condition_variable BufferCondition;
    
    // Quality monitoring
    FAudioQualityMetrics CurrentMetrics;
    std::queue<FAudioQualityMetrics> QualityHistory;
    mutable std::mutex MetricsMutex;
    
    // Callbacks
    std::vector<IAudioProcessingCallback*> Callbacks;
    std::mutex CallbackMutex;
    
    // Performance statistics
    std::atomic<uint32_t> DropoutCount;
    std::atomic<float> BufferUsagePercent;
    std::chrono::high_resolution_clock::time_point LastStatisticsReset;
    
    // Platform-specific audio handles
#ifdef _WIN32
    IMMDeviceEnumerator* pEnumerator;
    IMMDevice* pDevice;
    IAudioClient* pAudioClient;
    IAudioCaptureClient* pCaptureClient;
    WAVEFORMATEX* pwfx;
#elif __linux__
    snd_pcm_t* alsa_handle;
    pa_mainloop* pa_mainloop_ptr;
    pa_context* pa_context_ptr;
    pa_stream* pa_stream_ptr;
#elif __APPLE__
    AudioUnit audioUnit;
    AudioStreamBasicDescription audioFormat;
#endif
    
    // Internal processing methods
    void CaptureThreadFunction();
    void ProcessingThreadFunction();
    void QualityMonitorThreadFunction();
    
    void ProcessAudioBuffer(const uint8_t* Data, size_t Size);
    FAudioQualityMetrics AnalyzeAudioQuality(const std::vector<float>& Samples);
    void ApplyNoiseGate(std::vector<float>& Samples, float Threshold);
    void ApplyAutomaticGainControl(std::vector<float>& Samples);
    void ApplyNoiseReduction(std::vector<float>& Samples);
    void ApplyEchoCancellation(std::vector<float>& Samples);
    
    bool InitializePlatformAudio();
    void ShutdownPlatformAudio();
    bool StartPlatformCapture();
    void StopPlatformCapture();
    
    void NotifyCallbacks(const FAudioFrame& Frame);
    void NotifyQualityAlert(const FAudioQualityMetrics& Metrics);
    void NotifyEmergencyDetected(const FAudioFrame& Frame);
    
    // Utility methods
    float CalculateSignalToNoiseRatio(const std::vector<float>& Samples);
    float CalculateSpectralCentroid(const std::vector<float>& Spectrum);
    float CalculateZeroCrossingRate(const std::vector<float>& Samples);
    std::vector<float> ApplyWindow(const std::vector<float>& Samples, const std::string& WindowType);
    std::vector<float> ComputeFFT(const std::vector<float>& Samples);
    
    bool CheckAerospaceCompliance(const FAudioQualityMetrics& Metrics);
    bool DetectEmergencyAudio(const std::vector<float>& Samples);
};

// Global utility functions

/**
 * Convert raw audio data to floating-point samples
 * @param RawData Raw audio data buffer
 * @param BitsPerSample Audio bit depth
 * @return Normalized floating-point samples (-1.0 to 1.0)
 */
AQUA_V_API std::vector<float> ConvertToFloatSamples(const std::vector<uint8_t>& RawData, uint16_t BitsPerSample);

/**
 * Apply aerospace audio quality standards validation
 * @param Metrics Audio quality metrics to validate
 * @return true if metrics meet aerospace standards
 */
AQUA_V_API bool ValidateAerospaceAudioQuality(const FAudioQualityMetrics& Metrics);

/**
 * Calculate recommended buffer size for given latency requirement
 * @param LatencyMs Target latency in milliseconds
 * @param SampleRate Audio sample rate
 * @return Recommended buffer size in samples
 */
AQUA_V_API uint32_t CalculateOptimalBufferSize(uint32_t LatencyMs, uint32_t SampleRate);

#endif // AUDIOSTREAMPROCESSOR_H