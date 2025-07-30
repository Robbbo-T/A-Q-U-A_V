#!/bin/bash
# Performance Analysis Script for Quantum Software
# Document: QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-DTCEC-310-02-01-TPL-SCR-001-QHPC-v1.0.0.py
# Version: 1.0.0
# Owner: QHPC (Quantum High Performance Computing Division)

"""
Performance analysis script for quantum software testing.
Analyzes test results and generates performance reports.
"""

import argparse
import json
import os
import sys
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime
import pandas as pd


class PerformanceAnalyzer:
    """Analyzes quantum software performance metrics."""
    
    def __init__(self, input_path: str, output_path: str):
        self.input_path = Path(input_path)
        self.output_path = Path(output_path)
        self.metrics = {}
        self.thresholds = {
            'quantum_circuit_depth': 1000,
            'gate_fidelity': 0.95,
            'execution_time_ms': 5000,
            'memory_usage_mb': 1024,
            'qubit_count': 32,
            'success_rate': 0.90
        }
    
    def analyze_quantum_performance(self, test_data: dict) -> dict:
        """Analyze quantum-specific performance metrics."""
        quantum_metrics = {}
        
        # Circuit depth analysis
        if 'circuit_depth' in test_data:
            quantum_metrics['circuit_depth'] = {
                'value': test_data['circuit_depth'],
                'threshold': self.thresholds['quantum_circuit_depth'],
                'status': 'PASS' if test_data['circuit_depth'] <= self.thresholds['quantum_circuit_depth'] else 'FAIL'
            }
        
        # Gate fidelity analysis
        if 'gate_fidelity' in test_data:
            quantum_metrics['gate_fidelity'] = {
                'value': test_data['gate_fidelity'],
                'threshold': self.thresholds['gate_fidelity'],
                'status': 'PASS' if test_data['gate_fidelity'] >= self.thresholds['gate_fidelity'] else 'FAIL'
            }
        
        # Quantum execution time
        if 'quantum_execution_time' in test_data:
            quantum_metrics['execution_time'] = {
                'value': test_data['quantum_execution_time'],
                'threshold': self.thresholds['execution_time_ms'],
                'status': 'PASS' if test_data['quantum_execution_time'] <= self.thresholds['execution_time_ms'] else 'FAIL'
            }
        
        return quantum_metrics
    
    def analyze_general_performance(self, test_data: dict) -> dict:
        """Analyze general performance metrics."""
        general_metrics = {}
        
        # Memory usage
        if 'memory_usage' in test_data:
            general_metrics['memory_usage'] = {
                'value': test_data['memory_usage'],
                'threshold': self.thresholds['memory_usage_mb'],
                'status': 'PASS' if test_data['memory_usage'] <= self.thresholds['memory_usage_mb'] else 'FAIL'
            }
        
        # Success rate
        if 'success_rate' in test_data:
            general_metrics['success_rate'] = {
                'value': test_data['success_rate'],
                'threshold': self.thresholds['success_rate'],
                'status': 'PASS' if test_data['success_rate'] >= self.thresholds['success_rate'] else 'FAIL'
            }
        
        return general_metrics
    
    def load_test_results(self) -> list:
        """Load performance test results from input directory."""
        results = []
        
        if self.input_path.is_file():
            with open(self.input_path, 'r') as f:
                if self.input_path.suffix == '.json':
                    results.append(json.load(f))
                else:
                    # Assume CSV format
                    df = pd.read_csv(self.input_path)
                    results = df.to_dict('records')
        else:
            # Directory with multiple files
            for file_path in self.input_path.glob('*.json'):
                with open(file_path, 'r') as f:
                    results.append(json.load(f))
        
        return results
    
    def generate_report(self) -> dict:
        """Generate comprehensive performance report."""
        test_results = self.load_test_results()
        
        if not test_results:
            print("No test results found!")
            return {}
        
        report = {
            'metadata': {
                'timestamp': datetime.now().isoformat(),
                'test_count': len(test_results),
                'analyzer_version': '1.0.0',
                'aqua_v_component': 'Quantum Software Development'
            },
            'summary': {
                'total_tests': len(test_results),
                'passed_tests': 0,
                'failed_tests': 0,
                'overall_status': 'UNKNOWN'
            },
            'quantum_metrics': {},
            'general_metrics': {},
            'detailed_results': []
        }
        
        all_quantum_metrics = []
        all_general_metrics = []
        
        for i, test_data in enumerate(test_results):
            # Analyze individual test
            quantum_metrics = self.analyze_quantum_performance(test_data)
            general_metrics = self.analyze_general_performance(test_data)
            
            all_quantum_metrics.append(quantum_metrics)
            all_general_metrics.append(general_metrics)
            
            # Determine test status
            test_passed = True
            for metrics_group in [quantum_metrics, general_metrics]:
                for metric_name, metric_data in metrics_group.items():
                    if metric_data['status'] == 'FAIL':
                        test_passed = False
                        break
                if not test_passed:
                    break
            
            if test_passed:
                report['summary']['passed_tests'] += 1
            else:
                report['summary']['failed_tests'] += 1
            
            # Add to detailed results
            report['detailed_results'].append({
                'test_id': i + 1,
                'status': 'PASS' if test_passed else 'FAIL',
                'quantum_metrics': quantum_metrics,
                'general_metrics': general_metrics
            })
        
        # Calculate overall metrics
        report['summary']['overall_status'] = 'PASS' if report['summary']['failed_tests'] == 0 else 'FAIL'
        
        # Aggregate metrics
        self._aggregate_metrics(all_quantum_metrics, report, 'quantum_metrics')
        self._aggregate_metrics(all_general_metrics, report, 'general_metrics')
        
        return report
    
    def _aggregate_metrics(self, metrics_list: list, report: dict, metrics_key: str):
        """Aggregate metrics across all tests."""
        aggregated = {}
        
        for metrics in metrics_list:
            for metric_name, metric_data in metrics.items():
                if metric_name not in aggregated:
                    aggregated[metric_name] = []
                aggregated[metric_name].append(metric_data['value'])
        
        for metric_name, values in aggregated.items():
            if values:
                report[metrics_key][metric_name] = {
                    'mean': np.mean(values),
                    'median': np.median(values),
                    'std': np.std(values),
                    'min': np.min(values),
                    'max': np.max(values),
                    'count': len(values)
                }
    
    def generate_charts(self, report: dict):
        """Generate performance charts."""
        if not report or 'quantum_metrics' not in report:
            return
        
        # Create charts directory
        charts_dir = self.output_path.parent / 'charts'
        charts_dir.mkdir(exist_ok=True)
        
        # Quantum metrics chart
        fig, axes = plt.subplots(2, 2, figsize=(12, 10))
        fig.suptitle('AQUA V. Quantum Performance Metrics', fontsize=16)
        
        # Circuit depth
        if 'circuit_depth' in report['quantum_metrics']:
            data = report['quantum_metrics']['circuit_depth']
            axes[0, 0].bar(['Mean', 'Median', 'Max'], [data['mean'], data['median'], data['max']])
            axes[0, 0].set_title('Circuit Depth')
            axes[0, 0].set_ylabel('Gates')
        
        # Gate fidelity
        if 'gate_fidelity' in report['quantum_metrics']:
            data = report['quantum_metrics']['gate_fidelity']
            axes[0, 1].bar(['Mean', 'Median', 'Min'], [data['mean'], data['median'], data['min']])
            axes[0, 1].set_title('Gate Fidelity')
            axes[0, 1].set_ylabel('Fidelity')
        
        # Execution time
        if 'execution_time' in report['quantum_metrics']:
            data = report['quantum_metrics']['execution_time']
            axes[1, 0].bar(['Mean', 'Median', 'Max'], [data['mean'], data['median'], data['max']])
            axes[1, 0].set_title('Execution Time')
            axes[1, 0].set_ylabel('Milliseconds')
        
        # Success rate
        if 'success_rate' in report['general_metrics']:
            data = report['general_metrics']['success_rate']
            axes[1, 1].bar(['Mean', 'Median', 'Min'], [data['mean'], data['median'], data['min']])
            axes[1, 1].set_title('Success Rate')
            axes[1, 1].set_ylabel('Rate')
        
        plt.tight_layout()
        plt.savefig(charts_dir / 'quantum_performance_metrics.png', dpi=300, bbox_inches='tight')
        plt.close()
        
        print(f"Charts saved to: {charts_dir}")
    
    def save_report(self, report: dict):
        """Save the performance report to output file."""
        self.output_path.parent.mkdir(parents=True, exist_ok=True)
        
        with open(self.output_path, 'w') as f:
            json.dump(report, f, indent=2, default=str)
        
        print(f"Performance report saved to: {self.output_path}")
    
    def run_analysis(self):
        """Run the complete performance analysis."""
        print("AQUA V. Performance Analyzer v1.0.0")
        print("=====================================")
        print(f"Input: {self.input_path}")
        print(f"Output: {self.output_path}")
        print()
        
        report = self.generate_report()
        
        if not report:
            print("ERROR: No data to analyze")
            return 1
        
        # Print summary
        print("Analysis Summary:")
        print(f"  Total Tests: {report['summary']['total_tests']}")
        print(f"  Passed: {report['summary']['passed_tests']}")
        print(f"  Failed: {report['summary']['failed_tests']}")
        print(f"  Overall Status: {report['summary']['overall_status']}")
        print()
        
        # Save report
        self.save_report(report)
        
        # Generate charts
        try:
            self.generate_charts(report)
        except Exception as e:
            print(f"Warning: Could not generate charts: {e}")
        
        # Return exit code based on overall status
        return 0 if report['summary']['overall_status'] == 'PASS' else 1


def main():
    parser = argparse.ArgumentParser(description='AQUA V. Quantum Performance Analyzer')
    parser.add_argument('--input', required=True, help='Input path (file or directory)')
    parser.add_argument('--output', required=True, help='Output JSON file path')
    parser.add_argument('--charts', action='store_true', help='Generate performance charts')
    
    args = parser.parse_args()
    
    analyzer = PerformanceAnalyzer(args.input, args.output)
    exit_code = analyzer.run_analysis()
    
    sys.exit(exit_code)


if __name__ == '__main__':
    main()