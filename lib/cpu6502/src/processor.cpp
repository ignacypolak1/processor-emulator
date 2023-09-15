#include <algorithm>
#include "../include/instructions.h"

Processor::Processor::Processor() {
    resetCPU();

    instructionMap = {
            {INS_LDA_IMMEDIATE, &Processor::INS_LDA_IMMEDIATE_HANDLE},
            {INS_LDA_ABSOLUTE, &Processor::INS_LDA_ABSOLUTE_HANDLE},
            {INS_LDA_ABSOLUTE_X, &Processor::INS_LDA_ABSOLUTE_X_HANDLE},
            {INS_LDA_ABSOLUTE_Y, &Processor::INS_LDA_ABSOLUTE_Y_HANDLE},
            {INS_LDA_ZEROPAGE, &Processor::INS_LDA_ZEROPAGE_HANDLE},
            {INS_LDA_ZEROPAGE_X, &Processor::INS_LDA_ZEROPAGE_X_HANDLE},
            {INS_LDA_INDEXED_INDIRECT, &Processor::INS_LDA_INDEXED_INDIRECT_HANDLE},
            {INS_LDA_INDIRECT_INDEXED, &Processor::INS_LDA_INDIRECT_INDEXED_HANDLE},
            {INS_JSR, &Processor::INS_JSR_HANDLE}
    };
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
Processor::Byte Processor::Processor::getProcessorStatus(const char& key) const {
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
void Processor::Processor::setProcessorStatus(const char &key, const Byte &value) {
    processor_status.at(key);
    processor_status[key] = value;
}

/**
* Operator override for getting byte of instruction from processor memory
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

/**
* Initialize of processor memory (fill entire processor memory with 0's)
*/
void Processor::Memory::initialize() {
    std::fill(data, data+MAX_MEMORY, 0);
}

/**
* Reset CPU
*/
void Processor::Processor::resetCPU() {

    setProgramCounter(0xFFFC); // Reset Vector Address
    setStackPointer(0x0100); // First Stack Access Address
    memory.initialize(); // Initialize Memory

    for(const auto& pair : registers) { // Reset All General Purpose Registers
        setRegisterValue(pair.first, 0x00);
    }

    for(const auto& pair : processor_status) { // Reset All Status Register Bits
        setProcessorStatus(pair.first, 0x00);
    }
}

std::array<Processor::Byte, MAX_MEMORY> Processor::Processor::getMemory() const {
    std::array<Byte, MAX_MEMORY> memoryArray;
    std::copy(std::begin(memory.data), std::end(memory.data), memoryArray.begin());
    return memoryArray;
}
/**
* Fetch byte of instruction from processor memory.
*
* @param cycles Remaining cycles of processor reference.
* @param requested_cycles Entire number of requested cycles
* @return Byte of instruction from address of current program counter value.
*/
Processor::Byte Processor::Processor::fetchByte(Dword &cycles, const Dword &requested_cycles) {
    Byte byte = memory[program_counter];
    #ifdef DEBUG
        printf("Cycle %i: Fetch Byte: Read byte value: 0x%04X, address: 0x%04X\n", requested_cycles-cycles, byte, getProgramCounter());
    #endif
    cycles--;
    program_counter++;
    return byte;
}

/**
* Fetch word of instruction from processor memory.
*
* @param cycles Remaining cycles of processor reference.
* @param requested_cycles Entire number of requested cycles
* @return Word of instruction from address and address+1 of current program counter value.
*/
Processor::Word Processor::Processor::fetchWord(Dword &cycles, const Dword &requested_cycles) {
    Word word = 0x0000;

    word = (word & 0x00FF) | (memory[program_counter]);
    word = word | memory[program_counter + 1] << 8;

    #ifdef DEBUG
        printf("Cycle %i: Fetch Word: Read word value: 0x%04X, addresses: 0x%04X and 0x%04X\n", requested_cycles-cycles, word, getProgramCounter(), getProgramCounter()+1);
    #endif
    cycles-=2;
    program_counter+=2;
    return word;
}

/**
* Write word in processor memory.
*
* @param address Address to write in processor memory
* @param value Value to write in processor memory
* @param cycles Remaining cycles of processor reference
* @param reqested_cycles Entire number of requested cycles
* @return Word of instruction from address and address+1 of current program counter value.
*/
void Processor::Processor::writeWord(const Word &address, Word value, Dword &cycles, const Dword &reqested_cycles) {

    memory[address] = value & 0x00FF;
    memory[address+1] = (value >> 8);
    #ifdef DEBUG
        printf("Cycle %i: Write Word: Word 0x%04X written under addresses 0x%04X and 0x%04X\n", reqested_cycles-cycles, value, address, address+1);
    #endif
    cycles-=2;
}

/**
* Fetch word of instruction from processor memory.
*
* @param address Address in memory to read byte from
* @param cycles Remaining cycles of processor reference.
* @param reqested_cycles Entire number of requested cycles
* @return Word of instruction from address and address+1 of current program counter value.
*/
Processor::Byte Processor::Processor::readByte(const Word &address, Dword &cycles, const Dword &requested_cycles) {
    Byte instruction = memory[address];
    #ifdef DEBUG
        printf("Cycle %i: Read Byte: Read byte value: 0x%04X, address: 0x%04X\n", requested_cycles-cycles, instruction, address);
    #endif
    cycles--;
    return instruction;
}

/**
* Execute instruction loaded form memory.
*
* @param cycles Number of cycles for instruction execution.
*/
void Processor::Processor::execute(Dword cycles) {
    Dword cycles_num = cycles;

    while(cycles > 0)
    {
        Byte instruction = fetchByte(cycles, cycles_num);
        auto it = instructionMap.find(instruction);
        if (it != instructionMap.end())
        {
            #ifdef DEBUG
                printf("Cycle %i: Execute: Found instruction with opcode: 0x%04X\n", cycles_num-cycles, instruction);
            #endif
            InstructionFunction handler = it->second;
            (this->*handler)(cycles, cycles_num);
        }
        else {
            #ifdef DEBUG
                printf("Cycle %i: Execute: Unknown opcode: 0x%04X\n", cycles_num-cycles, instruction);
            #endif
            break;
            }
        }
    }
void Processor::Processor::setMemoryByte(const Word &address, const Byte value) {
    memory[address] = value;
}
void Processor::Processor::setMemoryWord(const Word &address, const Word value) {
    memory[address] = (value & 0x00FF);
    memory[address + 1] = (value >> 8);
}



