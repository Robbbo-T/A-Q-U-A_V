/**
 * ============================================================================
 * AQUA V. - Natural Language Processing Engine Header
 * ============================================================================
 * 
 * Document ID: AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-320-50-01-TPL-TEC-NLPN-001-QDAT-v0.1.0
 * 
 * Nomenclature Breakdown (AQUA V. Official System v3.1):
 * - LÍNEA:     AMP (AMPEL360 Products)
 * - PRODUCTO:  EVTOL (Electric Vertical Take-Off and Landing Aircraft)
 * - MSN:       25SVD0001 (2025 Silicon Valley Development Unit 0001)
 * - FASE:      DEV (Development Phase)
 * - ALI/BOB:   BOB (Build-Operate-Build Digital Systems)
 * - ARTIFACT:  TEC (Technical Artifacts)
 * - TYPE:      SM (Software Module)
 * - UTCS:      DTCEC-320-50-01 (Digital Twin, Cloud & Edge Computing - AI/ML for DT - AI Vision Software)
 * - CÓDIGO:    000-00-01 (Primary component within UTCS)
 * - TEMPLATE:  TPL-TEC-NLPN-001 (Technical Template - NLP Engine - Instance 001)
 * - QD:        QDAT (Q-Data Governance Division)
 * - VERSIÓN:   v0.1.0 (Initial development version)
 * 
 * Description: Advanced Natural Language Processing Engine for aerospace voice commands
 *              Handles intent classification, entity extraction, and contextual understanding
 *              specifically designed for eVTOL pilot training simulations
 * 
 * Digital Thread Integration:
 * - Parent System: AMPEL360 Training VR System
 * - Component: Voice Recognition Engine Core
 * - Dependencies: Audio Stream Processor (DTCEC-341), Command Parser (DTCEC-343)
 * - Interfaces: Unreal Engine 5.0+, AQUA V. Quantum Systems
 * 
 * Compliance:
 * - EASA CS-25 Voice Command Systems
 * - FAA Part 25 Human Factors Requirements
 * - DO-178C Software Considerations (DAL-C)
 * - AS9100/ISO 9001 Quality Management
 * - AQUA V. Digital Thread Standards v3.1
 * 
 * Author:      AQUA V. Development Team - QDAT Division
 * Date:        2025-07-28
 * Copyright:   (c) 2025 ROBBBO-T GAIA AIR & SPACE
 * License:     Proprietary - Aerospace Training Use Only
 * 
 * ============================================================================
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <memory>

namespace AQUA_V {
namespace VoiceCommands {
namespace NLP {

/**
 * Forward Declarations
 */
struct NLPConfig;
struct NLPResult;
struct Entity;
struct IntentResult;
struct ContextEntry;

/**
 * ============================================================================
 * CORE DATA STRUCTURES
 * ============================================================================
 */

/**
 * NLP Configuration Structure
 * Contains all parameters for initializing the NLP engine
 */
struct NLPConfig {
    float confidence_threshold = 0.75f;        // Minimum confidence for intent classification
    size_t context_window_size = 5;            // Number of previous commands to maintain in context
    std::string model_path = "";               // Path to trained models
    std::string language_code = "en-US-aerospace"; // Language and domain specification
    bool enable_context_boost = true;          // Enable contextual confidence boosting
    bool enable_entity_validation = true;      // Enable entity consistency validation
    bool debug_logging = false;                // Enable detailed debug logging
    
    // Aerospace-specific configuration
    bool enable_emergency_priority = true;     // Prioritize emergency command detection
    bool enable_quantum_terminology = true;    // Enable quantum systems vocabulary
    bool enable_ata_chapter_mapping = true;    // Enable ATA chapter categorization
    float emergency_confidence_boost = 0.2f;   // Additional confidence for emergency commands
};

/**
 * Entity Structure
 * Represents extracted entities from voice commands
 */
struct Entity {
    std::string type;           // Entity type (altitude, heading, frequency, etc.)
    std::string value;          // Extracted value
    float confidence;           // Confidence score (0.0 to 1.0)
    size_t start_pos;          // Start position in original text
    size_t end_pos;            // End position in original text
    std::string normalized_value; // Normalized/standardized value
    
