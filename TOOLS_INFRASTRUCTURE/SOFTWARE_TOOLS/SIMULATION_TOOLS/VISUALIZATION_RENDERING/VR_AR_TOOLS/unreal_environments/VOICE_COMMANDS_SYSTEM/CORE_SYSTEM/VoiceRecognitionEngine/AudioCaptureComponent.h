/**
 * A.Q.U.A.-V. Advanced Voice Commands System
 * Audio Capture Component - Revolutionary VR/AR Speech Recognition
 * 
 * Document ID: AQV-VCS-25JU0001-OPS-BOB-TEC-SM-ATA-053-00-01-TPL-TEC-001-QDAT-v1.0.0
 * 
 * This component provides optimized audio capture for aerospace training environments
 * with specific filtering for BWB-Q100 aircraft noise profiles and quantum system interference.
 * 
 * © 2025 A.Q.U.A. Venture. All rights reserved.
 * Classification: AQUA V. INTERNAL - RESTRICTED
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Engine.h"
#include "Sound/SoundWave.h"
#include "AudioCaptureComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioCaptured, const TArray<float>&, AudioData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoiceActivityDetected, bool, bIsVoiceActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuantumInterferenceDetected, float, InterferenceLevel, float, Frequency);

/**
 * BWB-Q100 Specific Noise Profile for optimal filtering
 */
USTRUCT(BlueprintType)
struct VOICECOMMANDS_API FNoiseProfile
{
    GENERATED_BODY()

    // Engine frequency range in Hz
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Profile")
    FVector2D EngineFrequencyRange = FVector2D(200.0f, 8000.0f);

    // HVAC noise level in dB
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Profile")
    float HVACNoiseLevel = -35.0f;

    // Avionics hum frequency in Hz
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Profile")
    float AvionicsHum = 1000.0f;

    // Wind noise threshold in dB
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Profile")
    float WindNoiseThreshold = -25.0f;

    // Unique quantum system interference frequency in Hz
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Profile")
    float QuantumSystemHum = 440.0f;

    FNoiseProfile()
    {
        EngineFrequencyRange = FVector2D(200.0f, 8000.0f);
        HVACNoiseLevel = -35.0f;
        AvionicsHum = 1000.0f;
        WindNoiseThreshold = -25.0f;
        QuantumSystemHum = 440.0f;
    }
};

/**
 * Audio Capture Settings for different environments
 */
USTRUCT(BlueprintType)
struct VOICECOMMANDS_API FAudioCaptureSettings
{
    GENERATED_BODY()

    // Sample rate in Hz (16kHz optimal for speech)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    int32 SampleRate = 16000;

    // Bit depth (16-bit optimal for speech)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    int32 BitDepth = 16;

    // Number of audio channels (1 for mono speech)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    int32 Channels = 1;

    // Buffer size for real-time processing
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    int32 BufferSize = 1024;

    // Microphone gain (1.0 = normal)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    float MicrophoneGain = 1.0f;

    // Auto Gain Control enabled
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    bool bEnableAGC = true;

    // Noise gate threshold in dB
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Settings")
    float NoiseGateThreshold = -50.0f;
};

/**
 * Audio Capture Component for A.Q.U.A.-V. Voice Commands System
 * 
 * Features:
 * - BWB-Q100 specific noise filtering
 * - Quantum system interference detection and removal
 * - Adaptive echo cancellation
 * - Real-time voice activity detection
 * - Military-grade audio processing
 */
UCLASS(ClassGroup=(VoiceCommands), meta=(BlueprintSpawnableComponent))
class VOICECOMMANDS_API UAudioCaptureComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAudioCaptureComponent();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
                              FActorComponentTickFunction* ThisTickFunction) override;

    // Initialize audio capture with BWB-Q100 profile
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    bool InitializeAudioCapture();

    // Start capturing audio
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    bool StartCapture();

    // Stop capturing audio
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void StopCapture();

    // Configure noise profile for current environment
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void SetNoiseProfile(const FNoiseProfile& NewProfile);

    // Get current audio settings
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    FAudioCaptureSettings GetAudioSettings() const { return AudioSettings; }

    // Set audio capture settings
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void SetAudioSettings(const FAudioCaptureSettings& NewSettings);

    // Check if voice activity is detected
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    bool IsVoiceActive() const { return bVoiceActivityDetected; }

    // Get current audio level in dB
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    float GetCurrentAudioLevel() const { return CurrentAudioLevel; }

    // Get noise level in dB
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    float GetNoiseLevel() const { return NoiseLevel; }

    // Get quantum interference level
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    float GetQuantumInterferenceLevel() const { return QuantumInterferenceLevel; }

    // Enable/disable cockpit mode (BWB-Q100 specific filtering)
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void SetCockpitMode(bool bEnabled);

    // Calibrate noise floor for current environment
    UFUNCTION(BlueprintCallable, Category = "Voice Commands")
    void CalibrateNoiseFloor();

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Voice Commands")
    FOnAudioCaptured OnAudioCaptured;

    UPROPERTY(BlueprintAssignable, Category = "Voice Commands")
    FOnVoiceActivityDetected OnVoiceActivityDetected;

    UPROPERTY(BlueprintAssignable, Category = "Voice Commands")
    FOnQuantumInterferenceDetected OnQuantumInterferenceDetected;

