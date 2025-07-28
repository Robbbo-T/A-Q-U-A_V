/**
 * AQUA V. Natural Language Processing Engine - Header
 * AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-01-02-NLPENGINE-QDAT-v7.6.0.h
 * 
 * Advanced natural language processing engine for aerospace voice commands
 * Handles intent classification, entity extraction, and contextual understanding
 * 
 * @author AQUA V. Corporation
 * @version 7.6.0
 * @date July 2025
 */

#ifndef AQUA_V_NLP_ENGINE_H
#define AQUA_V_NLP_ENGINE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <memory>

namespace AQUA_V {
namespace VoiceCommands {
namespace NLP {

/**
 * @brief Entity extracted from text input
 */
struct Entity {
    std::string type;           ///< Entity type (e.g., "number", "altitude", "heading")
    std::string value;          ///< Entity value as string
    float confidence;           ///< Confidence score [0.0-1.0]
    size_t start_pos;          ///< Start position in original text
    size_t end_pos;            ///< End position in original text
    
    Entity() : confidence(0.0f), start_pos(0), end_pos(0) {}
};

/**
 * @brief Intent classification result
 */
struct IntentResult {
    std::string intent;         ///< Classified intent
    float confidence;           ///< Confidence score [0.0-1.0]
    
    IntentResult() : confidence(0.0f) {}
};

/**
 * @brief Complete NLP processing result
 */
struct NLPResult {
    std::string input_text;                    ///< Original input text
    std::string intent;                        ///< Classified intent
    float intent_confidence;                   ///< Intent confidence [0.0-1.0]
    std::vector<Entity> entities;             ///< Extracted entities
    bool success;                             ///< Processing success flag
    std::string error_message;                ///< Error description if failed
    std::chrono::system_clock::time_point timestamp; ///< Processing timestamp
    
    NLPResult() : intent_confidence(0.0f), success(false) {}
};

/**
 * @brief Context entry for maintaining conversation state
 */
struct ContextEntry {
    std::string intent;                        ///< Intent from previous interaction
    std::vector<Entity> entities;             ///< Entities from previous interaction
    std::chrono::system_clock::time_point timestamp; ///< When this entry was created
    float confidence;                          ///< Confidence of this entry
    
    ContextEntry() : confidence(0.0f) {}
};

/**
 * @brief NLP Engine configuration
 */
struct NLPConfig {
    float confidence_threshold;     ///< Minimum confidence for valid results
    size_t context_window_size;    ///< Number of previous interactions to remember
    bool enable_context_boost;     ///< Whether to boost confidence based on context
    bool enable_spell_correction;  ///< Whether to attempt spell correction
    std::string language_code;     ///< Language code (e.g., "en-US")
    
    NLPConfig() 
        : confidence_threshold(0.75f)
        , context_window_size(5)
        , enable_context_boost(true)
        , enable_spell_correction(false)
        , language_code("en-US") 
    {}
};

/**
 * @brief Advanced Natural Language Processing Engine
 * 
 * This class provides sophisticated NLP capabilities specifically designed
 * for aerospace voice command processing. It handles:
 * - Intent classification using pattern matching and context
 * - Entity extraction for aerospace-specific terms
 * - Context management for multi-turn interactions
 * - Confidence scoring and validation
 * 
 * The engine is optimized for real-time processing with low latency
 * and high accuracy for mission-critical aerospace operations.
 */
class NLPEngine {
public:
    /**
     * @brief Default constructor
     */
    NLPEngine();
    
    /**
     * @brief Destructor
     */
    ~NLPEngine();
    
    /**
     * @brief Initialize the NLP engine with configuration
     * @param config Configuration parameters
     * @return true if initialization successful, false otherwise
     */
    bool Initialize(const NLPConfig& config);
    
    /**
     * @brief Process text input and extract intent and entities
     * @param text Input text to process
     * @return Complete NLP processing result
     */
    NLPResult ProcessText(const std::string& text);
    
    /**
     * @brief Check if engine is initialized and ready
     * @return true if initialized, false otherwise
     */
    bool IsInitialized() const { return m_initialized; }
    
    /**
     * @brief Get current configuration
     * @return Current NLP configuration
     */
    const NLPConfig& GetConfig() const { return m_config; }
    
    /**
     * @brief Update confidence threshold
     * @param threshold New confidence threshold [0.0-1.0]
     */
    void SetConfidenceThreshold(float threshold) { 
        m_confidenceThreshold = std::max(0.0f, std::min(1.0f, threshold)); 
    }
    
    /**
     * @brief Get current confidence threshold
     * @return Current confidence threshold
     */
    float GetConfidenceThreshold() const { return m_confidenceThreshold; }
    
    /**
     * @brief Clear context history
     */
    void ClearContext() { m_contextHistory.clear(); }
    