    Entity() : confidence(0.0f), start_pos(0), end_pos(0) {}
};

/**
 * Intent Classification Result
 * Contains the classified intent and confidence score
 */
struct IntentResult {
    std::string intent;         // Classified intent
    float confidence;           // Confidence score (0.0 to 1.0)
    std::string category;       // ATA chapter or system category
    std::string priority;       // Command priority level
    
    IntentResult() : confidence(0.0f) {}
};

/**
 * Context Entry Structure
 * Represents a single entry in the conversation context
 */
struct ContextEntry {
    std::string intent;                             // Previous intent
    std::vector<Entity> entities;                   // Previous entities
    std::chrono::system_clock::time_point timestamp; // When the command was processed
    float confidence;                               // Confidence of the previous command
    
    ContextEntry() : confidence(0.0f) {}
};

/**
 * NLP Processing Result
 * Complete result of natural language processing
 */
struct NLPResult {
    bool success = false;                           // Processing success flag
    std::string input_text;                         // Original input text
    std::string preprocessed_text;                  // Cleaned and normalized text
    std::string intent;                             // Classified intent
    float intent_confidence = 0.0f;                // Intent confidence score
    std::vector<Entity> entities;                   // Extracted entities
    std::string error_message;                      // Error details if processing failed
    std::chrono::system_clock::time_point timestamp; // Processing timestamp
    
    // Aerospace-specific fields
    std::string ata_chapter;                        // Relevant ATA chapter
    std::string command_priority;                   // Command priority level
    bool requires_confirmation = false;             // Whether command needs confirmation
    float safety_criticality = 0.0f;              // Safety criticality score (0.0 to 1.0)
};

/**
 * ============================================================================
 * MAIN NLP ENGINE CLASS
 * ============================================================================
 */

/**
 * Natural Language Processing Engine for AQUA V. Voice Commands
 * 
 * This class provides comprehensive NLP capabilities specifically designed for
 * aerospace training environments, including:
 * - Intent classification with aerospace domain knowledge
 * - Entity extraction for flight parameters and identifiers
 * - Contextual understanding for multi-turn conversations
 * - Safety-critical command prioritization
 * - Integration with quantum systems terminology
 * 
 * Thread Safety: This class is thread-safe for read operations but requires
 * external synchronization for concurrent write operations.
 */
class NLPEngine {
public:
    /**
     * Constructor
     * Initializes the NLP engine with default configuration
     */
    NLPEngine();
    
    /**
     * Destructor
     * Cleans up resources and saves state if necessary
     */
    ~NLPEngine();
    
    /**
     * Initialize the NLP engine with specified configuration
     * @param config Configuration parameters for the NLP engine
     * @return true if initialization successful, false otherwise
     */
    bool Initialize(const NLPConfig& config);
    
    /**
     * Process natural language text and extract intent and entities
     * @param text Input text from voice recognition
     * @return Complete NLP processing result
     */
    NLPResult ProcessText(const std::string& text);
    
    /**
     * Get current configuration
     * @return Current NLP configuration
     */
    const NLPConfig& GetConfiguration() const { return m_config; }
    
    /**
     * Update confidence threshold during runtime
     * @param threshold New confidence threshold (0.0 to 1.0)
     */
    void SetConfidenceThreshold(float threshold);
    
    /**
     * Get processing statistics
     * @return Map of processing statistics
     */
    std::unordered_map<std::string, float> GetProcessingStatistics() const;
    
    /**
     * Clear conversation context
     */
    void ClearContext();
    
    /**
     * Check if engine is properly initialized
     * @return true if initialized and ready to process
     */
    bool IsInitialized() const { return m_initialized; }

private:
    /**
     * ========================================================================
     * PRIVATE MEMBER VARIABLES
     * ========================================================================
     */
    
