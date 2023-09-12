#include "processor.h"
#include <iostream>

Processor::Processor::Processor() {
    resetCPU();
}

Processor::Processor::~Processor() {}

/**
* Get current program counter value.
*
* @return Current program counter value (type Processor::Word/uint8_t).
*/
Processor::Word Processor::Processor::getProgramCounter() const {
    return program_counter;
}

/**
* Get current stack register value.
*
* @return Current stack register value (type Processor::Word/uint8_t).
*/
Processor::Word Processor::Processor::getStackPointer() const {
    return stack_pointer;
}

/**
* Get current value of general purpose register by register name.
*
* @param key Register name
* @return Current general purpose register value (type Processor::Word/uint8_t).
* @throws std::out_of_range Thrown if key doesn't exist.
*/
Processor::Byte Processor::Processor::getRegisterValue(const char& key) const {
    return registers.at(key);
}

/**
* Get current state of specific bit in processor status register.
*
* @param key Status bit name
* @return Current state of specific bit in processor status register (type bool, true for set, false for unset).
* @throws std::out_of_range Thrown if key doesn't exist.
*/
bool Processor::Processor::getProcessorStatus(const char& key) const {
    return processor_status.at(key);
}

/**
* Set program counter register.
*
* @param values Value to set in program counter.
*/
void Processor::Processor::setProgramCounter(const Word& value) {
    program_counter = value;
}

/**
* Set stack register.
*
* @param values Value to set in stack register.
*/
void Processor::Processor::setStackPointer(const Word &value) {
    stack_pointer = value;
}

/**
* Set value in specific general purpose register.
*
* @param key General purpose register name.
* @param value Value to set in specific general purpose register.
* @throws std::out_of_range Thrown if key doesn't exist.
*/
void Processor::Processor::setRegisterValue(const char &key, const Byte &value) {
    registers.at(key);
    registers[key] = value;
}

/**
* Set specific bit in processor status register.
*
* @param key Specific bit name.
* @param value Value to set for specific bit.
* @throws std::out_of_range Thrown if key doesn't exist.
*/
void Processor::Processor::setProcessorStatus(const char &key, const bool &value) {
    processor_status.at(key);
    processor_status[key] = value;
}

/**
* Reset CPU
*/
void Processor::Processor::resetCPU() {

    setProgramCounter(0xFFFC); // Reset Vector Address
    setStackPointer(0x0100); // First Stack Access Address

    for(const auto& pair : registers) { // Reset All General Purpose Registers
        setRegisterValue(pair.first, 0x00);
    }

    for(const auto& pair : processor_status) { // Reset All Status Register Bits
        setProcessorStatus(pair.first, false);
    }
}

