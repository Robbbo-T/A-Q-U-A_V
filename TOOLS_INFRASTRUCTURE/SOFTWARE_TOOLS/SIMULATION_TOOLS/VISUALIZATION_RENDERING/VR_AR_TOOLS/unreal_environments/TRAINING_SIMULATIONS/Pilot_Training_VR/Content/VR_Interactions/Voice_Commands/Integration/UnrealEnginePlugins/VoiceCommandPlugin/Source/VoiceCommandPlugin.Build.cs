/*
 * ============================================================================
 * AQUA V. - Voice Command Plugin Build Configuration
 * ============================================================================
 * 
 * Project:     AMPEL360 Training VR System
 * Component:   Voice Command Plugin Build Script
 * File:        VoiceCommandPlugin.Build.cs
 * Version:     v7.6.0
 * 
 * Description: Unreal Engine build configuration for the AQUA V. Voice Command Plugin
 *              Defines dependencies, includes, and compilation settings
 * 
 * Author:      AQUA V. Development Team
 * Date:        2025-07-28
 * Copyright:   (c) 2025 ROBBBO-T GAIA AIR & SPACE
 * License:     Proprietary - Aerospace Training Use Only
 * 
 * ============================================================================
 */

using UnrealBuildTool;

public class VoiceCommandPlugin : ModuleRules
{
    public VoiceCommandPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        // PCH (Precompiled Header) usage for faster compilation
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Include paths for plugin headers
        PublicIncludePaths.AddRange(
            new string[] {
                // Public include paths
                "VoiceCommandPlugin/Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                // Private include paths
                "VoiceCommandPlugin/Private"
            }
        );

        // Public dependencies - available to other modules that depend on this plugin
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                // Core Unreal Engine modules
                "Core",
                "CoreUObject",
                "Engine",
                
                // Input and UI
                "InputCore",
                "UMG",
                "Slate",
                "SlateCore",
                
                // Audio processing modules
                "AudioPlatformConfiguration",
                "AudioMixer",
                "AudioMixerCore",
                "AudioCaptureCore",
                "AudioCapture",
                "SignalProcessing",
                "AudioSynesthesia",
                
                // Rendering and graphics
                "RenderCore",
                "RHI",
                
                // Utility modules
                "Json",
                "JsonUtilities",
                "HTTP",
                
