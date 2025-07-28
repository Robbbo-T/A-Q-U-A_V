# 🔍 A.Q.U.A.-V. Nomenclature Validation Tool
## validate-nomenclature.py

"""
A.Q.U.A.-V. Nomenclature Validation Tool
Document ID: AQV-SCR-25JU0001-OPS-SIM-TLS-TD-SIM-006-00-01-SCR-SIM-006-QDAT-v1.0.0

Description: Validates that all files follow A.Q.U.A.-V. nomenclature v3.1
Owner: A.Q.U.A. Venture - Q-Data Governance Division
Classification: AQUA V. INTERNAL - RESTRICTED
Version: 1.0.0
Date: July 28, 2025

© 2025 A.Q.U.A. Venture. All rights reserved.
"""

import os
import re
import sys
from pathlib import Path
from datetime import datetime

# ANSI color codes
class Colors:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'
    BOLD = '\033[1m'
    END = '\033[0m'

def print_header():
    """Print the validation tool header"""
    print(f"{Colors.BLUE}╔══════════════════════════════════════════════════════════════════════════════╗{Colors.END}")
    print(f"{Colors.BLUE}║               A.Q.U.A.-V. NOMENCLATURE VALIDATION TOOL                       ║{Colors.END}")
    print(f"{Colors.BLUE}║                            Version 1.0.0                                    ║{Colors.END}")
    print(f"{Colors.BLUE}║                                                                              ║{Colors.END}")
    print(f"{Colors.BLUE}║    Document ID: AQV-SCR-25JU0001-OPS-SIM-TLS-TD-SIM-006-00-01-SCR-SIM-006   ║{Colors.END}")
    print(f"{Colors.BLUE}╚══════════════════════════════════════════════════════════════════════════════╝{Colors.END}")
    print()

def validate_document_id(doc_id):
    """Validate document ID against A.Q.U.A.-V. nomenclature v3.1"""
    # Define the regex pattern for document ID using named groups for clarity
    pattern = (
        r'^AQV-'  # Prefix
        r'(?P<category>[A-Z]{3})-'  # Category (3 uppercase letters)
        r'(?P<date>\d{8})-'  # Date (8 digits)
        r'(?P<type>[A-Z]{3})-'  # Type (3 uppercase letters)
        r'(?P<identifier>[A-Z0-9-]{3,})-'  # Identifier (alphanumeric and hyphens, 3 or more characters)
        r'(?P<region>[A-Z]{2})-'  # Region (2 uppercase letters)
        r'(?P<subtype>[A-Z]{3})-'  # Subtype (3 uppercase letters)
        r'(?P<serial>\d{3})-'  # Serial number (3 digits)
        r'(?P<revision>\d{2})-'  # Revision number (2 digits)
        r'(?P<version>\d{2})-'  # Version number (2 digits)
        r'(?P<module>[A-Z]{3})-'  # Module (3 uppercase letters)
        r'(?P<system>[A-Z]{3})-'  # System (3 uppercase letters)
        r'(?P<code>\d{3})-'  # Code (3 digits)
        r'(?P<project>[A-Z]{4})-'  # Project (4 uppercase letters)
        r'v(?P<version_number>\d+\.\d+\.\d+)$'  # Version number (semantic versioning)
    )
    return re.match(pattern, doc_id) is not None

