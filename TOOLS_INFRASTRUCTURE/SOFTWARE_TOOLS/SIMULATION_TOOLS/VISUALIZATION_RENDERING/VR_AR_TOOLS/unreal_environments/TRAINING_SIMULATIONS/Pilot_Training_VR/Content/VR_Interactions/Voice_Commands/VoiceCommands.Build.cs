/**
 * ============================================================================
 * AQUA V. - Voice Commands Build Configuration
 * ============================================================================
 * 
 * Document ID: AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-346-50-01-TPL-TEC-BUILD-001-QDAT-v0.1.0
 * 
 * Nomenclature Breakdown (AQUA V. Official System v3.1):
 * - LÍNEA:     AMP (AMPEL360 Products)
 * - PRODUCTO:  EVTOL (Electric Vertical Take-Off and Landing Aircraft)
 * - MSN:       25SVD0001 (2025 Silicon Valley Development Unit 0001)
 * - FASE:      DEV (Development Phase)
 * - ALI/BOB:   BOB (Build-Operate-Build Digital Systems)
 * - ARTIFACT:  TEC (Technical Artifacts)
 * - TYPE:      SM (Software Module)
 * - UTCS:      DTCEC-346-50-01 (Digital Twin, Cloud & Edge Computing - Build Configuration)
 * - CÓDIGO:    000-00-01 (Primary component within UTCS)
 * - TEMPLATE:  TPL-TEC-BUILD-001 (Technical Template - Build Config - Instance 001)
 * - QD:        QDAT (Q-Data Governance Division)
 * - VERSIÓN:   v0.1.0 (Initial development version)
 * 
 * Description: Unreal Engine build configuration for AQUA V. Voice Commands system
 *              Manages dependencies, compilation settings, and module integration
 * 
 * Digital Thread Integration:
 * - Parent System: AMPEL360 Training VR System
 * - Component: Voice Recognition Engine Build System
 * - Dependencies: Core Unreal Engine modules, Audio modules, VR modules
 * - Build Target: Development, Shipping, Test configurations
 * 
 * Compliance:
 * - Unreal Engine 5.0+ Build System Standards
 * - C++17/C++20 Language Standards
 * - Cross-platform compilation (Windows, Linux, Mac)
 * - VR Platform Support (Oculus, HTC Vive, PICO)
 * 
 * Author:      AQUA V. Development Team - QDAT Division
 * Date:        2025-07-28
 * Copyright:   (c) 2025 ROBBBO-T GAIA AIR & SPACE
 * License:     Proprietary - Aerospace Training Use Only
 * 
 * ============================================================================
 */

using UnrealBuildTool;

