#!/usr/bin/env python3
"""
Documentation Validation Script
Validates documentation for broken links, missing sections, etc.
"""

import argparse
import os
import re
import sys
from pathlib import Path
from typing import List, Set, Tuple
import markdown
from urllib.parse import urlparse
import requests


class DocumentationValidator:
    """Validates project documentation."""
    
    def __init__(self, docs_path: str):
        self.docs_path = Path(docs_path)
        self.errors = []
        self.warnings = []
        
    def validate_links(self, content: str, file_path: Path) -> None:
        """Validate all links in a markdown file."""
        # Find all links
        link_pattern = r'\[([^\]]+)\]\(([^)]+)\)'
        links = re.findall(link_pattern, content)
        
        for link_text, link_url in links:
            if link_url.startswith('http'):
                # External link
                if not self._check_external_link(link_url):
                    self.errors.append(f"{file_path}: Broken external link: {link_url}")
            elif link_url.startswith('#'):
                # Anchor link
                if not self._check_anchor(content, link_url[1:]):
                    self.warnings.append(f"{file_path}: Missing anchor: {link_url}")
            else:
                # Internal link
                if not self._check_internal_link(file_path, link_url):
                    self.errors.append(f"{file_path}: Broken internal link: {link_url}")
    
    def _check_external_link(self, url: str) -> bool:
        """Check if external URL is accessible."""
        try:
            response = requests.head(url, timeout=5, allow_redirects=True)
            return response.status_code < 400
        except:
            return False
    
    def _check_anchor(self, content: str, anchor: str) -> bool:
        """Check if anchor exists in content."""
        # Convert anchor to header format
        header_text = anchor.replace('-', ' ').title()
        return header_text in content
    
    def _check_internal_link(self, current_file: Path, link: str) -> bool:
        """Check if internal file link exists."""
        link_path = (current_file.parent / link).resolve()
        return link_path.exists()
    
    def validate_structure(self, content: str, file_path: Path) -> None:
        """Validate document structure."""
        lines = content.split('\n')
        
        # Check for title
        if not any(line.startswith('# ') for line in lines[:5]):
            self.warnings.append(f"{file_path}: Missing main title (# Title)")
        
        # Check for proper header hierarchy
        headers = [line for line in lines if line.startswith('#')]
        last_level = 0
        for header in headers:
            level = len(header.split()[0])
            if level > last_level + 1:
                self.warnings.append(f"{file_path}: Skip in header hierarchy: {header}")
            last_level = level
    
    def validate_code_blocks(self, content: str, file_path: Path) -> None:
        """Validate code blocks have language specified."""
        code_block_pattern = r'```(\w*)\n'
        code_blocks = re.findall(code_block_pattern, content)
        
        for i, lang in enumerate(code_blocks):
            if not lang:
                self.warnings.append(f"{file_path}: Code block {i+1} missing language specifier")
    
    def validate_file(self, file_path: Path) -> None:
        """Validate a single documentation file."""
        print(f"Validating: {file_path}")
        
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        self.validate_links(content, file_path)
        self.validate_structure(content, file_path)
        self.validate_code_blocks(content, file_path)
    
    def validate_all(self) -> int:
        """Validate all documentation files."""
        # Find all markdown files
        md_files = list(self.docs_path.rglob('*.md'))
        
        if not md_files:
            print("No markdown files found")
            return 1
        
        for md_file in md_files:
            self.validate_file(md_file)
        
        # Print results
        if self.errors:
            print("\nErrors found:")
            for error in self.errors:
                print(f"  ❌ {error}")
        
        if self.warnings:
            print("\nWarnings found:")
            for warning in self.warnings:
                print(f"  ⚠️  {warning}")
        
        if not self.errors and not self.warnings:
            print("\n✅ All documentation is valid!")
            return 0
        
        return 1 if self.errors else 0


def main():
    parser = argparse.ArgumentParser(description='Validate project documentation')
    parser.add_argument('--path', required=True, help='Path to documentation directory')
    parser.add_argument('--strict', action='store_true', help='Treat warnings as errors')
    
    args = parser.parse_args()
    
    validator = DocumentationValidator(args.path)
    exit_code = validator.validate_all()
    
    if args.strict and validator.warnings:
        exit_code = 1
    
    sys.exit(exit_code)


if __name__ == '__main__':
    main()