    /**
     * @brief Get context history size
     * @return Number of entries in context history
     */
    size_t GetContextSize() const { return m_contextHistory.size(); }

private:
    // Core processing methods
    std::string PreprocessText(const std::string& text);
    IntentResult ClassifyIntent(const std::string& text);
    std::vector<Entity> ExtractEntities(const std::string& text, const std::string& intent);
    void UpdateContext(const NLPResult& result);
    bool ValidateResult(const NLPResult& result);
    
    // Helper methods
    float CalculatePatternConfidence(const std::string& text, const std::string& pattern);
    float CalculateContextualBoost(const std::string& intent);
    std::string DetermineNumberType(const std::string& number, const std::string& intent);
    bool ValidateIntentEntityConsistency(const std::string& intent, const std::vector<Entity>& entities);
    bool HasRequiredEntities(const std::string& intent, const std::vector<Entity>& entities);
    
    // Initialization methods
    bool LoadLanguageModels();
    bool InitializeIntentClassifier();
    bool InitializeEntityExtractor();
    bool InitializeContextManager();
    void InitializeModels();
    
    // Utility methods
    NLPResult CreateErrorResult(const std::string& error);
    void LogProcessingResult(const NLPResult& result);
    void Cleanup();
    
    // Member variables
    bool m_initialized;                          ///< Initialization status
    NLPConfig m_config;                         ///< Engine configuration
    float m_confidenceThreshold;               ///< Minimum confidence threshold
    size_t m_contextWindowSize;                ///< Context window size
    std::vector<ContextEntry> m_contextHistory; ///< Context history buffer
    
    // Disable copy construction and assignment
    NLPEngine(const NLPEngine&) = delete;
    NLPEngine& operator=(const NLPEngine&) = delete;
};

/**
 * @brief Intent types supported by the NLP engine
 */
namespace Intents {
    // Flight Control Intents
    constexpr const char* FLIGHT_CONTROL_ALTITUDE = "flight_control_altitude";
    constexpr const char* FLIGHT_CONTROL_HEADING = "flight_control_heading";
    constexpr const char* FLIGHT_CONTROL_SPEED = "flight_control_speed";
    constexpr const char* FLIGHT_CONTROL_FLAPS = "flight_control_flaps";
    constexpr const char* FLIGHT_CONTROL_GEAR = "flight_control_gear";
    constexpr const char* FLIGHT_CONTROL_AUTOPILOT = "flight_control_autopilot";
    
    // Navigation Intents
    constexpr const char* NAVIGATION_WAYPOINT = "navigation_waypoint";
    constexpr const char* NAVIGATION_COURSE = "navigation_course";
    constexpr const char* NAVIGATION_DIRECT = "navigation_direct";
    
    // Communication Intents
    constexpr const char* COMMUNICATION_RADIO = "communication_radio";
    constexpr const char* COMMUNICATION_TRANSPONDER = "communication_transponder";
    constexpr const char* COMMUNICATION_FREQUENCY = "communication_frequency";
    
    // Quantum System Intents
    constexpr const char* QUANTUM_QNS = "quantum_qns";
    constexpr const char* QUANTUM_QPU = "quantum_qpu";
    constexpr const char* QUANTUM_QDS = "quantum_qds";
    
    // Emergency Intents
    constexpr const char* EMERGENCY_PROCEDURE = "emergency_procedure";
    constexpr const char* EMERGENCY_MAYDAY = "emergency_mayday";
    constexpr const char* EMERGENCY_PAN_PAN = "emergency_pan_pan";
    
    // System Intents
    constexpr const char* SYSTEM_STATUS = "system_status";
    constexpr const char* SYSTEM_HELP = "system_help";
    constexpr const char* SYSTEM_CANCEL = "system_cancel";
    
    // Unknown/Error
    constexpr const char* UNKNOWN = "unknown";
    constexpr const char* ERROR = "error";
}

/**
 * @brief Entity types recognized by the NLP engine
 */
namespace EntityTypes {
    // Numeric entities
    constexpr const char* NUMBER = "number";
    constexpr const char* ALTITUDE = "altitude";
    constexpr const char* HEADING = "heading";
    constexpr const char* SPEED = "speed";
    constexpr const char* FREQUENCY = "frequency";
    constexpr const char* TIME = "time";
    constexpr const char* DISTANCE = "distance";
    
    // Direction entities
    constexpr const char* DIRECTION = "direction";
    constexpr const char* BEARING = "bearing";
    
    // Identifier entities
    constexpr const char* IDENTIFIER = "identifier";
    constexpr const char* WAYPOINT = "waypoint";
    constexpr const char* CALLSIGN = "callsign";
    constexpr const char* AIRPORT_CODE = "airport_code";
    
    // System entities
    constexpr const char* SYSTEM_NAME = "system_name";
    constexpr const char* COMMAND_NAME = "command_name";
    
    // Quantum entities
    constexpr const char* QUANTUM_STATE = "quantum_state";
    constexpr const char* QUANTUM_OPERATION = "quantum_operation";
}

} // namespace NLP
} // namespace VoiceCommands
} // namespace AQUA_V

#endif // AQUA_V_NLP_ENGINE_H
