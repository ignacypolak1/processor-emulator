#include "memory.h"

/**
* Initialize of processor memory (fill entire processor memory with 0's).
*/
void Processor::Memory::initialize() {
    std::fill(data, data+MAX_MEMORY, 0);
}

/**
* Operator override for getting byte of instruction from processor memory.
*
* @param address Address to get byte of instruction from.
*/
Processor::Byte& Processor::Memory::operator [](Word address) {
    if(address < MAX_MEMORY) {
        return data[address];
    }
    else {
        throw std::out_of_range("Emulated processor out of memory");
    }
}

