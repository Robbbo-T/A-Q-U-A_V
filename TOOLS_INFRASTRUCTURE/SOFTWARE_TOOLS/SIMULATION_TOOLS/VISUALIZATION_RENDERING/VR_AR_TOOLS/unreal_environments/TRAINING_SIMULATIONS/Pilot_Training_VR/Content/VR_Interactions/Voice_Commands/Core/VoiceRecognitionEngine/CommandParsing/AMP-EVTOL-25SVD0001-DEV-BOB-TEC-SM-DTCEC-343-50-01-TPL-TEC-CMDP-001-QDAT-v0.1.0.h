/**
 * ============================================================================
 * AQUA V. - Command Parser Engine Header
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

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <memory>
#include <variant>

namespace AQUA_V {
namespace VoiceCommands {
namespace Parser {

/**
 * Forward Declarations
 */
struct CommandParserConfig;
struct ParsedCommand;
struct CommandParameter;
struct ValidationResult;
struct ExecutionContext;

/**
 * ============================================================================
 * CORE ENUMERATIONS
 * ============================================================================
 */

/**
 * Command Categories based on ATA Chapters and AQUA V. Systems
 */
enum class CommandCategory {
    FLIGHT_CONTROL = 27,        // ATA Chapter 27 - Flight Controls
    COMMUNICATIONS = 23,        // ATA Chapter 23 - Communications
    NAVIGATION = 34,            // ATA Chapter 34 - Navigation
    SYSTEMS_MANAGEMENT = 31,    // ATA Chapter 31 - Instruments/Systems
    QUANTUM_SYSTEMS = 934,      // QCSAA 934-936 - Quantum Systems
    ENVIRONMENTAL = 21,         // ATA Chapter 21 - Air Conditioning
    EMERGENCY = 25,             // ATA Chapter 25 - Equipment/Furnishings (Emergency)
    TRAINING = 778,             // ACV 778 - Training Operations
    MAINTENANCE = 5,            // ATA Chapter 5 - Time Limits/Maintenance
    UNKNOWN = 0                 // Unknown/Invalid category
};

/**
 * Command Priority Levels for Safety-Critical Operations
 */
enum class CommandPriority {
    EMERGENCY = 0,              // Immediate execution required (mayday, emergency descent)
    CRITICAL = 1,               // High priority safety operations (altitude changes, heading)
    NORMAL = 2,                 // Standard flight operations
    TRAINING = 3,               // Training mode commands
    INFORMATIONAL = 4           // System status queries
};

/**
 * Parameter Types for Command Arguments
 */
enum class ParameterType {
    INTEGER,                    // Whole numbers (altitude, heading degrees)
    FLOAT,                      // Decimal numbers (frequency, speed)
    STRING,                     // Text values (waypoint names, identifiers)
    BOOLEAN,                    // True/false values
    ENUM,                       // Predefined enumeration values
    COORDINATE,                 // Latitude/longitude pairs
    TIME,                       // Time values
    IDENTIFIER                  // System identifiers (runway, radio call signs)
};

/**
 * Validation Status for Parsed Commands
 */
enum class ValidationStatus {
    VALID,                      // Command is valid and ready for execution
    INVALID_SYNTAX,             // Syntax errors in command structure
    MISSING_PARAMETERS,         // Required parameters not provided
    INVALID_PARAMETERS,         // Parameters out of range or invalid format
    SAFETY_VIOLATION,           // Command violates safety constraints
    AUTHORIZATION_REQUIRED,     // Command requires higher authorization
    CONTEXT_ERROR              // Command not valid in current context
};

/**
 * ============================================================================
 * CORE DATA STRUCTURES
 * ============================================================================
 */

/**
 * Command Parser Configuration
 */
struct CommandParserConfig {
    bool strict_validation = true;                      // Enable strict parameter validation
    bool safety_checks = true;                          // Enable safety constraint checking
    bool context_awareness = true;                      // Enable context-sensitive parsing
    float confidence_threshold = 0.8f;                 // Minimum confidence for execution
    uint32_t max_parameters = 10;                       // Maximum parameters per command
    uint32_t command_timeout_ms = 5000;                 // Command execution timeout
    