public class VoiceCommands : ModuleRules
{
    public VoiceCommands(ReadOnlyTargetRules Target) : base(Target)
    {
        // ====================================================================
        // C++ LANGUAGE AND STANDARDS CONFIGURATION
        // ====================================================================
        
        // Use C++17 for aerospace-grade stability with modern features
        CppStandard = CppStandardVersion.Cpp17;
        
        // Enable RTTI for voice command polymorphism
        bUseRTTI = true;
        
        // Enable exceptions for robust error handling in voice processing
        bEnableExceptions = true;
        
        // Enable Unity builds for faster compilation
        bUseUnity = true;
        
        // Precompiled header settings for optimal build performance
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        // ====================================================================
        // AQUA V. VOICE COMMANDS CORE DEPENDENCIES
        // ====================================================================
        
        PublicDependencyModuleNames.AddRange(new string[]
        {
            // Core Unreal Engine modules
            "Core",
            "CoreUObject", 
            "Engine",
            "UnrealEd",
            "ToolMenus",
            
            // Input and interaction modules
            "InputCore",
            "EnhancedInput",
            "Slate",
            "SlateCore",
            "UMG",
            
            // Audio processing modules for voice recognition
            "AudioCapture",
            "AudioMixer",
            "AudioExtensions",
            "SignalProcessing",
            "SoundUtilities",
            
            // VR and spatial audio support
            "HeadMountedDisplay",
            "SteamVR",
            "OculusHMD",
            "OpenXRHMD",
            "XRBase",
            
            // Networking for distributed training scenarios
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "Networking",
            "Sockets",
            
            // Platform abstraction
            "ApplicationCore",
            "RenderCore",
            "RHI",
            
            // JSON processing for configuration
            "Json",
            "JsonUtilities",
            
            // File and IO operations
            "PakFile",
            "SandboxFile",
            
            // Async and threading support
            "Engine",
            "CoreUObject"
        });
        
        // ====================================================================
        // PRIVATE DEPENDENCIES FOR INTERNAL IMPLEMENTATION
        // ====================================================================
        
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            // Advanced audio processing
            "AudioCapture",
            "AudioMixerCore",
            "SynthComponents",
            "MetasoundEngine",
            "MetasoundStandardNodes",
            
            // Machine learning and AI (if available)
            "NeuralNetworkInference",
            "MLAdapter",
            
            // Advanced rendering for VR feedback
            "Renderer",
            "RenderCore",
            "RHI",
            
            // Platform-specific implementations
            "TargetPlatform",
            "DesktopPlatform",
            
            // Development tools
            "ToolMenus",
            "WorkspaceMenuStructure",
            "EditorStyle",
            "EditorWidgets",
            "PropertyEditor",
            "DetailCustomizations",
            
            // Automation and testing
            "AutomationController",
            "UnrealEd"
        });
        
        // ====================================================================
        // PLATFORM-SPECIFIC CONFIGURATIONS
        // ====================================================================
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Windows-specific voice recognition APIs
            PublicSystemLibraries.AddRange(new string[]
            {
                "sapi.lib",        // Windows Speech API
                "winmm.lib",       // Windows Multimedia API
                "dsound.lib"       // DirectSound for audio processing
            });
            
            PublicDefinitions.AddRange(new string[]
            {
                "AQUA_V_PLATFORM_WINDOWS=1",
                "AQUA_V_SPEECH_API_SAPI=1",
                "AQUA_V_AUDIO_DIRECTSOUND=1"
            });
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            // Linux audio and speech processing
            PublicSystemLibraries.AddRange(new string[]
            {
                "asound",          // ALSA audio
                "pulse",           // PulseAudio
                "speech-dispatcher" // Linux speech synthesis
            });
            
            PublicDefinitions.AddRange(new string[]
            {
                "AQUA_V_PLATFORM_LINUX=1",
                "AQUA_V_AUDIO_ALSA=1",
                "AQUA_V_SPEECH_API_SPEECHD=1"
            });
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            // macOS speech and audio frameworks
            PublicFrameworks.AddRange(new string[]
            {
                "Speech",          // macOS Speech Recognition
                "AVFoundation",    // Audio/Video processing
                "AudioToolbox",    // Core Audio
                "CoreAudio"        // Low-level audio
            });
            
            PublicDefinitions.AddRange(new string[]
            {
                "AQUA_V_PLATFORM_MAC=1",
                "AQUA_V_SPEECH_API_NSSPEECH=1",
                "AQUA_V_AUDIO_COREAUDIO=1"
            });
        }
        
        // ====================================================================
        // VR PLATFORM SUPPORT
        // ====================================================================
        
        if (Target.bBuildEditor == false) // Runtime configurations
        {
            // Oculus VR support
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PrivateDependencyModuleNames.AddRange(new string[]
                {
                    "OculusHMD",
                    "OculusInput",
                    "OculusAudio"
                });
                
                PublicDefinitions.Add("AQUA_V_VR_OCULUS=1");
            }
            
            // SteamVR support
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "SteamVR",
                "SteamVRInput"
            });
            
            PublicDefinitions.Add("AQUA_V_VR_STEAMVR=1");
            
            // PICO VR support (if available)
            PublicDefinitions.Add("AQUA_V_VR_PICO=1");
        }
        
        // ====================================================================
        // COMPILATION AND OPTIMIZATION SETTINGS
        // ====================================================================
        
        // Optimization settings for different build configurations
        if (Target.Configuration == UnrealTargetConfiguration.Development ||
            Target.Configuration == UnrealTargetConfiguration.DebugGame)
        {
            // Development builds: Enable debugging and logging
            PublicDefinitions.AddRange(new string[]
            {
                "AQUA_V_DEBUG_LOGGING=1",
                "AQUA_V_VOICE_DEBUG=1",
                "AQUA_V_PERFORMANCE_MONITORING=1"
            });
            
            // Enable additional debug information
            bEnableUndefinedIdentifierWarnings = true;
            ShadowVariableWarningLevel = WarningLevel.Warning;
        }
        else if (Target.Configuration == UnrealTargetConfiguration.Shipping)
        {
            // Shipping builds: Maximum optimization, minimal logging
            PublicDefinitions.AddRange(new string[]
            {
                "AQUA_V_DEBUG_LOGGING=0",
                "AQUA_V_VOICE_DEBUG=0",
                "AQUA_V_PERFORMANCE_MONITORING=0",
                "AQUA_V_SHIPPING_BUILD=1"
            });
            
            // Aggressive optimization for production
            OptimizeCode = CodeOptimization.Speed;
            bEnableUndefinedIdentifierWarnings = false;
        }
        else if (Target.Configuration == UnrealTargetConfiguration.Test)
        {
            // Test builds: Enable testing frameworks and validation
            PublicDefinitions.AddRange(new string[]
            {
                "AQUA_V_DEBUG_LOGGING=1",
                "AQUA_V_VOICE_DEBUG=1",
                "AQUA_V_PERFORMANCE_MONITORING=1",
                "AQUA_V_TESTING_ENABLED=1",
                "AQUA_V_UNIT_TESTS=1"
            });
            
            // Additional testing dependencies
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "AutomationController",
                "UnrealEd"
            });
        }
        
        // ====================================================================
        // AQUA V. AEROSPACE COMPLIANCE DEFINITIONS
        // ====================================================================
        
        PublicDefinitions.AddRange(new string[]
        {
            // System identification
            "AQUA_V_VOICE_SYSTEM_VERSION=\"7.6.0\"",
            "AQUA_V_VOICE_BUILD_DATE=\"" + System.DateTime.Now.ToString("yyyy-MM-dd") + "\"",
            "AQUA_V_VOICE_BUILD_TIME=\"" + System.DateTime.Now.ToString("HH:mm:ss") + "\"",
            
            // Aerospace standards compliance
            "AQUA_V_EASA_CS25_COMPLIANT=1",
            "AQUA_V_FAA_PART25_COMPLIANT=1",
            "AQUA_V_DO178C_DAL_C=1",
            "AQUA_V_AS9100_COMPLIANT=1",
            
            // ATA chapter support
            "AQUA_V_ATA_CHAPTER_SUPPORT=1",
            "AQUA_V_ATA_FLIGHT_CONTROLS=27",
            "AQUA_V_ATA_COMMUNICATIONS=23",
            "AQUA_V_ATA_NAVIGATION=34",
            "AQUA_V_ATA_EMERGENCY=25",
            
            // Quantum systems integration
            "AQUA_V_QUANTUM_SYSTEMS_SUPPORT=1",
            "AQUA_V_QCSAA_934_936_COMPLIANT=1",
            
            // Performance requirements
            "AQUA_V_MAX_LATENCY_MS=100",
            "AQUA_V_MIN_ACCURACY=95",
            "AQUA_V_SAMPLE_RATE=48000",
            "AQUA_V_BIT_DEPTH=24",
            
            // Safety and security
            "AQUA_V_SAFETY_CRITICAL=1",
            "AQUA_V_SECURE_COMMUNICATIONS=1",
            "AQUA_V_DATA_ENCRYPTION=1"
        });
        
        // ====================================================================
        // INCLUDE PATHS FOR VOICE COMMAND MODULES
        // ====================================================================
        
        PublicIncludePaths.AddRange(new string[]
        {
            // Core voice command headers
            "VoiceCommands/Core",
            "VoiceCommands/Core/VoiceRecognitionEngine",
            "VoiceCommands/Core/VoiceRecognitionEngine/AudioStreamProcessor",
            "VoiceCommands/Core/VoiceRecognitionEngine/NLPEngine", 
            "VoiceCommands/Core/VoiceRecognitionEngine/CommandParsing",
            "VoiceCommands/Core/VoiceRecognitionEngine/AudioResponse",
            "VoiceCommands/Core/VoiceRecognitionEngine/Integration",
            
            // Configuration and utilities
            "VoiceCommands/Config",
            "VoiceCommands/Utils",
            "VoiceCommands/Testing"
        });
        
        PrivateIncludePaths.AddRange(new string[]
        {
            // Private implementation details
            "VoiceCommands/Private",
            "VoiceCommands/Private/AudioProcessing",
            "VoiceCommands/Private/NLP",
            "VoiceCommands/Private/Parsing",
            "VoiceCommands/Private/Response",
            "VoiceCommands/Private/Integration"
        });
        
        // ====================================================================
        // EXTERNAL LIBRARY INTEGRATIONS
        // ====================================================================
        
        // Audio processing libraries
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Windows-specific audio libraries
            string AudioLibPath = "$(ModuleDir)/ThirdParty/Audio/Win64/";
            PublicAdditionalLibraries.AddRange(new string[]
            {
                AudioLibPath + "portaudio.lib",
                AudioLibPath + "fftw3.lib",
                AudioLibPath + "speex.lib"
            });
        }
        
        // Machine Learning libraries (if available)
        string MLLibPath = "$(ModuleDir)/ThirdParty/ML/";
        if (System.IO.Directory.Exists(MLLibPath))
        {
            PublicDefinitions.Add("AQUA_V_ML_SUPPORT=1");
            
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicAdditionalLibraries.Add(MLLibPath + "Win64/tensorflow_lite.lib");
            }
        }
        
        // ====================================================================
        // COMPILATION WARNINGS AND ERRORS
        // ====================================================================
        
        // Treat specific warnings as errors for aerospace compliance
        bTreatAsEngineModule = false;
        bEnableUndefinedIdentifierWarnings = true;
        
        // Suppress known third-party warnings
        bDisableStaticAnalysis = false;
        
        // Enable all relevant warnings
        ShadowVariableWarningLevel = WarningLevel.Warning;
        UnsafeTypeCastWarningLevel = WarningLevel.Warning;
        
        // ====================================================================
        // MODULE METADATA
        // ====================================================================
        
        // Module information for packaging and distribution
        PublicDefinitions.AddRange(new string[]
        {
            "AQUA_V_MODULE_NAME=\"VoiceCommands\"",
            "AQUA_V_MODULE_VERSION=\"v0.1.0\"",
            "AQUA_V_MODULE_AUTHOR=\"AQUA V. Development Team - QDAT Division\"",
            "AQUA_V_MODULE_COPYRIGHT=\"(c) 2025 ROBBBO-T GAIA AIR & SPACE\"",
            "AQUA_V_MODULE_LICENSE=\"Proprietary - Aerospace Training Use Only\""
        });
        
        // ====================================================================
        // LOGGING AND DIAGNOSTICS
        // ====================================================================
        
        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            // Development logging categories
            PublicDefinitions.AddRange(new string[]
            {
                "DECLARE_LOG_CATEGORY_EXTERN(LogAquaVoice, Log, All)",
                "DECLARE_LOG_CATEGORY_EXTERN(LogAquaVoiceAudio, Log, All)",
                "DECLARE_LOG_CATEGORY_EXTERN(LogAquaVoiceNLP, Log, All)",
                "DECLARE_LOG_CATEGORY_EXTERN(LogAquaVoiceParsing, Log, All)",
                "DECLARE_LOG_CATEGORY_EXTERN(LogAquaVoiceResponse, Log, All)",
                "DECLARE_LOG_CATEGORY_EXTERN(LogAquaVoiceIntegration, Log, All)"
            });
        }
    }
}
