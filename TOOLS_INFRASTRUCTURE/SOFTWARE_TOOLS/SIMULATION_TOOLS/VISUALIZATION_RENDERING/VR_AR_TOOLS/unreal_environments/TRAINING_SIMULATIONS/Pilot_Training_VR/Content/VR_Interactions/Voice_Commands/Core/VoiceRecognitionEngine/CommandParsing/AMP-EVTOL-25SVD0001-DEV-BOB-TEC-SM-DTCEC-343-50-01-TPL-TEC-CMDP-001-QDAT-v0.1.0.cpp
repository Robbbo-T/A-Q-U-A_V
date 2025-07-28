/**
 * ============================================================================
 * AQUA V. - Command Parser Engine Implementation
 * ============================================================================
 * 
 * Document ID: AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-343-50-01-TPL-TEC-CMDP-001-QDAT-v0.1.0
 * 
 * Nomenclature Breakdown (AQUA V. Official System v3.1):
 * - LÍNEA:     AMP (AMPEL360 Products)
 * - PRODUCTO:  EVTOL (Electric Vertical Take-Off and Landing Aircraft)
 * - MSN:       25SVD0001 (2025 Silicon Valley Development Unit 0001)
 * - FASE:      DEV (Development Phase)
 * - ALI/BOB:   BOB (Build-Operate-Build Digital Systems)
 * - ARTIFACT:  TEC (Technical Artifacts)
 * - TYPE:      SM (Software Module)
 * - UTCS:      DTCEC-343-50-01 (Digital Twin, Cloud & Edge Computing - Command Processing)
 * - CÓDIGO:    000-00-01 (Primary component within UTCS)
 * - TEMPLATE:  TPL-TEC-CMDP-001 (Technical Template - Command Parser - Instance 001)
 * - QD:        QDAT (Q-Data Governance Division)
 * - VERSIÓN:   v0.1.0 (Initial development version)
 * 
 * Description: Advanced Command Parser Engine for aerospace voice commands
 *              Handles command syntax validation, parameter extraction, and execution routing
 *              specifically designed for eVTOL pilot training simulations
 * 
 * Digital Thread Integration:
 * - Parent System: AMPEL360 Training VR System
 * - Component: Voice Recognition Engine Core
 * - Dependencies: NLP Engine (DTCEC-320), Audio Stream Processor (DTCEC-341)
 * - Interfaces: Unreal Engine 5.0+, AQUA V. Quantum Systems, ATA Chapter Systems
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

#include "AMP-EVTOL-25SVD0001-DEV-BOB-TEC-SM-DTCEC-343-50-01-TPL-TEC-CMDP-001-QDAT-v0.1.0.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <iomanip>
#include <random>

namespace AQUA_V {
namespace VoiceCommands {
namespace Parser {

/**
 * ============================================================================
 * STATIC AEROSPACE COMMAND DEFINITIONS
 * ============================================================================
 */

// Flight Control Command Patterns (ATA 27)
static const std::vector<CommandTemplate> FlightControlTemplates = {
    {
        "climb to (\\d+)",
        CommandCategory::FLIGHT_CONTROL,
        CommandPriority::CRITICAL,
        "climb_to_altitude",
        {{"altitude", ParameterType::INTEGER, 0, true, "feet", "Target altitude in feet"}},
        false,
        "ATA-27-10",
        "Climb to specified altitude"
    },
    {
        "descend to (\\d+)",
        CommandCategory::FLIGHT_CONTROL,
        CommandPriority::CRITICAL,
        "descend_to_altitude",
        {{"altitude", ParameterType::INTEGER, 0, true, "feet", "Target altitude in feet"}},
        false,
        "ATA-27-10",
        "Descend to specified altitude"
    },
    {
        "turn (left|right) (\\d+) degrees?",
        CommandCategory::FLIGHT_CONTROL,
        CommandPriority::CRITICAL,
        "turn_heading",
        {
            {"direction", ParameterType::STRING, std::string(""), true, "", "Turn direction"},
            {"degrees", ParameterType::INTEGER, 0, true, "degrees", "Turn amount in degrees"}
        },
        false,
        "ATA-27-20",
        "Turn aircraft by specified degrees"
    },
    {
        "heading (\\d+)",
        CommandCategory::FLIGHT_CONTROL,
        CommandPriority::CRITICAL,
        "set_heading",
        {{"heading", ParameterType::INTEGER, 0, true, "degrees", "Target heading in degrees"}},
        false,
        "ATA-27-20",
        "Set aircraft heading"
    },
    {
        "airspeed (\\d+)",
        CommandCategory::FLIGHT_CONTROL,
        CommandPriority::NORMAL,
        "set_airspeed",
        {{"speed", ParameterType::INTEGER, 0, true, "knots", "Target airspeed in knots"}},
        false,
        "ATA-27-30",
        "Set target airspeed"
    }
};