def check_file_headers(file_path):
    """Check if file has proper A.Q.U.A.-V. headers"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()  # Read entire file content
            
        issues = []
        
        # Check for Document ID
        if 'Document ID:' not in content and 'AQV-' not in content:
            issues.append("Missing Document ID")
        
        # Check for A.Q.U.A. Venture reference
        if 'A.Q.U.A. Venture' not in content and 'A.Q.U.A.-V.' not in content:
            issues.append("Missing A.Q.U.A. Venture reference")
        
        # Check for classification
        classification_keywords = ['AQUA V. INTERNAL', 'RESTRICTED', 'CONFIDENTIAL', 'PUBLIC']
        if not any(keyword in content for keyword in classification_keywords):
            issues.append("Missing security classification")
        
        # Check for copyright - look for various copyright formats
        copyright_patterns = [
            '© 2025 A.Q.U.A. Venture',
            '(c) 2025 A.Q.U.A. Venture',
            'Copyright 2025 A.Q.U.A. Venture',
            '© 2025 A.Q.U.A.-V.',
            '© 2025 AQUA'
        ]
        if not any(pattern in content for pattern in copyright_patterns):
            issues.append("Missing copyright notice")
            
        return issues
        
    except Exception as e:
        return [f"Error reading file: {str(e)}"]

def validate_directory_structure():
    """Validate the directory structure follows nomenclature"""
    simulation_root = Path("/workspaces/A.Q.U.A.-V./TOOLS_INFRASTRUCTURE/SOFTWARE_TOOLS/SIMULATION_TOOLS")
    
    required_dirs = [
        "AERODYNAMICS_SIMULATION",
        "QUANTUM_SIMULATION", 
        "STRUCTURAL_SIMULATION",
        "FLIGHT_SIMULATION",
        "DIGITAL_TWIN_SIMULATION",
        "SPACE_SYSTEMS_SIMULATION",
        "MANUFACTURING_SIMULATION",
        "SYSTEMS_INTEGRATION",
        "VISUALIZATION_RENDERING",
        "HPC_INTEGRATION",
        "UTILITIES",
        "DOCUMENTATION"
    ]
    
    issues = []
    for dir_name in required_dirs:
        dir_path = simulation_root / dir_name
        if not dir_path.exists():
            issues.append(f"Missing required directory: {dir_name}")
        elif not dir_path.is_dir():
            issues.append(f"Expected directory but found file: {dir_name}")
    
    return issues

def scan_files():
    """Scan all files for nomenclature compliance"""
    simulation_root = Path("/workspaces/A.Q.U.A.-V./TOOLS_INFRASTRUCTURE/SOFTWARE_TOOLS/SIMULATION_TOOLS")
    
    print(f"{Colors.CYAN}📁 Scanning files in: {simulation_root}{Colors.END}")
    print()
    
    total_files = 0
    compliant_files = 0
    issues_found = []
    
    for file_path in simulation_root.rglob("*"):
        if file_path.is_file() and not file_path.name.startswith('.'):
            total_files += 1
            
            # Check specific file types
            if file_path.suffix in ['.md', '.py', '.sh', '.yml', '.yaml', '.txt']:
                issues = check_file_headers(file_path)
                
                if not issues:
                    compliant_files += 1
                    print(f"{Colors.GREEN}✓{Colors.END} {file_path.relative_to(simulation_root)}")
                else:
                    print(f"{Colors.RED}✗{Colors.END} {file_path.relative_to(simulation_root)}")
                    for issue in issues:
                        print(f"  {Colors.YELLOW}⚠{Colors.END}  {issue}")
                    issues_found.extend([(str(file_path.relative_to(simulation_root)), issue) for issue in issues])
            else:
                # For binary files, just check if they exist
                compliant_files += 1
                print(f"{Colors.BLUE}•{Colors.END} {file_path.relative_to(simulation_root)} (binary file)")
    
    return total_files, compliant_files, issues_found

def main():
    """Main validation function"""
    print_header()
    
    print(f"{Colors.BOLD}🚀 Starting A.Q.U.A.-V. Nomenclature Validation{Colors.END}")
    print(f"Timestamp: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()
    
    # Validate directory structure
    print(f"{Colors.CYAN}📂 Validating directory structure...{Colors.END}")
    dir_issues = validate_directory_structure()
    
    if not dir_issues:
        print(f"{Colors.GREEN}✓ Directory structure is compliant{Colors.END}")
    else:
        print(f"{Colors.RED}✗ Directory structure issues found:{Colors.END}")
        for issue in dir_issues:
            print(f"  {Colors.YELLOW}⚠{Colors.END}  {issue}")
    print()
    
    # Scan files
    total_files, compliant_files, file_issues = scan_files()
    
    # Summary
    print(f"{Colors.BOLD}📊 VALIDATION SUMMARY{Colors.END}")
    print("=" * 50)
    print(f"Total files scanned: {total_files}")
    print(f"Compliant files: {compliant_files}")
    print(f"Non-compliant files: {total_files - compliant_files}")
    print(f"Directory issues: {len(dir_issues)}")
    print(f"File issues: {len(file_issues)}")
    
    compliance_rate = (compliant_files / total_files * 100) if total_files > 0 else 0
    print(f"Compliance rate: {compliance_rate:.1f}%")
    
    if compliance_rate >= 90:
        print(f"{Colors.GREEN}🎉 Excellent compliance!{Colors.END}")
    elif compliance_rate >= 75:
        print(f"{Colors.YELLOW}⚠ Good compliance, minor issues{Colors.END}")
    else:
        print(f"{Colors.RED}❌ Poor compliance, action required{Colors.END}")
    
    print()
    print(f"{Colors.BLUE}📞 Support Contact:{Colors.END} nomenclature@aqua-v.aerospace")
    print(f"{Colors.BLUE}📖 Documentation:{Colors.END} https://docs.aqua-v.aerospace/nomenclature")
    print()
    print(f"{Colors.GREEN}© 2025 A.Q.U.A. Venture. All rights reserved.{Colors.END}")
    
    # Exit with appropriate code
    if dir_issues or file_issues:
        sys.exit(1)
    else:
        sys.exit(0)

if __name__ == "__main__":
    main()