                // Threading and async support
                "ApplicationCore"
            }
        );

        // Private dependencies - only used internally by this plugin
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                // Core systems
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                
                // Editor support (for development)
                "UnrealEd",
                "ToolMenus",
                "EditorStyle",
                "EditorWidgets",
                
                // Audio analysis and processing
                "AudioAnalyzer",
                "AudioMixerCore",
                "SoundUtilities",
                
                // File and configuration management
                "DesktopPlatform",
                "DirectoryWatcher",
                
                // Networking (for external API integration)
                "Sockets",
                "Networking",
                
                // Performance and profiling
                "TraceLog",
                "ProfilerService",
                
                // VR and XR support
                "HeadMountedDisplay",
                "XRBase"
            }
        );

        // Dynamic dependencies that may not be available on all platforms
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // Optional modules that can be loaded at runtime
                "AudioCaptureRtAudio",
                "AudioCaptureWasapi",
                "AudioCaptureAndroid",
                "MediaFoundationMedia"
            }
        );

        // Platform-specific configurations
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Windows-specific audio libraries
            PublicSystemLibraries.AddRange(new string[]
            {
                "winmm.lib",
                "dsound.lib",
                "dxguid.lib"
            });

            // Windows audio API definitions
            PublicDefinitions.Add("WITH_WASAPI=1");
            PublicDefinitions.Add("WITH_DIRECTSOUND=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            // Linux-specific audio libraries
            PublicSystemLibraries.AddRange(new string[]
            {
                "asound",
                "pulse"
            });

            PublicDefinitions.Add("WITH_ALSA=1");
            PublicDefinitions.Add("WITH_PULSEAUDIO=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            // macOS-specific audio frameworks
            PublicFrameworks.AddRange(new string[]
            {
                "CoreAudio",
                "AudioUnit",
                "AudioToolbox"
            });

            PublicDefinitions.Add("WITH_COREAUDIO=1");
        }

        // Compilation definitions for feature control
        PublicDefinitions.AddRange(new string[]
        {
            // Plugin identification
            "VOICE_COMMAND_PLUGIN_VERSION=\"7.6.0\"",
            "AQUA_V_VOICE_COMMANDS=1",
            
            // Feature flags
            "WITH_VOICE_RECOGNITION=1",
            "WITH_NATURAL_LANGUAGE_PROCESSING=1",
            "WITH_TEXT_TO_SPEECH=1",
            "WITH_AUDIO_QUALITY_MONITORING=1",
            
            // Aerospace-specific features
            "WITH_ATA_CHAPTER_SUPPORT=1",
            "WITH_QUANTUM_SYSTEMS_SUPPORT=1",
            "WITH_EMERGENCY_PROCEDURES=1",
            
            // Compliance and safety
            "DO_178C_COMPLIANT=1",
            "EASA_CS25_COMPLIANT=1",
            "FAA_PART25_COMPLIANT=1",
            
            // Performance optimization
            "WITH_REAL_TIME_AUDIO_PROCESSING=1",
            "WITH_MULTI_THREADED_RECOGNITION=1",
            
            // Debug and development features
            "WITH_VOICE_COMMAND_DEBUG_TOOLS=1",
            "WITH_PERFORMANCE_PROFILING=1"
        });

        // Optimization settings for different build configurations
        if (Target.Configuration == UnrealTargetConfiguration.Development ||
            Target.Configuration == UnrealTargetConfiguration.Debug)
        {
            // Development/Debug specific settings
            PublicDefinitions.Add("VOICE_COMMAND_DEBUG=1");
            PublicDefinitions.Add("ENABLE_VOICE_RECORDING=1");
            
            // Additional debugging modules
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "MessageLog",
                "OutputLog"
            });
        }
        else
        {
            // Shipping/Release optimizations
            PublicDefinitions.Add("VOICE_COMMAND_DEBUG=0");
            PublicDefinitions.Add("ENABLE_VOICE_RECORDING=0");
            
            // Optimization flags
            PublicDefinitions.Add("VOICE_COMMAND_OPTIMIZED=1");
        }

        // VR platform support
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // VR headset support for Windows
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "OculusHMD",
                "SteamVR",
                "OpenXRHMD"
            });
            
            PublicDefinitions.Add("WITH_VR_VOICE_COMMANDS=1");
        }

        // Thread safety and performance
        PublicDefinitions.AddRange(new string[]
        {
            // Threading configuration
            "VOICE_COMMAND_THREAD_SAFE=1",
            "VOICE_COMMAND_MAX_THREADS=4",
            
            // Memory management
            "VOICE_COMMAND_USE_MEMORY_POOL=1",
            "VOICE_COMMAND_MAX_MEMORY_MB=512",
            
            // Audio buffer configuration
            "VOICE_COMMAND_BUFFER_SIZE=1024",
            "VOICE_COMMAND_SAMPLE_RATE=48000",
            "VOICE_COMMAND_CHANNELS=1"
        });

        // External library integration (placeholder for future speech recognition libraries)
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Windows Speech API integration
            PublicDefinitions.Add("WITH_WINDOWS_SPEECH_API=1");
            
            // Potential integration with Microsoft Speech Platform
            // PublicSystemLibraries.Add("sapi.lib");
        }

        // Localization support
        PublicDefinitions.AddRange(new string[]
        {
            "WITH_AEROSPACE_TERMINOLOGY=1",
            "WITH_ICAO_PHONETIC_ALPHABET=1",
            "WITH_MULTILINGUAL_SUPPORT=1"
        });

        // Compliance and certification requirements
        PublicDefinitions.AddRange(new string[]
        {
            // Safety certification levels
            "SOFTWARE_LEVEL_DAL_C=1",
            "SAFETY_CRITICAL_VOICE_COMMANDS=1",
            
            // Audit and traceability
            "WITH_COMMAND_AUDIT_TRAIL=1",
            "WITH_PERFORMANCE_LOGGING=1",
            
            // Security features
            "WITH_VOICE_COMMAND_ENCRYPTION=1",
            "WITH_SECURE_COMMUNICATION=1"
        });

        // Include third-party libraries (when available)
        // Note: Actual speech recognition libraries would be integrated here
        /*
        string ThirdPartyPath = Path.Combine(ModuleDirectory, "../ThirdParty/");
        
        if (Directory.Exists(ThirdPartyPath))
        {
            // Add third-party speech recognition libraries
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "SpeechSDK/Include"));
            
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "SpeechSDK/Lib/Win64"));
                PublicAdditionalLibraries.Add("speechsdk.lib");
            }
        }
        */

        // Module initialization order
        PublicDefinitions.Add("VOICE_COMMAND_EARLY_INIT=1");
        
        // Ensure compatibility with Unreal Engine versions
        if (Target.Version.MajorVersion >= 5)
        {
            PublicDefinitions.Add("UE5_COMPATIBLE=1");
            
            // UE5-specific optimizations
            if (Target.Version.MinorVersion >= 1)
            {
                PublicDefinitions.Add("WITH_UE5_AUDIO_IMPROVEMENTS=1");
            }
        }
    }
}

/*
 * ============================================================================
 * Build Configuration Notes
 * ============================================================================
 * 
 * This build script configures the AQUA V. Voice Command Plugin for optimal
 * performance in aerospace training environments. Key features include:
 * 
 * 1. Real-time audio processing with low latency
 * 2. Thread-safe architecture for concurrent operations
 * 3. Platform-specific optimizations for Windows, Linux, and macOS
 * 4. VR headset integration for immersive training
 * 5. Compliance with aviation software standards
 * 6. Extensive debugging and profiling support
 * 7. Security and encryption capabilities
 * 8. Multilingual and aerospace terminology support
 * 
 * The configuration is designed to meet the stringent requirements of
 * aerospace training applications while maintaining compatibility with
 * Unreal Engine's plugin architecture.
 * 
 * ============================================================================
 */