// Communication Command Patterns (ATA 23)
static const std::vector<CommandTemplate> CommunicationTemplates = {
    {
        "contact ([a-zA-Z0-9\\s]+)",
        CommandCategory::COMMUNICATIONS,
        CommandPriority::NORMAL,
        "contact_station",
        {{"station", ParameterType::STRING, std::string(""), true, "", "Radio station to contact"}},
        false,
        "ATA-23-10",
        "Contact specified radio station"
    },
    {
        "frequency (\\d+\\.\\d+)",
        CommandCategory::COMMUNICATIONS,
        CommandPriority::NORMAL,
        "set_frequency",
        {{"frequency", ParameterType::FLOAT, 0.0f, true, "MHz", "Radio frequency in MHz"}},
        false,
        "ATA-23-20",
        "Set radio frequency"
    },
    {
        "squawk (\\d{4})",
        CommandCategory::COMMUNICATIONS,
        CommandPriority::NORMAL,
        "set_transponder",
        {{"code", ParameterType::STRING, std::string(""), true, "", "Transponder code"}},
        false,
        "ATA-23-30",
        "Set transponder squawk code"
    }
};

// Navigation Command Patterns (ATA 34)
static const std::vector<CommandTemplate> NavigationTemplates = {
    {
        "navigate to ([A-Z0-9]+)",
        CommandCategory::NAVIGATION,
        CommandPriority::NORMAL,
        "navigate_to_waypoint",
        {{"waypoint", ParameterType::STRING, std::string(""), true, "", "Destination waypoint"}},
        false,
        "ATA-34-10",
        "Navigate to specified waypoint"
    },
    {
        "direct ([A-Z0-9]+)",
        CommandCategory::NAVIGATION,
        CommandPriority::NORMAL,
        "direct_to_waypoint",
        {{"waypoint", ParameterType::STRING, std::string(""), true, "", "Direct-to waypoint"}},
        false,
        "ATA-34-10",
        "Proceed direct to waypoint"
    }
};

// Quantum Systems Command Patterns (QCSAA 934-936)
static const std::vector<CommandTemplate> QuantumSystemTemplates = {
    {
        "activate qns",
        CommandCategory::QUANTUM_SYSTEMS,
        CommandPriority::CRITICAL,
        "activate_quantum_navigation",
        {},
        true,
        "QCSAA-934",
        "Activate Quantum Navigation System"
    },
    {
        "initialize qpu",
        CommandCategory::QUANTUM_SYSTEMS,
        CommandPriority::CRITICAL,
        "initialize_quantum_processor",
        {},
        true,
        "QCSAA-935",
        "Initialize Quantum Processing Unit"
    },
    {
        "qds status",
        CommandCategory::QUANTUM_SYSTEMS,
        CommandPriority::INFORMATIONAL,
        "query_quantum_data_storage",
        {},
        false,
        "QCSAA-936",
        "Query Quantum Data Storage status"
    }
};