    // Safety configuration
    bool emergency_override = true;                     // Allow emergency commands to override normal validation
    bool require_confirmation = false;                  // Require confirmation for critical commands
    
    // Training configuration
    bool training_mode = false;                         // Enable training mode features
    bool allow_simulation = true;                       // Allow simulation commands
    
    CommandParserConfig() = default;
};

/**
 * Command Parameter Structure
 */
struct CommandParameter {
    std::string name;                                   // Parameter name
    ParameterType type;                                 // Parameter data type
    std::variant<int, float, std::string, bool> value; // Parameter value
    bool required = true;                               // Whether parameter is required
    std::string unit;                                   // Unit of measurement (if applicable)
    std::string description;                            // Parameter description
    
    // Validation constraints
    std::variant<int, float> min_value;                 // Minimum allowed value
    std::variant<int, float> max_value;                 // Maximum allowed value
    std::vector<std::string> allowed_values;            // Allowed enumeration values
    
    CommandParameter() : type(ParameterType::STRING) {}
};

/**
 * Validation Result Structure
 */
struct ValidationResult {
    ValidationStatus status = ValidationStatus::VALID;  // Validation status
    std::string error_message;                          // Detailed error message
    std::vector<std::string> warnings;                  // Non-fatal warnings
    std::vector<std::string> missing_parameters;        // List of missing required parameters
    std::vector<std::string> invalid_parameters;        // List of invalid parameters
    float safety_score = 1.0f;                         // Safety assessment score (0.0 to 1.0)
    
    bool IsValid() const { return status == ValidationStatus::VALID; }
};

/**
 * Execution Context Structure
 */
struct ExecutionContext {
    CommandCategory active_category = CommandCategory::UNKNOWN; // Current command category context
    std::string session_id;                             // Unique session identifier
    std::chrono::system_clock::time_point timestamp;    // Command timestamp
    std::string user_id;                                // User identifier (for authorization)
    std::string aircraft_state;                         // Current aircraft state
    std::unordered_map<std::string, std::string> environment; // Environmental context
    
    ExecutionContext() : timestamp(std::chrono::system_clock::now()) {}
};

/**
 * Parsed Command Structure
 */
struct ParsedCommand {
    std::string raw_command;                            // Original command text
    std::string normalized_command;                     // Normalized command text
    CommandCategory category = CommandCategory::UNKNOWN; // Command category
    CommandPriority priority = CommandPriority::NORMAL; // Command priority
    std::string action;                                 // Primary action/verb
    std::vector<CommandParameter> parameters;           // Command parameters
    ValidationResult validation;                        // Validation result
    ExecutionContext context;                           // Execution context
    float confidence = 0.0f;                           // Parsing confidence score
    bool requires_confirmation = false;                 // Whether command needs confirmation
    
    // ATA Chapter information
    std::string ata_chapter;                            // Relevant ATA chapter
    std::string subsystem;                              // Specific subsystem within chapter
    
    // Safety information
    float safety_criticality = 0.0f;                   // Safety criticality score
    std::vector<std::string> safety_warnings;           // Safety-related warnings
    
    ParsedCommand() = default;
};

/**
 * Command Template Structure for Grammar Definition
 */
struct CommandTemplate {
    std::string pattern;                                // Command pattern (regex or grammar)
    CommandCategory category;                           // Command category
    CommandPriority priority;                           // Default priority
    std::string action;                                 // Action name
    std::vector<CommandParameter> parameter_templates;  // Parameter templates
    bool requires_confirmation = false;                 // Confirmation requirement
    std::string ata_chapter;                            // Related ATA chapter
    std::string description;                            // Command description
    
    CommandTemplate() : category(CommandCategory::UNKNOWN), priority(CommandPriority::NORMAL) {}
};

/**
 * ============================================================================
 * MAIN COMMAND PARSER CLASS
 * ============================================================================
 */

/**
 * Command Parser Engine for AQUA V. Voice Commands
 * 
 * This class provides comprehensive command parsing capabilities specifically
 * designed for aerospace training environments, including:
 * - Syntax validation against aerospace command grammar
 * - Parameter extraction and type validation
 * - Safety constraint checking
 * - ATA chapter categorization
 * - Context-sensitive parsing
 * - Integration with quantum systems commands
 * 
 * Thread Safety: This class is thread-safe for read operations but requires
 * external synchronization for concurrent configuration changes.
 */