protected:
    // Process raw audio data
    void ProcessAudioData(const TArray<float>& RawAudioData);

    // Apply BWB-Q100 specific noise filtering
    void ApplyBWBNoiseFiltering(TArray<float>& AudioData);

    // Detect and remove quantum system interference
    void ProcessQuantumInterference(TArray<float>& AudioData);

    // Adaptive echo cancellation specific to cockpit acoustics
    void ApplyAdaptiveEchoCancellation(TArray<float>& AudioData);

    // Voice Activity Detection optimized for aviation speech
    bool DetectVoiceActivity(const TArray<float>& AudioData);

    // Calculate spectral centroid for voice detection
    float CalculateSpectralCentroid(const TArray<float>& AudioData);

    // Analyze aviation speech patterns
    float AnalyzeAviationSpeechPatterns(const TArray<float>& AudioData);

    // Fast Fourier Transform for frequency analysis
    void PerformFFT(const TArray<float>& InputData, TArray<float>& FrequencyData);

    // Apply bandpass filter for voice frequencies
    void ApplyVoiceBandpassFilter(TArray<float>& AudioData);

    // Automatic Gain Control
    void ApplyAutomaticGainControl(TArray<float>& AudioData);

    // Noise gate processing
    void ApplyNoiseGate(TArray<float>& AudioData);

private:
    // Audio capture settings
    UPROPERTY(EditAnywhere, Category = "Audio Settings")
    FAudioCaptureSettings AudioSettings;

    // Noise profile for BWB-Q100
    UPROPERTY(EditAnywhere, Category = "Noise Profile")
    FNoiseProfile CockpitNoiseProfile;

    // Current state
    bool bIsCapturing = false;
    bool bVoiceActivityDetected = false;
    bool bCockpitModeEnabled = true;
    
    // Audio levels
    float CurrentAudioLevel = 0.0f;
    float NoiseLevel = 0.0f;
    float QuantumInterferenceLevel = 0.0f;
    float NoiseFloor = -60.0f;

    // Processing buffers
    TArray<float> ProcessingBuffer;
    TArray<float> FFTBuffer;
    TArray<float> FilterBuffer;

    // Adaptive filtering state
    TArray<float> EchoStateBuffer;
    TArray<float> CockpitResponseBuffer;
    
    // AGC state
    float AGCGain = 1.0f;
    float AGCAttack = 0.1f;
    float AGCRelease = 0.01f;

    // Voice activity detection state
    float VADThreshold = -40.0f;
    float VoiceConfidence = 0.0f;
    int32 VoiceFrameCount = 0;
    int32 SilenceFrameCount = 0;

    // Quantum interference detection
    float QuantumFrequencyBin = 0.0f;
    float QuantumInterferenceThreshold = -45.0f;

    // Performance metrics
    int32 ProcessedFrames = 0;
    float AverageProcessingTime = 0.0f;
    float MaxProcessingTime = 0.0f;

    // Constants
    static constexpr float VOICE_FREQUENCY_MIN = 85.0f;    // Hz
    static constexpr float VOICE_FREQUENCY_MAX = 8000.0f;  // Hz
    static constexpr float VOICE_FORMANT_F1 = 800.0f;     // Hz
    static constexpr float VOICE_FORMANT_F2 = 1200.0f;    // Hz
    static constexpr int32 VAD_FRAME_THRESHOLD = 3;       // Frames for voice confirmation
    static constexpr int32 SILENCE_FRAME_THRESHOLD = 10;  // Frames for silence confirmation
};

/**
 * Inline implementations for performance-critical functions
 */

// Calculate RMS audio level
inline float CalculateRMSLevel(const TArray<float>& AudioData)
{
    if (AudioData.Num() == 0) return 0.0f;
    
    float Sum = 0.0f;
    for (float Sample : AudioData)
    {
        Sum += Sample * Sample;
    }
    
    float RMS = FMath::Sqrt(Sum / AudioData.Num());
    return 20.0f * FMath::LogX(10.0f, FMath::Max(RMS, 1e-10f)); // Convert to dB
}

// Simple high-pass filter for noise reduction
inline void ApplyHighPassFilter(TArray<float>& AudioData, float CutoffFreq, float SampleRate)
{
    if (AudioData.Num() < 2) return;
    
    float RC = 1.0f / (2.0f * PI * CutoffFreq);
    float dt = 1.0f / SampleRate;
    float Alpha = RC / (RC + dt);
    
    for (int32 i = 1; i < AudioData.Num(); ++i)
    {
        AudioData[i] = Alpha * (AudioData[i-1] + AudioData[i] - AudioData[i-1]);
    }
}

// Apply window function for FFT
inline void ApplyHannWindow(TArray<float>& AudioData)
{
    const int32 N = AudioData.Num();
    for (int32 i = 0; i < N; ++i)
    {
        float Window = 0.5f * (1.0f - FMath::Cos(2.0f * PI * i / (N - 1)));
        AudioData[i] *= Window;
    }
}