// Emergency Command Patterns (ATA 25)
static const std::vector<CommandTemplate> EmergencyTemplates = {
    {
        "emergency descent",
        CommandCategory::EMERGENCY,
        CommandPriority::EMERGENCY,
        "emergency_descent",
        {},
        false,
        "ATA-25-10",
        "Initiate emergency descent procedure"
    },
    {
        "mayday",
        CommandCategory::EMERGENCY,
        CommandPriority::EMERGENCY,
        "declare_emergency",
        {},
        false,
        "ATA-25-20",
        "Declare emergency (Mayday)"
    },
    {
        "pan pan",
        CommandCategory::EMERGENCY,
        CommandPriority::EMERGENCY,
        "declare_urgency",
        {},
        false,
        "ATA-25-20",
        "Declare urgency (Pan Pan)"
    }
};

/**
 * ============================================================================
 * COMMAND PARSER IMPLEMENTATION
 * ============================================================================
 */

CommandParser::CommandParser() : m_initialized(false) {
    // Initialize with empty configuration
    m_config = CommandParserConfig();
}

CommandParser::~CommandParser() {
    // Cleanup resources
    m_templates.clear();
    m_intent_mapping.clear();
}

bool CommandParser::Initialize(const CommandParserConfig& config) {
    m_config = config;
    
    // Load default aerospace command templates
    if (!LoadDefaultTemplates()) {
        return false;
    }
    
    // Initialize all command categories
    if (!InitializeFlightControlCommands() ||
        !InitializeCommunicationCommands() ||
        !InitializeNavigationCommands() ||
        !InitializeQuantumSystemCommands() ||
        !InitializeEmergencyCommands()) {
        return false;
    }
    
    m_initialized = true;
    return true;
}

ParsedCommand CommandParser::ParseCommand(const std::string& command_text,
                                        const std::string& intent,
                                        const std::vector<std::string>& entities) {
    ParsedCommand result;
    result.raw_command = command_text;
    result.normalized_command = NormalizeCommandText(command_text);
    result.context = m_context;
    
    // Map intent to command category
    result.category = MapIntentToCategory(intent);
    
    // Find matching command template
    auto intent_it = m_intent_mapping.find(intent);
    if (intent_it != m_intent_mapping.end()) {
        const CommandTemplate& template_def = intent_it->second;
        
        result.action = template_def.action;
        result.priority = template_def.priority;
        result.ata_chapter = template_def.ata_chapter;
        result.requires_confirmation = template_def.requires_confirmation;
        
        // Extract parameters from entities
        result.parameters = ExtractParameters(entities, template_def.parameter_templates);
        
        // Calculate confidence based on parameter match
        float parameter_confidence = static_cast<float>(result.parameters.size()) / 
                                   std::max(1.0f, static_cast<float>(template_def.parameter_templates.size()));
        result.confidence = parameter_confidence;
        
        // Validate the parsed command
        result.validation = ValidateCommand(result);
        
        // Calculate safety criticality
        result.safety_criticality = CalculateSafetyCriticality(result.category, result.action, result.parameters);
        
    } else {
        // Unknown intent
        result.validation.status = ValidationStatus::INVALID_SYNTAX;
        result.validation.error_message = "Unknown command intent: " + intent;
        result.confidence = 0.0f;
    }
    
    // Log parsing result for debugging
    if (m_config.strict_validation) {
        LogParsingResult(result);
    }
    
    return result;
}

ValidationResult CommandParser::ValidateCommand(const ParsedCommand& command) {
    ValidationResult result;
    
    // Check basic syntax validation
    if (command.action.empty()) {
        result.status = ValidationStatus::INVALID_SYNTAX;
        result.error_message = "No action specified in command";
        return result;
    }
    
    // Validate parameters
    ValidationResult param_validation = ValidateParameters(command.parameters);
    if (!param_validation.IsValid()) {
        return param_validation;
    }
    
    // Check safety constraints if enabled
    if (m_config.safety_checks) {
        ValidationResult safety_validation = CheckSafetyConstraints(command);
        if (!safety_validation.IsValid()) {
            return safety_validation;
        }
        result.safety_score = safety_validation.safety_score;
    }
    
    // Check confidence threshold
    if (command.confidence < m_config.confidence_threshold) {
        result.status = ValidationStatus::INVALID_SYNTAX;
        result.error_message = "Command confidence below threshold: " + 
                              std::to_string(command.confidence) + " < " + 
                              std::to_string(m_config.confidence_threshold);
        return result;
    }
    
    // All validations passed
    result.status = ValidationStatus::VALID;
    return result;
}

