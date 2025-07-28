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
    
    FAudioStreamConfig() = default;
};

/**
 * Audio quality metrics
 */
struct FAudioQualityMetrics
{
    float SignalToNoiseRatio = 0.0f;
    float BackgroundNoiseLevel = 0.0f;
    float SpeechClarity = 0.0f;
    float VoiceActivityLevel = 0.0f;
    bool IsAerospaceCompliant = false;
    uint64_t Timestamp = 0;
    
    FAudioQualityMetrics() = default;
};

/**
 * Audio stream processor class
 */
class AQUA_V_API AudioStreamProcessor
{
public:
    AudioStreamProcessor();
    virtual ~AudioStreamProcessor();
    
    /**
     * Initialize audio stream processor
     */
    bool Initialize(const FAudioStreamConfig& Config);
    
    /**
     * Start audio capture
     */
    bool StartCapture();
    
    /**
     * Stop audio capture
     */
    void StopCapture();
    
    /**
     * Check if audio data is available
     */
    bool IsDataAvailable() const;
    
    /**
     * Get next audio block
     */
    std::vector<uint8_t> GetNextAudioBlock();
    
    /**
     * Calibrate audio input
     */
    bool Calibrate(uint32_t CalibrationTimeMs);
    
    /**
     * Get current audio quality metrics
     */
    FAudioQualityMetrics GetQualityMetrics() const;
    
    /**
     * Set noise gate parameters
     */
    void SetNoiseGate(bool bEnabled, float ThresholdDb);

private:
    FAudioStreamConfig Configuration;
    std::atomic<bool> bIsCapturing;
    std::atomic<bool> bShouldStop;
    
    std::thread CaptureThread;
    std::queue<std::vector<uint8_t>> AudioBuffers;
    mutable std::mutex BufferMutex;
    std::condition_variable BufferCondition;
    
    FAudioQualityMetrics CurrentMetrics;
    mutable std::mutex MetricsMutex;
    
    void CaptureThreadFunction();
    void ProcessAudioBuffer(const uint8_t* Data, size_t Size);
    FAudioQualityMetrics AnalyzeAudioQuality(const std::vector<float>& Samples);
};

#endif // AUDIOSTREAMPROCESSOR_H
