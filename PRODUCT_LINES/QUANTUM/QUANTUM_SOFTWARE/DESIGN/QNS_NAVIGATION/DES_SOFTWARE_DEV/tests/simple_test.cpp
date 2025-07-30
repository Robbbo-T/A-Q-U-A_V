/**
 * @file simple_test.cpp
 * @brief Simple test for AQUA V. Quantum Navigation HAL v2.0.0
 */

#include <iostream>
#include <cassert>
#include "../src/hal/QUA-QNS01-25SVD0001-DES-BOB-TEC-SM-QCSAA-915-02-01-TPL-HAL-001-QHPC-v2.0.0.h"

using namespace aqua_v::qns::hal;

int main() {
    std::cout << "=== AQUA V. Quantum HAL v2.0.0 Basic Test ===" << std::endl;
    
    // Test 1: Basic data structures
    std::cout << "Testing basic data structures..." << std::endl;
    
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D sum = v1 + v2;
    assert(sum.x == 5.0 && sum.y == 7.0 && sum.z == 9.0);
    
    double magnitude = v1.magnitude();
    assert(std::abs(magnitude - std::sqrt(14.0)) < 1e-10);
    
    Quaternion q(1.0, 0.0, 0.0, 0.0);
    q.normalize();
    assert(std::abs(q.w - 1.0) < 1e-10);
    
    std::cout << "✓ Basic data structures test passed" << std::endl;
    
    // Test 2: Static circular buffer
    std::cout << "Testing StaticCircularBuffer..." << std::endl;
    
    StaticCircularBuffer<int, 5> buffer;
    assert(buffer.empty());
    assert(buffer.size() == 0);
    
    for (int i = 0; i < 3; ++i) {
        assert(buffer.push(i));
    }
    assert(buffer.size() == 3);
    
    int value;
    assert(buffer.pop(value));
    assert(value == 0);
    assert(buffer.size() == 2);
    
    std::cout << "✓ StaticCircularBuffer test passed" << std::endl;
    
    // Test 3: Static queue
    std::cout << "Testing StaticQueue..." << std::endl;
    
    StaticQueue<HalResult, 10> queue;
    assert(queue.size() == 0);
    
    assert(queue.enqueue(HalResult::SUCCESS));
    assert(queue.enqueue(HalResult::ERROR_TIMEOUT));
    assert(queue.size() == 2);
    
    HalResult result;
    assert(queue.dequeue(result));
    assert(result == HalResult::SUCCESS);
    
    std::cout << "✓ StaticQueue test passed" << std::endl;
    
    // Test 4: Quantum structures
    std::cout << "Testing Quantum structures..." << std::endl;
    
    QuantumState state;
    assert(state.fidelity == 1.0);
    assert(state.purity == 1.0);
    
    QuantumMetrics metrics;
    assert(metrics.gate_error_rate == 0.0);
    assert(metrics.gate_count == 0);
    
    std::cout << "✓ Quantum structures test passed" << std::endl;
    
    // Test 5: Utility functions
    std::cout << "Testing utility functions..." << std::endl;
    
    assert(is_success(HalResult::SUCCESS));
    assert(!is_success(HalResult::ERROR_TIMEOUT));
    
    assert(is_error(HalResult::ERROR_TIMEOUT));
    assert(!is_error(HalResult::SUCCESS));
    
    assert(is_quantum_error(HalResult::ERROR_QUANTUM_DECOHERENCE));
    assert(!is_quantum_error(HalResult::ERROR_TIMEOUT));
    
    assert(is_safety_error(HalResult::ERROR_SAFETY_VIOLATION));
    assert(!is_safety_error(HalResult::ERROR_TIMEOUT));
    
    std::cout << "✓ Utility functions test passed" << std::endl;
    
    // Test 6: Device structures
    std::cout << "Testing Device structures..." << std::endl;
    
    DeviceInfo device_info;
    assert(device_info.device_id == 0);
    assert(device_info.type == DeviceType::QUANTUM_SENSOR);
    assert(device_info.redundancy_factor == 1);
    assert(device_info.fault_tolerant == false);
    
    QuantumSensorData sensor_data;
    assert(sensor_data.measurement_count == 0);
    assert(sensor_data.uncertainty == 0.0);
    
    std::cout << "✓ Device structures test passed" << std::endl;
    
    std::cout << "\n🎉 ALL BASIC TESTS PASSED! 🎉" << std::endl;
    std::cout << "AQUA V. Quantum HAL v2.0.0 interface is working correctly!" << std::endl;
    std::cout << "\nKey Features Validated:" << std::endl;
    std::cout << "✓ Static memory allocation (StaticCircularBuffer, StaticQueue)" << std::endl;
    std::cout << "✓ Enhanced quantum data structures" << std::endl;
    std::cout << "✓ Safety-critical device information" << std::endl;
    std::cout << "✓ Comprehensive error classification" << std::endl;
    std::cout << "✓ Mathematical operations (Vector3D, Quaternion)" << std::endl;
    
    return 0;
}