bool CommandParser::LoadGrammar(const std::string& grammar_file) {
    // Placeholder for loading grammar from external file
    // In a real implementation, this would parse a grammar definition file
    // For now, we use the hardcoded templates
    return true;
}

bool CommandParser::RegisterCommandTemplate(const CommandTemplate& template_def) {
    if (template_def.pattern.empty() || template_def.action.empty()) {
        return false;
    }
    
    // Add to category-based storage
    m_templates[template_def.category].push_back(template_def);
    
    // Create intent mapping based on action
    m_intent_mapping[template_def.action] = template_def;
    
    return true;
}

std::vector<CommandCategory> CommandParser::GetSupportedCategories() const {
    std::vector<CommandCategory> categories;
    for (const auto& pair : m_templates) {
        categories.push_back(pair.first);
    }
    return categories;
}

std::vector<CommandTemplate> CommandParser::GetCommandTemplates(CommandCategory category) const {
    auto it = m_templates.find(category);
    if (it != m_templates.end()) {
        return it->second;
    }
    return {};
}

void CommandParser::SetExecutionContext(const ExecutionContext& context) {
    m_context = context;
}

/**
 * ============================================================================
 * PRIVATE METHOD IMPLEMENTATIONS
 * ============================================================================
 */

std::string CommandParser::NormalizeCommandText(const std::string& command_text) {
    std::string normalized = command_text;
    
    // Convert to lowercase
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    
    // Remove extra whitespace
    std::regex ws_regex("\\s+");
    normalized = std::regex_replace(normalized, ws_regex, " ");
    
    // Trim leading and trailing whitespace
    normalized.erase(0, normalized.find_first_not_of(" \\t\\n\\r"));
    normalized.erase(normalized.find_last_not_of(" \\t\\n\\r") + 1);
    
    return normalized;
}

CommandCategory CommandParser::MapIntentToCategory(const std::string& intent) {
    // Map intents to ATA chapters and categories
    if (intent.find("flight_control") != std::string::npos) {
        return CommandCategory::FLIGHT_CONTROL;
    } else if (intent.find("communication") != std::string::npos) {
        return CommandCategory::COMMUNICATIONS;
    } else if (intent.find("navigation") != std::string::npos) {
        return CommandCategory::NAVIGATION;
    } else if (intent.find("quantum") != std::string::npos) {
        return CommandCategory::QUANTUM_SYSTEMS;
    } else if (intent.find("emergency") != std::string::npos) {
        return CommandCategory::EMERGENCY;
    } else if (intent.find("training") != std::string::npos) {
        return CommandCategory::TRAINING;
    } else {
        return CommandCategory::UNKNOWN;
    }
}

std::vector<CommandParameter> CommandParser::ExtractParameters(
    const std::vector<std::string>& entities,
    const std::vector<CommandParameter>& template_params) {
    
    std::vector<CommandParameter> extracted_params;
    
    // Simple parameter extraction based on position and type
    for (size_t i = 0; i < template_params.size() && i < entities.size(); ++i) {
        CommandParameter param = template_params[i];
        
        // Convert entity value based on parameter type
        const std::string& entity_value = entities[i];
        
        switch (param.type) {
            case ParameterType::INTEGER:
                try {
                    param.value = std::stoi(entity_value);
                } catch (const std::exception&) {
                    continue; // Skip invalid integer
                }
                break;
                
            case ParameterType::FLOAT:
                try {
                    param.value = std::stof(entity_value);
                } catch (const std::exception&) {
                    continue; // Skip invalid float
                }
                break;
                
            case ParameterType::STRING:
            case ParameterType::IDENTIFIER:
                param.value = entity_value;
                break;
                
            case ParameterType::BOOLEAN:
                param.value = (entity_value == "true" || entity_value == "yes" || entity_value == "on");
                break;
                
            default:
                param.value = entity_value;
                break;
        }
        
        extracted_params.push_back(param);
    }
    
    return extracted_params;
}