    bool m_initialized;                                 // Initialization status
    NLPConfig m_config;                                 // Current configuration
    float m_confidenceThreshold;                       // Active confidence threshold
    size_t m_contextWindowSize;                        // Context window size
    std::vector<ContextEntry> m_contextHistory;        // Conversation context
    
    // Processing statistics
    mutable std::unordered_map<std::string, float> m_statistics;
    
    /**
     * ========================================================================
     * PRIVATE PROCESSING METHODS
     * ========================================================================
     */
    
    /**
     * Preprocess input text for better recognition
     * @param text Raw input text
     * @return Cleaned and normalized text
     */
    std::string PreprocessText(const std::string& text);
    
    /**
     * Classify intent from preprocessed text
     * @param text Preprocessed text
     * @return Intent classification result
     */
    IntentResult ClassifyIntent(const std::string& text);
    
    /**
     * Extract entities from text based on intent
     * @param text Preprocessed text
     * @param intent Classified intent
     * @return Vector of extracted entities
     */
    std::vector<Entity> ExtractEntities(const std::string& text, const std::string& intent);
    
    /**
     * Update conversation context with new processing result
     * @param result Latest processing result
     */
    void UpdateContext(const NLPResult& result);
    
    /**
     * Validate processing result for consistency and completeness
     * @param result Processing result to validate
     * @return true if result is valid
     */
    bool ValidateResult(const NLPResult& result);
    
    /**
     * ========================================================================
     * CONFIDENCE AND SCORING METHODS
     * ========================================================================
     */
    
    /**
     * Calculate confidence score for pattern matching
     * @param text Input text
     * @param pattern Matched pattern
     * @return Confidence score (0.0 to 1.0)
     */
    float CalculatePatternConfidence(const std::string& text, const std::string& pattern);
    
    /**
     * Calculate contextual confidence boost
     * @param intent Current intent
     * @return Contextual boost value
     */
    float CalculateContextualBoost(const std::string& intent);
    
    /**
     * Determine safety criticality of a command
     * @param intent Classified intent
     * @param entities Extracted entities
     * @return Safety criticality score (0.0 to 1.0)
     */
    float CalculateSafetyCriticality(const std::string& intent, const std::vector<Entity>& entities);
    
    /**
     * ========================================================================
     * ENTITY PROCESSING METHODS
     * ========================================================================
     */
    
    /**
     * Determine entity type based on value and context
     * @param number Extracted numeric value
     * @param intent Current intent
     * @return Entity type classification
     */
    std::string DetermineNumberType(const std::string& number, const std::string& intent);
    
    /**
     * Normalize entity values to standard formats
     * @param entity Entity to normalize
     * @return Normalized entity
     */
    Entity NormalizeEntity(const Entity& entity);
    
    /**
     * ========================================================================
     * VALIDATION METHODS
     * ========================================================================
     */
    
    /**
     * Validate consistency between intent and extracted entities
     * @param intent Classified intent
     * @param entities Extracted entities
     * @return true if consistent
     */
    bool ValidateIntentEntityConsistency(const std::string& intent, const std::vector<Entity>& entities);
    
    /**
     * Check if required entities are present for the given intent
     * @param intent Classified intent
     * @param entities Extracted entities
     * @return true if all required entities are present
     */
    bool HasRequiredEntities(const std::string& intent, const std::vector<Entity>& entities);
    
    /**
     * ========================================================================
     * INITIALIZATION AND CLEANUP METHODS
     * ========================================================================
     */
    
    /**
     * Load language models and patterns
     * @return true if loading successful
     */
    bool LoadLanguageModels();
    
    /**
     * Initialize intent classification system
     * @return true if initialization successful
     */
    bool InitializeIntentClassifier();
    
    /**
     * Initialize entity extraction system
     * @return true if initialization successful
     */
    bool InitializeEntityExtractor();
    
    /**
     * Initialize context management system
     * @return true if initialization successful
     */
    bool InitializeContextManager();
    
    /**
     * Initialize static models and data
     */
    void InitializeModels();
    
    /**
     * Create error result with specified message
     * @param error Error message
     * @return Error result structure
     */
    NLPResult CreateErrorResult(const std::string& error);
    
