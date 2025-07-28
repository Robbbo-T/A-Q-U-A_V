#!/bin/bash

# A.Q.U.A.-V. Unreal Engine Structure Validation Script
# Document ID: AQV-SCR-25JU0001-OPS-SIM-TLS-TD-SIM-008-00-01-SCR-UE5-008-QDAT-v1.0.0

echo "🔍 A.Q.U.A.-V. Unreal Engine Environments Structure Validation"
echo "============================================================="
echo ""

# Base directory - Auto-detect current working directory
BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Initialize counters
TOTAL_DIRS=0
TOTAL_FILES=0
MISSING_ITEMS=0

echo "📁 Validating directory structure..."

# Function to check if directory exists
check_directory() {
    local dir_path="$1"
    if [ -d "$BASE_DIR/$dir_path" ]; then
        echo "✅ $dir_path"
        ((TOTAL_DIRS++))
    else
        echo "❌ MISSING: $dir_path"
        ((MISSING_ITEMS++))
    fi
}

# Function to check if file exists
check_file() {
    local file_path="$1"
    if [ -f "$BASE_DIR/$file_path" ]; then
        echo "✅ $file_path"
        ((TOTAL_FILES++))
    else
        echo "❌ MISSING: $file_path"
        ((MISSING_ITEMS++))
    fi
}

echo ""
echo "📘 Checking Core Documentation Files..."
check_file "README.md"
check_file "SETUP_GUIDE.md"
check_file "UNREAL_STANDARDS.md"
check_file "LICENSE_UNREAL.md"
check_file "create-directory-structure.sh"

echo ""
echo "📘 Checking Configuration Files..."
check_file "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/Config/DefaultEngine.ini"
check_file "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/Config/DefaultInput.ini"
check_file "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/AQUAV_Visualization.uproject"

echo ""
echo "🛩️ Validating AIRCRAFT_VISUALIZATION structure..."
# Aircraft Visualization directories
AIRCRAFT_DIRS=(
    "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/Content/Aircraft/Meshes/Fuselage"
    "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/Content/Aircraft/Materials/Quantum_Surfaces"
    "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/Content/Aircraft/Blueprints/BP_BWB_Q100_Master"
    "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/Content/Environments/Hangar_Scene"
    "AIRCRAFT_VISUALIZATION/BWB_Q100_Digital_Showroom/Plugins/AQUA_V_Core"
    "AIRCRAFT_VISUALIZATION/eVTOL_Experience/Content/Urban_Environment"
    "AIRCRAFT_VISUALIZATION/Fleet_Visualization/Multi_Aircraft_Scene"
)

for dir in "${AIRCRAFT_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🎓 Validating TRAINING_SIMULATIONS structure..."
# Training Simulations directories
TRAINING_DIRS=(
    "TRAINING_SIMULATIONS/Pilot_Training_VR/Content/Cockpit_Environments/BWB_Q100_Cockpit/Instruments"
    "TRAINING_SIMULATIONS/Pilot_Training_VR/Content/Training_Scenarios/Emergency_Procedures"
    "TRAINING_SIMULATIONS/Pilot_Training_VR/Content/VR_Interactions/Hand_Tracking"
    "TRAINING_SIMULATIONS/Maintenance_Training_AR/Content/Engine_Procedures"
    "TRAINING_SIMULATIONS/Ground_Crew_Simulation/Safety_Protocols"
)

for dir in "${TRAINING_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🔬 Validating DESIGN_REVIEW_ENVIRONMENTS structure..."
# Design Review directories
DESIGN_DIRS=(
    "DESIGN_REVIEW_ENVIRONMENTS/Collaborative_Design_Space/Content/Meeting_Rooms/Virtual_Conference"
    "DESIGN_REVIEW_ENVIRONMENTS/Collaborative_Design_Space/Content/Design_Tools/Annotation_System"
    "DESIGN_REVIEW_ENVIRONMENTS/Collaborative_Design_Space/Content/Avatar_System/User_Avatars"
    "DESIGN_REVIEW_ENVIRONMENTS/Engineering_Walkthrough/Full_Scale_Models"
    "DESIGN_REVIEW_ENVIRONMENTS/Customer_Experience/Cabin_Configuration"
)

for dir in "${DESIGN_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "⚛️ Validating QUANTUM_VISUALIZATION structure..."
# Quantum Visualization directories
QUANTUM_DIRS=(
    "QUANTUM_VISUALIZATION/Quantum_System_Explorer/Content/Quantum_Circuits/Qubit_Visualization"
    "QUANTUM_VISUALIZATION/Quantum_System_Explorer/Content/Quantum_States/Bloch_Sphere"
    "QUANTUM_VISUALIZATION/Quantum_System_Explorer/Content/Algorithm_Visualization/QAOA_Steps"
    "QUANTUM_VISUALIZATION/Quantum_System_Explorer/Shaders/Quantum_Probability"
    "QUANTUM_VISUALIZATION/Quantum_Navigation_Display/GPS_Free_Navigation"
)