ValidationResult CommandParser::ValidateParameters(const std::vector<CommandParameter>& parameters) {
    ValidationResult result;
    
    for (const auto& param : parameters) {
        // Check parameter constraints based on type
        switch (param.type) {
            case ParameterType::INTEGER: {
                if (std::holds_alternative<int>(param.value)) {
                    int value = std::get<int>(param.value);
                    
                    // Check altitude constraints
                    if (param.name == "altitude") {
                        if (value < 0 || value > 50000) {
                            result.status = ValidationStatus::INVALID_PARAMETERS;
                            result.error_message = "Altitude out of range: " + std::to_string(value);
                            result.invalid_parameters.push_back(param.name);
                            return result;
                        }
                    }
                    
                    // Check heading constraints
                    if (param.name == "heading" || param.name == "degrees") {
                        if (value < 0 || value >= 360) {
                            result.status = ValidationStatus::INVALID_PARAMETERS;
                            result.error_message = "Heading out of range: " + std::to_string(value);
                            result.invalid_parameters.push_back(param.name);
                            return result;
                        }
                    }
                    
                    // Check speed constraints
                    if (param.name == "speed") {
                        if (value < 0 || value > 500) {
                            result.status = ValidationStatus::INVALID_PARAMETERS;
                            result.error_message = "Speed out of range: " + std::to_string(value);
                            result.invalid_parameters.push_back(param.name);
                            return result;
                        }
                    }
                }
                break;
            }
            
            case ParameterType::FLOAT: {
                if (std::holds_alternative<float>(param.value)) {
                    float value = std::get<float>(param.value);
                    
                    // Check frequency constraints
                    if (param.name == "frequency") {
                        if (value < 118.0f || value > 137.0f) {
                            result.status = ValidationStatus::INVALID_PARAMETERS;
                            result.error_message = "Frequency out of aviation range: " + std::to_string(value);
                            result.invalid_parameters.push_back(param.name);
                            return result;
                        }
                    }
                }
                break;
            }
            
            case ParameterType::STRING:
            case ParameterType::IDENTIFIER: {
                if (std::holds_alternative<std::string>(param.value)) {
                    const std::string& value = std::get<std::string>(param.value);
                    
                    // Check for empty required parameters
                    if (param.required && value.empty()) {
                        result.status = ValidationStatus::MISSING_PARAMETERS;
                        result.error_message = "Required parameter missing: " + param.name;
                        result.missing_parameters.push_back(param.name);
                        return result;
                    }
                    
                    // Validate waypoint format (basic check)
                    if (param.name == "waypoint") {
                        if (value.length() < 2 || value.length() > 5) {
                            result.status = ValidationStatus::INVALID_PARAMETERS;
                            result.error_message = "Invalid waypoint format: " + value;
                            result.invalid_parameters.push_back(param.name);
                            return result;
                        }
                    }
                }
                break;
            }
            
            default:
                break;
        }
    }
    
    result.status = ValidationStatus::VALID;
    result.safety_score = 1.0f;
    return result;
}

ValidationResult CommandParser::CheckSafetyConstraints(const ParsedCommand& command) {
    ValidationResult result;
    result.status = ValidationStatus::VALID;
    result.safety_score = 1.0f;
    
    // Check for safety-critical operations
    if (command.category == CommandCategory::EMERGENCY) {
        result.safety_score = 0.9f; // High safety concern but valid
        result.warnings.push_back("Emergency command detected");
    }
    
    // Check altitude change rates
    if (command.action == "climb_to_altitude" || command.action == "descend_to_altitude") {
        for (const auto& param : command.parameters) {
            if (param.name == "altitude" && std::holds_alternative<int>(param.value)) {
                int target_altitude = std::get<int>(param.value);
                
                // Simulate current altitude (in real implementation, this would come from aircraft state)
                int current_altitude = 10000; // Example current altitude
                int altitude_change = std::abs(target_altitude - current_altitude);
                
                // Check for extreme altitude changes
                if (altitude_change > 10000) {
                    result.safety_score = 0.5f;
                    result.warnings.push_back("Large altitude change requested: " + std::to_string(altitude_change) + " feet");
                }
            }
        }
    }
    
    // Check for conflicting commands in rapid succession
    // This would require integration with command history
    
    return result;
}

