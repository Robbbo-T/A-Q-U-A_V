/**
 * ============================================================================
 * AQUA V. - Natural Language Processing Engine Implementation
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

#include "AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-320-50-01-TPL-TEC-NLPN-001-QDAT-v0.1.0.h"
#include <algorithm>
#include <regex>
#include <unordered_map>
#include <memory>

namespace AQUA_V {
namespace VoiceCommands {
namespace NLP {

// Static aerospace terminology dictionary
const std::unordered_map<std::string, std::string> AerospaceTerminology = {
    // Flight Control Terms
    {"altitude", "flight_level"},
    {"heading", "bearing"},
    {"airspeed", "velocity"},
    {"throttle", "power_setting"},
    {"flaps", "high_lift_devices"},
    {"gear", "landing_gear"},
    {"autopilot", "automatic_flight_control"},
    
    // Navigation Terms
    {"waypoint", "navigation_fix"},
    {"course", "track"},
    {"bearing", "radial"},
    {"distance", "range"},
    {"eta", "estimated_time_arrival"},
    
    // Communications
    {"frequency", "radio_channel"},
    {"transponder", "ssr_code"},
    {"squawk", "transponder_code"},
    
    // Quantum Systems
    {"qns", "quantum_navigation_system"},
    {"qpu", "quantum_processing_unit"},
    {"qds", "quantum_data_storage"},
    {"entanglement", "quantum_correlation"},
    {"superposition", "quantum_state"}
};

// Intent patterns for aerospace commands
const std::unordered_map<std::string, std::vector<std::string>> IntentPatterns = {
    {"flight_control_altitude", {
        "climb to \\d+", "descend to \\d+", "maintain \\d+", "altitude \\d+", "flight level \\d+"
    }},
    {"flight_control_heading", {
        "turn left \\d+", "turn right \\d+", "heading \\d+", "turn to \\d+", "steer \\d+"
    }},
    {"flight_control_speed", {
        "increase speed", "reduce speed", "airspeed \\d+", "mach \\d+", "velocity \\d+"
    }},
    {"communication_radio", {
        "contact \\w+", "frequency \\d+\\.\\d+", "radio \\w+", "call \\w+"
    }},
    {"navigation_waypoint", {
        "navigate to \\w+", "direct \\w+", "proceed to \\w+", "waypoint \\w+"
    }},
    {"quantum_qns", {
        "activate qns", "quantum navigation", "qns calibrate", "qns status"
    }},
    {"quantum_qpu", {
        "quantum processing", "qpu initialize", "execute quantum", "qpu status"
    }},
    {"emergency_procedure", {
        "emergency", "mayday", "pan pan", "emergency descent", "emergency landing"
    }}
};

NLPEngine::NLPEngine() 
    : m_initialized(false)
    , m_confidenceThreshold(0.75f)
    , m_contextWindowSize(5)
{
    InitializeModels();
}

NLPEngine::~NLPEngine() {
    Cleanup();
}

bool NLPEngine::Initialize(const NLPConfig& config) {
    m_config = config;
    m_confidenceThreshold = config.confidence_threshold;
    m_contextWindowSize = config.context_window_size;
    
    // Load language models
    if (!LoadLanguageModels()) {
        return false;
    }
    
    // Initialize intent classifier
    if (!InitializeIntentClassifier()) {
        return false;
    }
    
    // Initialize entity extractor
    if (!InitializeEntityExtractor()) {
        return false;
    }
    
    // Initialize context manager
    if (!InitializeContextManager()) {
        return false;
    }
    
    m_initialized = true;
    return true;
}

NLPResult NLPEngine::ProcessText(const std::string& text) {
    if (!m_initialized) {
        return CreateErrorResult("NLP Engine not initialized");
    }
    
    NLPResult result;
    result.input_text = text;
    result.timestamp = std::chrono::system_clock::now();
    
    try {
        // Pre-process text
        std::string processedText = PreprocessText(text);
        
        // Extract intent
        IntentResult intentResult = ClassifyIntent(processedText);
        result.intent = intentResult.intent;
        result.intent_confidence = intentResult.confidence;
        
        // Extract entities
        result.entities = ExtractEntities(processedText, result.intent);
        
        // Update context
        UpdateContext(result);
        
        // Post-process and validate
        result.success = ValidateResult(result);
        
        if (result.success) {
            LogProcessingResult(result);
        }
        
    } catch (const std::exception& e) {
        result = CreateErrorResult(std::string("Processing error: ") + e.what());
    }
    
    return result;
}

std::string NLPEngine::PreprocessText(const std::string& text) {
    std::string processed = text;
    
    // Convert to lowercase
    std::transform(processed.begin(), processed.end(), processed.begin(), ::tolower);
    
    // Remove unnecessary punctuation (keep important ones like decimal points)
    std::regex punct_regex("[^a-zA-Z0-9\\s\\.\\-]");
    processed = std::regex_replace(processed, punct_regex, " ");
    
    // Normalize whitespace
    std::regex ws_regex("\\s+");
    processed = std::regex_replace(processed, ws_regex, " ");
    
    // Trim
    processed.erase(0, processed.find_first_not_of(" \t\n\r"));
    processed.erase(processed.find_last_not_of(" \t\n\r") + 1);
    
    // Apply aerospace terminology normalization
    for (const auto& term_pair : AerospaceTerminology) {
        std::regex term_regex("\\b" + term_pair.first + "\\b");
        processed = std::regex_replace(processed, term_regex, term_pair.second);
    }
    
    return processed;
}

IntentResult NLPEngine::ClassifyIntent(const std::string& text) {
    IntentResult result;
    result.confidence = 0.0f;
    
    float maxConfidence = 0.0f;
    std::string bestIntent = "unknown";
    
    // Pattern-based intent classification
    for (const auto& intent_pair : IntentPatterns) {
        for (const auto& pattern : intent_pair.second) {
            std::regex pattern_regex(pattern, std::regex_constants::icase);
            if (std::regex_search(text, pattern_regex)) {
                float confidence = CalculatePatternConfidence(text, pattern);
                if (confidence > maxConfidence) {
                    maxConfidence = confidence;
                    bestIntent = intent_pair.first;
                }
            }
        }
    }
    
    // Apply context-based confidence boost
    if (!m_contextHistory.empty()) {
        float contextBoost = CalculateContextualBoost(bestIntent);
        maxConfidence = std::min(1.0f, maxConfidence + contextBoost);
    }
    
    result.intent = bestIntent;
    result.confidence = maxConfidence;
    
    return result;
}

std::vector<Entity> NLPEngine::ExtractEntities(const std::string& text, const std::string& intent) {
    std::vector<Entity> entities;
    
    // Number extraction
    std::regex number_regex("\\b(\\d+(?:\\.\\d+)?)\\b");
    std::sregex_iterator numbers_begin(text.begin(), text.end(), number_regex);
    std::sregex_iterator numbers_end;
    
    for (std::sregex_iterator i = numbers_begin; i != numbers_end; ++i) {
        Entity entity;
        entity.type = DetermineNumberType((*i).str(), intent);
        entity.value = (*i).str();
        entity.confidence = 0.9f;
        entity.start_pos = i->position();
        entity.end_pos = i->position() + i->length();
        entities.push_back(entity);
    }
    
    // Direction extraction
    std::regex direction_regex("\\b(left|right|north|south|east|west)\\b");
    std::sregex_iterator directions_begin(text.begin(), text.end(), direction_regex);
    std::sregex_iterator directions_end;
    
    for (std::sregex_iterator i = directions_begin; i != directions_end; ++i) {
        Entity entity;
        entity.type = "direction";
        entity.value = (*i).str();
        entity.confidence = 0.95f;
        entity.start_pos = i->position();
        entity.end_pos = i->position() + i->length();
        entities.push_back(entity);
    }
    
    // Waypoint/identifier extraction
    std::regex identifier_regex("\\b([A-Z]{2,5}\\d*)\\b");
    std::sregex_iterator identifiers_begin(text.begin(), text.end(), identifier_regex);
    std::sregex_iterator identifiers_end;
    
    for (std::sregex_iterator i = identifiers_begin; i != identifiers_end; ++i) {
        Entity entity;
        entity.type = "identifier";
        entity.value = (*i).str();
        entity.confidence = 0.8f;
        entity.start_pos = i->position();
        entity.end_pos = i->position() + i->length();
        entities.push_back(entity);
    }
    
    return entities;
}

void NLPEngine::UpdateContext(const NLPResult& result) {
    ContextEntry entry;
    entry.intent = result.intent;
    entry.entities = result.entities;
    entry.timestamp = result.timestamp;
    entry.confidence = result.intent_confidence;
    
    m_contextHistory.push_back(entry);
    
    // Maintain context window size
    if (m_contextHistory.size() > m_contextWindowSize) {
        m_contextHistory.erase(m_contextHistory.begin());
    }
}

bool NLPEngine::ValidateResult(const NLPResult& result) {
    // Check minimum confidence threshold
    if (result.intent_confidence < m_confidenceThreshold) {
        return false;
    }
    
    // Validate intent-entity consistency
    if (!ValidateIntentEntityConsistency(result.intent, result.entities)) {
        return false;
    }
    
    // Check for required entities based on intent
    if (!HasRequiredEntities(result.intent, result.entities)) {
        return false;
    }
    
    return true;
}

float NLPEngine::CalculatePatternConfidence(const std::string& text, const std::string& pattern) {
    // Base confidence for pattern match
    float baseConfidence = 0.7f;
    
    // Boost confidence based on pattern specificity
    float specificityBoost = std::min(0.2f, pattern.length() / 50.0f);
    
    // Boost confidence based on text length match
    float lengthRatio = std::min(1.0f, static_cast<float>(pattern.length()) / text.length());
    float lengthBoost = lengthRatio * 0.1f;
    
    return std::min(1.0f, baseConfidence + specificityBoost + lengthBoost);
}

float NLPEngine::CalculateContextualBoost(const std::string& intent) {
    if (m_contextHistory.empty()) {
        return 0.0f;
    }
    
    // Check for similar intents in recent context
    int similarIntents = 0;
    for (const auto& entry : m_contextHistory) {
        if (entry.intent.find(intent.substr(0, intent.find('_'))) != std::string::npos) {
            similarIntents++;
        }
    }
    
    // Boost confidence based on context consistency
    float contextBoost = (static_cast<float>(similarIntents) / m_contextHistory.size()) * 0.15f;
    
    return contextBoost;
}

std::string NLPEngine::DetermineNumberType(const std::string& number, const std::string& intent) {
    if (intent.find("altitude") != std::string::npos || intent.find("flight_level") != std::string::npos) {
        return "altitude";
    } else if (intent.find("heading") != std::string::npos || intent.find("bearing") != std::string::npos) {
        return "heading";
    } else if (intent.find("speed") != std::string::npos || intent.find("velocity") != std::string::npos) {
        return "speed";
    } else if (intent.find("frequency") != std::string::npos) {
        return "frequency";
    } else {
        return "number";
    }
}

bool NLPEngine::ValidateIntentEntityConsistency(const std::string& intent, const std::vector<Entity>& entities) {
    // Define required entity types for each intent category
    static const std::unordered_map<std::string, std::vector<std::string>> requiredEntities = {
        {"flight_control_altitude", {"altitude", "number"}},
        {"flight_control_heading", {"heading", "number", "direction"}},
        {"flight_control_speed", {"speed", "number"}},
        {"communication_radio", {"frequency", "number", "identifier"}},
        {"navigation_waypoint", {"identifier"}},
        {"quantum_qns", {}},
        {"quantum_qpu", {}},
        {"emergency_procedure", {}}
    };
    
    auto it = requiredEntities.find(intent);
    if (it == requiredEntities.end()) {
        return true; // Unknown intent, assume valid
    }
    
    if (it->second.empty()) {
        return true; // No specific entities required
    }
    
    // Check if at least one required entity type is present
    for (const std::string& requiredType : it->second) {
        for (const Entity& entity : entities) {
            if (entity.type == requiredType) {
                return true;
            }
        }
    }
    
    return false;
}

bool NLPEngine::HasRequiredEntities(const std::string& intent, const std::vector<Entity>& entities) {
    // For now, implement basic validation
    // This could be extended with more sophisticated rules
    
    if (intent.find("flight_control") != std::string::npos) {
        // Flight control commands typically need at least one numeric value
        for (const Entity& entity : entities) {
            if (entity.type == "number" || entity.type == "altitude" || 
                entity.type == "heading" || entity.type == "speed") {
                return true;
            }
        }
        return false;
    }
    
    return true; // Default to valid for other intents
}

bool NLPEngine::LoadLanguageModels() {
    // Placeholder for actual model loading
    // In a real implementation, this would load trained ML models
    // For now, we'll use rule-based patterns
    return true;
}

bool NLPEngine::InitializeIntentClassifier() {
    // Initialize intent classification system
    // In a real implementation, this might load a trained classifier
    return true;
}

bool NLPEngine::InitializeEntityExtractor() {
    // Initialize entity extraction system
    // In a real implementation, this might load NER models
    return true;
}

bool NLPEngine::InitializeContextManager() {
    // Initialize context management
    m_contextHistory.clear();
    m_contextHistory.reserve(m_contextWindowSize);
    return true;
}

void NLPEngine::InitializeModels() {
    // Initialize any static data or models
    // This could include loading pre-trained models from files
}

NLPResult NLPEngine::CreateErrorResult(const std::string& error) {
    NLPResult result;
    result.success = false;
    result.intent = "error";
    result.intent_confidence = 0.0f;
    result.error_message = error;
    result.timestamp = std::chrono::system_clock::now();
    return result;
}

void NLPEngine::LogProcessingResult(const NLPResult& result) {
    // Log processing results for debugging and analysis
    // This could write to files, console, or logging system
    
    #ifdef AQUA_V_DEBUG_LOGGING
    std::cout << "[NLP] Intent: " << result.intent 
              << " Confidence: " << result.intent_confidence
              << " Entities: " << result.entities.size() << std::endl;
    #endif
}

void NLPEngine::Cleanup() {
    m_contextHistory.clear();
    m_initialized = false;
}

} // namespace NLP
} // namespace VoiceCommands
} // namespace AQUA_V