class CommandParser {
public:
    /**
     * Constructor
     */
    CommandParser();
    
    /**
     * Destructor
     */
    ~CommandParser();
    
    /**
     * Initialize the command parser with specified configuration
     * @param config Parser configuration
     * @return true if initialization successful
     */
    bool Initialize(const CommandParserConfig& config);
    
    /**
     * Parse a natural language command into structured format
     * @param command_text Raw command text from NLP engine
     * @param intent Classified intent from NLP
     * @param entities Extracted entities from NLP
     * @return Parsed command structure
     */
    ParsedCommand ParseCommand(const std::string& command_text, 
                              const std::string& intent,
                              const std::vector<std::string>& entities);
    
    /**
     * Validate a parsed command against safety and syntax rules
     * @param command Parsed command to validate
     * @return Validation result
     */
    ValidationResult ValidateCommand(const ParsedCommand& command);
    
    /**
     * Load command grammar from file
     * @param grammar_file Path to grammar definition file
     * @return true if loading successful
     */
    bool LoadGrammar(const std::string& grammar_file);
    
    /**
     * Register a custom command template
     * @param template_def Command template definition
     * @return true if registration successful
     */
    bool RegisterCommandTemplate(const CommandTemplate& template_def);
    
    /**
     * Get supported command categories
     * @return Vector of supported categories
     */
    std::vector<CommandCategory> GetSupportedCategories() const;
    
    /**
     * Get command templates for a specific category
     * @param category Command category
     * @return Vector of command templates
     */
    std::vector<CommandTemplate> GetCommandTemplates(CommandCategory category) const;
    
    /**
     * Set execution context for command parsing
     * @param context Execution context
     */
    void SetExecutionContext(const ExecutionContext& context);
    
    /**
     * Get current execution context
     * @return Current execution context
     */
    const ExecutionContext& GetExecutionContext() const { return m_context; }
    
    /**
     * Check if parser is initialized and ready
     * @return true if ready to parse commands
     */
    bool IsReady() const { return m_initialized; }

private:
    /**
     * ========================================================================
     * PRIVATE MEMBER VARIABLES
     * ========================================================================
     */
    
    bool m_initialized = false;                                             // Initialization status
    CommandParserConfig m_config;                                           // Parser configuration
    ExecutionContext m_context;                                             // Current execution context
    std::unordered_map<CommandCategory, std::vector<CommandTemplate>> m_templates; // Command templates by category
    std::unordered_map<std::string, CommandTemplate> m_intent_mapping;      // Intent to template mapping
    
    /**
     * ========================================================================
     * PRIVATE PARSING METHODS
     * ========================================================================
     */
    
    /**
     * Normalize command text for consistent parsing
     * @param command_text Raw command text
     * @return Normalized command text
     */
    std::string NormalizeCommandText(const std::string& command_text);
    
    /**
     * Map intent to command category
     * @param intent Intent from NLP engine
     * @return Corresponding command category
     */
    CommandCategory MapIntentToCategory(const std::string& intent);
    
    /**
     * Extract parameters from entities
     * @param entities Entities from NLP engine
     * @param template_params Parameter templates
     * @return Extracted parameters
     */
    std::vector<CommandParameter> ExtractParameters(const std::vector<std::string>& entities,
                                                   const std::vector<CommandParameter>& template_params);
    
    /**
     * Validate parameter values against constraints
     * @param parameters Parameters to validate
     * @return Validation result
     */
    ValidationResult ValidateParameters(const std::vector<CommandParameter>& parameters);
    
    /**
     * Check safety constraints for command
     * @param command Parsed command
     * @return Safety validation result
     */
    ValidationResult CheckSafetyConstraints(const ParsedCommand& command);
    
    /**
     * ========================================================================
     * INITIALIZATION METHODS
     * ========================================================================
     */
    
    /**
     * Load default aerospace command templates
     * @return true if loading successful
     */
    bool LoadDefaultTemplates();
    
    /**
     * Initialize flight control commands (ATA 27)
     * @return true if initialization successful
     */
    bool InitializeFlightControlCommands();
    