/**
 * ============================================================================
 * INITIALIZATION METHOD IMPLEMENTATIONS
 * ============================================================================
 */

bool CommandParser::LoadDefaultTemplates() {
    // Clear existing templates
    m_templates.clear();
    m_intent_mapping.clear();
    
    return true;
}

bool CommandParser::InitializeFlightControlCommands() {
    for (const auto& template_def : FlightControlTemplates) {
        if (!RegisterCommandTemplate(template_def)) {
            return false;
        }
    }
    return true;
}

bool CommandParser::InitializeCommunicationCommands() {
    for (const auto& template_def : CommunicationTemplates) {
        if (!RegisterCommandTemplate(template_def)) {
            return false;
        }
    }
    return true;
}

bool CommandParser::InitializeNavigationCommands() {
    for (const auto& template_def : NavigationTemplates) {
        if (!RegisterCommandTemplate(template_def)) {
            return false;
        }
    }
    return true;
}

bool CommandParser::InitializeQuantumSystemCommands() {
    for (const auto& template_def : QuantumSystemTemplates) {
        if (!RegisterCommandTemplate(template_def)) {
            return false;
        }
    }
    return true;
}

bool CommandParser::InitializeEmergencyCommands() {
    for (const auto& template_def : EmergencyTemplates) {
        if (!RegisterCommandTemplate(template_def)) {
            return false;
        }
    }
    return true;
}

/**
 * ============================================================================
 * UTILITY METHOD IMPLEMENTATIONS
 * ============================================================================
 */

ParameterType CommandParser::StringToParameterType(const std::string& type_str) {
    if (type_str == "integer") return ParameterType::INTEGER;
    if (type_str == "float") return ParameterType::FLOAT;
    if (type_str == "string") return ParameterType::STRING;
    if (type_str == "boolean") return ParameterType::BOOLEAN;
    if (type_str == "identifier") return ParameterType::IDENTIFIER;
    return ParameterType::STRING; // Default
}

std::string CommandParser::ParameterTypeToString(ParameterType type) {
    switch (type) {
        case ParameterType::INTEGER: return "integer";
        case ParameterType::FLOAT: return "float";
        case ParameterType::STRING: return "string";
        case ParameterType::BOOLEAN: return "boolean";
        case ParameterType::IDENTIFIER: return "identifier";
        default: return "unknown";
    }
}

std::string CommandParser::GenerateCommandId() {
    // Generate unique command ID using timestamp and random component
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    
    std::stringstream ss;
    ss << "CMD-" << timestamp << "-" << dis(gen);
    return ss.str();
}

void CommandParser::LogParsingResult(const ParsedCommand& command) {
    #ifdef AQUA_V_DEBUG_LOGGING
    std::cout << "[PARSER] Command: " << command.raw_command
              << " Action: " << command.action
              << " Category: " << static_cast<int>(command.category)
              << " Confidence: " << command.confidence
              << " Valid: " << (command.validation.IsValid() ? "Yes" : "No")
              << std::endl;
    #endif
}

/**
 * ============================================================================
 * UTILITY FUNCTION IMPLEMENTATIONS
 * ============================================================================
 */

CommandParserConfig LoadParserConfigFromFile(const std::string& config_path) {
    // Placeholder for JSON file loading
    // In real implementation, would parse JSON configuration file
    return CreateDefaultAerospaceParserConfig();
}

bool SaveParserConfigToFile(const CommandParserConfig& config, const std::string& config_path) {
    // Placeholder for JSON file saving
    // In real implementation, would serialize configuration to JSON
    return true;
}

CommandParserConfig CreateDefaultAerospaceParserConfig() {
    CommandParserConfig config;
    config.strict_validation = true;
    config.safety_checks = true;
    config.context_awareness = true;
    config.confidence_threshold = AQUA_V_DEFAULT_CONFIDENCE_THRESHOLD;
    config.max_parameters = AQUA_V_MAX_COMMAND_PARAMETERS;
    config.command_timeout_ms = AQUA_V_DEFAULT_COMMAND_TIMEOUT_MS;
    config.emergency_override = true;
    config.require_confirmation = false;
    config.training_mode = false;
    config.allow_simulation = true;
    return config;
}

