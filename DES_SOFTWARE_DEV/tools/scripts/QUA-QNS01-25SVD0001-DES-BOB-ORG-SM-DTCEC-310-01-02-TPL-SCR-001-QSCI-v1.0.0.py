import argparse
import json
import sys
from datetime import datetime
from pathlib import Path
from typing import Any, Dict


class PerformanceAnalyzer:
    """Analyze performance test results and generate reports."""
    
    def __init__(self, input_dir: str, output_file: str, thresholds_file: str = None, verbose: bool = False):
        self.input_dir = Path(input_dir)
        self.output_path = Path(output_file)
        self.thresholds_file = thresholds_file
        self.verbose = verbose
        self.results = []
    
    def collect_results(self) -> None:
        """Collect performance test results from the input directory."""
        if self.verbose:
            print(f"Collecting results from: {self.input_dir}")
        
        # For simplicity, let's assume results are in JSON files in the input directory
        for file in self.input_dir.glob("*.json"):
            with open(file) as f:
                result = json.load(f)
                self.results.append(result)
        
        if self.verbose:
            print(f"Found {len(self.results)} result files")
    
    def generate_report(self) -> Dict[str, Any]:
        """Generate a performance report from the collected results."""
        if self.verbose:
            print("Generating report")
        
        # Simple report structure
        report = {
            "timestamp": datetime.now().isoformat(),
            "summary": {
                "total_tests": len(self.results),
                "passed_tests": sum(1 for r in self.results if r['passed']),
                "failed_tests": sum(1 for r in self.results if not r['passed']),
                "pass_rate": sum(1 for r in self.results if r['passed']) / len(self.results) if self.results else 0,
            },
            "tests": {r['test_name']: r for r in self.results},
        }
        
        if self.verbose:
            print("Report generated")
        
        return report
    
    def save_report(self, report: Dict[str, Any]) -> None:
        """Save performance report to output file."""
        with open(self.output_path, 'w') as f:
            json.dump(report, f, indent=2)
        
        print(f"Report saved to: {self.output_path}")
        
        # Also create a summary markdown file
        summary_path = self.output_path.parent / f"{self.output_path.stem}_summary.md"
        self._generate_markdown_summary(report, summary_path)
    
    def _generate_markdown_summary(self, report: Dict[str, Any], output_path: Path) -> None:
        """Generate a markdown summary of the performance report."""
        with open(output_path, 'w') as f:
            f.write("# Performance Test Report\n\n")
            f.write(f"**Generated:** {report['timestamp']}\n\n")
            
            # Summary section
            summary = report['summary']
            f.write("## Summary\n\n")
            f.write(f"- Total Tests: {summary['total_tests']}\n")
            f.write(f"- Passed: {summary['passed_tests']}\n")
            f.write(f"- Failed: {summary['failed_tests']}\n")
            f.write(f"- Pass Rate: {summary['pass_rate']:.1%}\n\n")
            
            # Test results
            f.write("## Test Results\n\n")
            for test_name, test_result in report['tests'].items():
                status = "✅ PASSED" if test_result['passed'] else "❌ FAILED"
                f.write(f"### {test_name} - {status}\n\n")
                
                # Metrics
                if test_result['metrics']:
                    f.write("#### Metrics\n\n")
                    for metric_type, values in test_result['metrics'].items():
                        f.write(f"**{metric_type.replace('_', ' ').title()}:**\n")
                        if isinstance(values, dict):
                            for key, value in values.items():
                                if isinstance(value, float):
                                    f.write(f"- {key}: {value:.2f}\n")
                                else:
                                    f.write(f"- {key}: {value}\n")
                        f.write("\n")
                
                # Violations
                if test_result['violations']:
                    f.write("#### Threshold Violations\n\n")
                    for violation_type, message in test_result['violations'].items():
                        f.write(f"- ⚠️ {message}\n")
                    f.write("\n")
                
                f.write("---\n\n")
        
        print(f"Markdown summary saved to: {output_path}")
    
    def run(self) -> int:
        """Run the complete performance analysis."""
        try:
            self.collect_results()
            
            if not self.results:
                print("No performance test results found")
                return 1
            
            report = self.generate_report()
            self.save_report(report)
            
            # Return exit code based on pass rate
            if report['summary']['pass_rate'] < 1.0:
                print(f"Performance tests failed: {report['summary']['failed_tests']} tests failed")
                return 1
            
            print("All performance tests passed!")
            return 0
            
        except Exception as e:
            print(f"Error during performance analysis: {e}")
            return 2


def main():
    """Main entry point for the performance analysis script."""
    parser = argparse.ArgumentParser(
        description='Analyze performance test results for quantum software'
    )
    parser.add_argument(
        '--input',
        required=True,
        help='Input directory containing test results'
    )
    parser.add_argument(
        '--output',
        required=True,
        help='Output file for the performance report (JSON)'
    )
    parser.add_argument(
        '--thresholds',
        help='Custom thresholds configuration file'
    )
    parser.add_argument(
        '--verbose',
        action='store_true',
        help='Enable verbose output'
    )
    
    args = parser.parse_args()
    
    # Create analyzer and run
    analyzer = PerformanceAnalyzer(args.input, args.output)
    exit_code = analyzer.run()
    
    sys.exit(exit_code)


if __name__ == '__main__':
    main()