    /**
     * Initialize communication commands (ATA 23)
     * @return true if initialization successful
     */
    bool InitializeCommunicationCommands();
    
    /**
     * Initialize navigation commands (ATA 34)
     * @return true if initialization successful
     */
    bool InitializeNavigationCommands();
    
    /**
     * Initialize quantum system commands (QCSAA 934-936)
     * @return true if initialization successful
     */
    bool InitializeQuantumSystemCommands();
    
    /**
     * Initialize emergency commands (ATA 25)
     * @return true if initialization successful
     */
    bool InitializeEmergencyCommands();
    
    /**
     * ========================================================================
     * UTILITY METHODS
     * ========================================================================
     */
    
    /**
     * Convert string to parameter type
     * @param type_str String representation of type
     * @return Parameter type
     */
    ParameterType StringToParameterType(const std::string& type_str);
    
    /**
     * Convert parameter type to string
     * @param type Parameter type
     * @return String representation
     */
    std::string ParameterTypeToString(ParameterType type);
    
    /**
     * Generate unique command ID
     * @return Unique command identifier
     */
    std::string GenerateCommandId();
    
    /**
     * Log parsing result for debugging
     * @param command Parsed command
     */
    void LogParsingResult(const ParsedCommand& command);
};

/**
 * ============================================================================
 * UTILITY FUNCTIONS
 * ============================================================================
 */

/**
 * Load parser configuration from JSON file
 * @param config_path Path to configuration file
 * @return Loaded configuration
 */
CommandParserConfig LoadParserConfigFromFile(const std::string& config_path);

/**
 * Save parser configuration to JSON file
 * @param config Configuration to save
 * @param config_path Path to configuration file
 * @return true if saving successful
 */
bool SaveParserConfigToFile(const CommandParserConfig& config, const std::string& config_path);

/**
 * Create default parser configuration for aerospace applications
 * @return Default configuration
 */
CommandParserConfig CreateDefaultAerospaceParserConfig();

/**
 * Convert command category to ATA chapter string
 * @param category Command category
 * @return ATA chapter string
 */
std::string CommandCategoryToATAChapter(CommandCategory category);

/**
 * Convert ATA chapter to command category
 * @param ata_chapter ATA chapter string
 * @return Command category
 */
CommandCategory ATAChapterToCommandCategory(const std::string& ata_chapter);

/**
 * Check if command requires confirmation based on safety criticality
 * @param command Parsed command
 * @return true if confirmation required
 */
bool RequiresConfirmation(const ParsedCommand& command);

/**
 * Calculate safety criticality score for a command
 * @param category Command category
 * @param action Command action
 * @param parameters Command parameters
 * @return Safety criticality score (0.0 to 1.0)
 */
float CalculateSafetyCriticality(CommandCategory category, 
                               const std::string& action,
                               const std::vector<CommandParameter>& parameters);

} // namespace Parser
} // namespace VoiceCommands
} // namespace AQUA_V

/**
 * ============================================================================
 * COMPILE-TIME CONSTANTS
 * ============================================================================
 */

// Parser version information
#define AQUA_V_COMMAND_PARSER_VERSION "0.1.0"
#define AQUA_V_COMMAND_PARSER_BUILD_DATE "2025-07-28"

// Default configuration values
#define AQUA_V_DEFAULT_CONFIDENCE_THRESHOLD 0.8f
#define AQUA_V_DEFAULT_COMMAND_TIMEOUT_MS 5000
#define AQUA_V_MAX_COMMAND_PARAMETERS 10
#define AQUA_V_MAX_COMMAND_LENGTH 256

// Safety thresholds
#define AQUA_V_SAFETY_CRITICAL_THRESHOLD 0.8f
#define AQUA_V_SAFETY_WARNING_THRESHOLD 0.6f

/**
 * ============================================================================
 * END OF HEADER FILE
 * ============================================================================
 * 
 * This header file provides the complete interface for the AQUA V. Command
 * Parser Engine, designed specifically for aerospace training applications
 * with full compliance to:
 * 
 * - AQUA V. Official Nomenclature System v3.1
 * - Digital Thread Integration Standards
 * - Aerospace Software Development Standards (DO-178C)
 * - Safety-Critical System Requirements
 * - ATA Chapter Classifications
 * 
 * ============================================================================
 */