std::string CommandCategoryToATAChapter(CommandCategory category) {
    switch (category) {
        case CommandCategory::FLIGHT_CONTROL: return "ATA-27";
        case CommandCategory::COMMUNICATIONS: return "ATA-23";
        case CommandCategory::NAVIGATION: return "ATA-34";
        case CommandCategory::SYSTEMS_MANAGEMENT: return "ATA-31";
        case CommandCategory::QUANTUM_SYSTEMS: return "QCSAA-934-936";
        case CommandCategory::ENVIRONMENTAL: return "ATA-21";
        case CommandCategory::EMERGENCY: return "ATA-25";
        case CommandCategory::TRAINING: return "ACV-778";
        case CommandCategory::MAINTENANCE: return "ATA-05";
        default: return "UNKNOWN";
    }
}

CommandCategory ATAChapterToCommandCategory(const std::string& ata_chapter) {
    if (ata_chapter == "ATA-27") return CommandCategory::FLIGHT_CONTROL;
    if (ata_chapter == "ATA-23") return CommandCategory::COMMUNICATIONS;
    if (ata_chapter == "ATA-34") return CommandCategory::NAVIGATION;
    if (ata_chapter == "ATA-31") return CommandCategory::SYSTEMS_MANAGEMENT;
    if (ata_chapter == "QCSAA-934-936") return CommandCategory::QUANTUM_SYSTEMS;
    if (ata_chapter == "ATA-21") return CommandCategory::ENVIRONMENTAL;
    if (ata_chapter == "ATA-25") return CommandCategory::EMERGENCY;
    if (ata_chapter == "ACV-778") return CommandCategory::TRAINING;
    if (ata_chapter == "ATA-05") return CommandCategory::MAINTENANCE;
    return CommandCategory::UNKNOWN;
}

bool RequiresConfirmation(const ParsedCommand& command) {
    // Emergency commands don't require confirmation for speed
    if (command.priority == CommandPriority::EMERGENCY) {
        return false;
    }
    
    // Critical commands with high safety impact require confirmation
    if (command.priority == CommandPriority::CRITICAL && command.safety_criticality > AQUA_V_SAFETY_CRITICAL_THRESHOLD) {
        return true;
    }
    
    // Quantum system commands require confirmation
    if (command.category == CommandCategory::QUANTUM_SYSTEMS) {
        return true;
    }
    
    return command.requires_confirmation;
}

float CalculateSafetyCriticality(CommandCategory category,
                               const std::string& action,
                               const std::vector<CommandParameter>& parameters) {
    float criticality = 0.0f;
    
    // Base criticality by category
    switch (category) {
        case CommandCategory::EMERGENCY:
            criticality = 1.0f;
            break;
        case CommandCategory::FLIGHT_CONTROL:
            criticality = 0.8f;
            break;
        case CommandCategory::QUANTUM_SYSTEMS:
            criticality = 0.7f;
            break;
        case CommandCategory::NAVIGATION:
            criticality = 0.6f;
            break;
        case CommandCategory::COMMUNICATIONS:
            criticality = 0.4f;
            break;
        default:
            criticality = 0.3f;
            break;
    }
    
    // Adjust based on specific actions
    if (action.find("emergency") != std::string::npos) {
        criticality = 1.0f;
    } else if (action.find("descent") != std::string::npos || action.find("climb") != std::string::npos) {
        criticality = std::max(criticality, 0.9f);
    }
    
    // Adjust based on parameter values (example: large altitude changes)
    for (const auto& param : parameters) {
        if (param.name == "altitude" && std::holds_alternative<int>(param.value)) {
            int altitude = std::get<int>(param.value);
            if (altitude > 30000 || altitude < 1000) {
                criticality = std::min(1.0f, criticality + 0.1f);
            }
        }
    }
    
    return std::min(1.0f, criticality);
}

} // namespace Parser
} // namespace VoiceCommands
} // namespace AQUA_V