    /**
     * Log processing result for debugging and analysis
     * @param result Processing result to log
     */
    void LogProcessingResult(const NLPResult& result);
    
    /**
     * Cleanup resources and save state
     */
    void Cleanup();
    
    /**
     * Update processing statistics
     * @param key Statistic key
     * @param value Statistic value
     */
    void UpdateStatistic(const std::string& key, float value) const;
};

/**
 * ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================
 */

/**
 * Load NLP configuration from JSON file
 * @param configPath Path to configuration file
 * @return Loaded configuration
 */
NLPConfig LoadNLPConfigFromFile(const std::string& configPath);

/**
 * Save NLP configuration to JSON file
 * @param config Configuration to save
 * @param configPath Path to configuration file
 * @return true if saving successful
 */
bool SaveNLPConfigToFile(const NLPConfig& config, const std::string& configPath);

/**
 * Create default NLP configuration for aerospace applications
 * @return Default configuration
 */
NLPConfig CreateDefaultAerospaceConfig();

/**
 * Validate entity value against expected format
 * @param entity Entity to validate
 * @param expectedFormat Expected format pattern
 * @return true if entity matches expected format
 */
bool ValidateEntityFormat(const Entity& entity, const std::string& expectedFormat);

/**
 * Convert intent to ATA chapter code
 * @param intent Intent classification
 * @return Corresponding ATA chapter code
 */
std::string IntentToATAChapter(const std::string& intent);

/**
 * Determine command priority from intent and entities
 * @param intent Intent classification
 * @param entities Extracted entities
 * @return Command priority level
 */
std::string DetermineCommandPriority(const std::string& intent, const std::vector<Entity>& entities);

} // namespace NLP
} // namespace VoiceCommands
} // namespace AQUA_V

/**
 * ============================================================================
 * COMPILE-TIME CONSTANTS AND MACROS
 * ============================================================================
 */

// NLP Engine version information
#define AQUA_V_NLP_ENGINE_VERSION "0.1.0"
#define AQUA_V_NLP_ENGINE_BUILD_DATE "2025-07-28"

// Configuration limits
#define AQUA_V_NLP_MAX_CONTEXT_SIZE 10
#define AQUA_V_NLP_MIN_CONFIDENCE 0.1f
#define AQUA_V_NLP_MAX_CONFIDENCE 1.0f
#define AQUA_V_NLP_DEFAULT_CONFIDENCE 0.75f

// Entity type constants
#define AQUA_V_ENTITY_TYPE_ALTITUDE "altitude"
#define AQUA_V_ENTITY_TYPE_HEADING "heading"
#define AQUA_V_ENTITY_TYPE_SPEED "speed"
#define AQUA_V_ENTITY_TYPE_FREQUENCY "frequency"
#define AQUA_V_ENTITY_TYPE_IDENTIFIER "identifier"
#define AQUA_V_ENTITY_TYPE_DIRECTION "direction"
#define AQUA_V_ENTITY_TYPE_NUMBER "number"

// Intent category constants
#define AQUA_V_INTENT_FLIGHT_CONTROL "flight_control"
#define AQUA_V_INTENT_COMMUNICATION "communication"
#define AQUA_V_INTENT_NAVIGATION "navigation"
#define AQUA_V_INTENT_QUANTUM_SYSTEMS "quantum_systems"
#define AQUA_V_INTENT_EMERGENCY "emergency"
#define AQUA_V_INTENT_TRAINING "training"

/**
 * ============================================================================
 * END OF HEADER FILE
 * ============================================================================
 * 
 * This header file provides the complete interface for the AQUA V. Natural
 * Language Processing Engine, designed specifically for aerospace training
 * applications with full compliance to:
 * 
 * - AQUA V. Official Nomenclature System v3.1
 * - Digital Thread Integration Standards
 * - Aerospace Software Development Standards (DO-178C)
 * - Safety-Critical System Requirements
 * 
 * The implementation follows industry best practices for NLP systems while
 * maintaining the specific requirements of aerospace training environments.
 * 
 * ============================================================================
 */