for dir in "${QUANTUM_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🏭 Validating MANUFACTURING_VISUALIZATION structure..."
# Manufacturing directories
MANUFACTURING_DIRS=(
    "MANUFACTURING_VISUALIZATION/Factory_Digital_Twin/Content/Production_Line"
    "MANUFACTURING_VISUALIZATION/Factory_Digital_Twin/Content/Robot_Simulation"
    "MANUFACTURING_VISUALIZATION/Assembly_Guidance_AR/Step_By_Step"
)

for dir in "${MANUFACTURING_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🛸 Validating MISSION_VISUALIZATION structure..."
# Mission Visualization directories
MISSION_DIRS=(
    "MISSION_VISUALIZATION/Flight_Path_Visualization/Content/Globe_View"
    "MISSION_VISUALIZATION/Space_Operations/Orbital_Mechanics"
    "MISSION_VISUALIZATION/Emergency_Response/Incident_Replay"
)

for dir in "${MISSION_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "📊 Validating DATA_VISUALIZATION structure..."
# Data Visualization directories
DATA_DIRS=(
    "DATA_VISUALIZATION/Telemetry_Dashboard/Content/Real_Time_Gauges"
    "DATA_VISUALIZATION/Fleet_Analytics/Aircraft_Status"
    "DATA_VISUALIZATION/Quantum_Metrics/Coherence_Time"
)

for dir in "${DATA_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🎨 Validating SHARED_ASSETS structure..."
# Shared Assets directories
SHARED_DIRS=(
    "SHARED_ASSETS/Common_Materials/PBR_Library"
    "SHARED_ASSETS/Blueprint_Library/Interaction_Systems"
    "SHARED_ASSETS/Audio/Engine_Sounds"
    "SHARED_ASSETS/Post_Process/VR_Optimization"
)

for dir in "${SHARED_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🔧 Validating DEVELOPMENT_TOOLS structure..."
# Development Tools directories
DEV_DIRS=(
    "DEVELOPMENT_TOOLS/Editor_Utilities/Asset_Importers"
    "DEVELOPMENT_TOOLS/Performance_Tools/Profiler_Configs"
    "DEVELOPMENT_TOOLS/Build_Pipeline/Automated_Builds"
)

for dir in "${DEV_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "📚 Validating DOCUMENTATION structure..."
# Documentation directories
DOC_DIRS=(
    "DOCUMENTATION/Project_Setup/System_Requirements"
    "DOCUMENTATION/Content_Guidelines/Art_Standards"
    "DOCUMENTATION/API_Documentation/AQUA_V_Plugin"
    "DOCUMENTATION/Tutorials/Basic_Navigation"
)

for dir in "${DOC_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🧪 Validating TEST_PROJECTS structure..."
# Test Projects directories
TEST_DIRS=(
    "TEST_PROJECTS/Unit_Tests/Blueprint_Tests"
    "TEST_PROJECTS/Integration_Tests/VR_Hardware"
    "TEST_PROJECTS/User_Studies/Usability_Scenarios"
)

for dir in "${TEST_DIRS[@]}"; do
    check_directory "$dir"
done

echo ""
echo "🔍 Checking .gitkeep files..."
GITKEEP_COUNT=$(find "$BASE_DIR" -name ".gitkeep" -type f | wc -l)
echo "📁 Found $GITKEEP_COUNT .gitkeep files"

echo ""
echo "📊 VALIDATION SUMMARY"
echo "===================="
echo "✅ Validated Directories: $TOTAL_DIRS"
echo "✅ Validated Files: $TOTAL_FILES"
echo "📁 .gitkeep Files: $GITKEEP_COUNT"

if [ $MISSING_ITEMS -eq 0 ]; then
    echo "🎉 ALL CHECKS PASSED!"
    echo "✅ A.Q.U.A.-V. Unreal Engine Environments structure is complete and valid"
    echo ""
    echo "🚀 Ready for:"
    echo "   • Unreal Engine project setup"
    echo "   • VR/AR development"
    echo "   • Team collaboration"
    echo "   • Production deployment"
    echo ""
    echo "📞 Next Steps:"
    echo "   1. Install Unreal Engine 5.3+"
    echo "   2. Open AQUAV_Visualization.uproject"
    echo "   3. Configure VR/AR hardware"
    echo "   4. Import BWB-Q100 models"
    echo "   5. Set up cloud services"
else
    echo "⚠️  VALIDATION ISSUES FOUND: $MISSING_ITEMS missing items"
    echo "❌ Please resolve missing directories/files before proceeding"
    exit 1
fi

echo ""
echo "🔒 Security Classification: AQUA V. INTERNAL - RESTRICTED"
echo "📄 Document ID: AQV-SCR-25JU0001-OPS-SIM-TLS-TD-SIM-008-00-01-SCR-UE5-008-QDAT-v1.0.0"
echo "© 2025 A.Q.U.A. Venture. All rights reserved."
