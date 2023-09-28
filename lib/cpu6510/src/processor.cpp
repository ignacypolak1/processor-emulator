#include "instructions.h"
#include <sstream>
#include <iostream>
#include "programs.h"


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
* @return Current stack register value (type Processor::Byte/uint8_t).
*/
Processor::Byte Processor::Processor::getStackPointer() const {
    return stack_pointer;
}

/**
* Get current memory address pointed by stack register value.
*
* @return Current address pointed by stack register value. (type Processor::Word/uint16_t).
*/
Processor::Word Processor::Processor::getStackPointerMemoryAddress() const {
    return 0x0100 + stack_pointer;
}

/**
* Get current value of general purpose register by register name.
*
* @param key Register name.
* @return Current general purpose register value (type Processor::Word/uint8_t).
* @throws std::out_of_range Thrown if key doesn't exist.
*/
Processor::Byte Processor::Processor::getRegisterValue(const char& key) const {
    return registers.at(key);
}

/**
* Get processor status register.
*
* @return Processor status register.
* @throws std::out_of_range Thrown if key doesn't exist.
*/
Processor::Byte Processor::Processor::getProcessorStatusRegister() const {
    return processor_status;
}

/**
* Get processor status register flag.
*
* @return Processor status register flag.
*/
Processor::Byte Processor::Processor::getProcessorStatusFlag(const char &flag) const {
    switch(flag) {
        case 'C':
            return (processor_status & 0x01);
            break;
        case 'Z':
            return (processor_status & 0x02) >> 1;
            break;
        case 'I':
            return (processor_status & 0x04) >> 2;
            break;
        case 'D':
            return (processor_status & 0x08) >> 3;
            break;
        case 'B':
            return (processor_status & 0x10) >> 4;
            break;
        case 'V':
            return (processor_status & 0x40) >> 6;
            break;
        case 'N':
            return (processor_status & 0x80) >> 7;
            break;
        default:
            char errorMessage[100];
            sprintf(errorMessage, "Flag: %c doesn't exists", flag);
            throw std::runtime_error(errorMessage);
    }
}

/**
* Set program counter register.
*
* @param values Value to set in program counter.
*/
void Processor::Processor::setProgramCounter(const Word& address, const std::optional<Dword> cycles, const std::optional<Dword> requested_cycles, const std::string opname) {
    program_counter = address;
    #ifdef DEBUG
    if(opname != "" && cycles.has_value() && requested_cycles.has_value()) {
        printf("Cycle %i: %s: Current program counter set to address (0x%04X)\n", requested_cycles.value()-cycles.value(), opname.c_str(), address);
    }
    #endif
}

/**
* Set stack register.
*
* @param values Value to set in stack register.
*/
void Processor::Processor::setStackPointer(const Byte &value) {
    stack_pointer = value;
}

/**
* Set value in specific general purpose register.
*
* @param key General purpose register name.
* @param value Value to set in specific general purpose register.
* @throws std::out_of_range Thrown if key doesn't exist.
*/
void Processor::Processor::setRegisterValue(const char &key, const Byte &value, const std::optional<Dword> cycles, const std::optional<Dword> requested_cycles, const std::string opname) {
    #ifdef DEBUG
    if(opname != "" && cycles.has_value() && requested_cycles.has_value()){
        printf("Cycle %i: %s: Setting Register(%c) with value 0x%04X\n", requested_cycles.value()-cycles.value(), opname.c_str(), key, value);
    }
    #endif
    registers.at(key);
    registers[key] = value;
}

/**
* Set processor status register.
*
* @param value Value to set in register.
*/
void Processor::Processor::setProcessorStatusRegister(const Byte &value) {
    processor_status = value;
}

/**
* Set processor status register specific flag.
*
* @param flag Flag to set in status register.
*/
void Processor::Processor::setProcessorStatusFlag(const char &flag) {
    switch(flag) {
        case 'C':
            processor_status|=0x01;
            break;
        case 'Z':
            processor_status|=0x02;
            break;
        case 'I':
            processor_status|=0x04;
            break;
        case 'D':
            processor_status|=0x08;
            break;
        case 'B':
            processor_status|=0x10;
            break;
        case 'V':
            processor_status|=0x40;
            break;
        case 'N':
            processor_status|=0x80;
            break;
        default:
            char errorMessage[100];
            sprintf(errorMessage, "Flag: %c doesn't exists", flag);
            throw std::runtime_error(errorMessage);
    }
}

/**
* Reset processor status register specific flag.
*
* @param flag Flag to reset in status register.
*/
void Processor::Processor::resetProcessorStatusFlag(const char &flag) {
    switch(flag) {
        case 'C':
            processor_status&=~0x01;
            break;
        case 'Z':
            processor_status&=~0x02;
            break;
        case 'I':
            processor_status&=~0x04;
            break;
        case 'D':
            processor_status&=~0x08;
            break;
        case 'B':
            processor_status&=~0x10;
            break;
        case 'V':
            processor_status&=~0x40;
            break;
        case 'N':
            processor_status&=~0x80;
            break;
        default:
            char errorMessage[100];
            sprintf(errorMessage, "Flag: %c doesn't exists", flag);
            throw std::runtime_error(errorMessage);
    }
}

/**
* Reset CPU.
*/
void Processor::Processor::resetCPU() {

    setProgramCounter(0xFFFC); // Reset Vector Address
    setStackPointer(0xFF); // First Stack Access Address
    memory.initialize(); // Initialize Memory

    for(const auto& pair : registers) { // Reset All General Purpose Registers
        setRegisterValue(pair.first, 0x00);
    }

    setProcessorStatusRegister(0x20);
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
* @param requested_cycles Entire number of requested cycles.
* @return Byte of instruction from address of current program counter value.
*/
Processor::Byte Processor::Processor::fetchByte(Dword &cycles, const Dword &requested_cycles, std::string opname) {
    Byte byte = memory[program_counter];
    #ifdef DEBUG
        printf("Cycle %i: Fetch Byte: Read byte value: 0x%04X, address: 0x%04X\n", requested_cycles-cycles, byte, getProgramCounter());
        if(opname != "") {
        #ifdef DEBUG
                printf("Cycle %i: %s: Found byte argument: 0x%04X\n", requested_cycles-cycles, opname.c_str(), byte);
        #endif
    }
    #endif

    cycles--;
    program_counter++;
    return byte;
}

/**
* Fetch word of instruction from processor memory.
*
* @param cycles Remaining cycles of processor reference.
* @param requested_cycles Entire number of requested cycles.
* @return Word of instruction from address and address+1 of current program counter value.
*/
Processor::Word Processor::Processor::fetchWord(Dword &cycles, const Dword &requested_cycles, std::string opname) {
    Word word = 0x0000;

    word = (word & 0x00FF) | (memory[program_counter]);
    word = word | memory[program_counter + 1] << 8;

    #ifdef DEBUG
        printf("Cycle %i: Fetch Word: Read word value: 0x%04X, addresses: 0x%04X and 0x%04X\n", requested_cycles-cycles, word, getProgramCounter(), getProgramCounter()+1);
    if(opname != "") {
        #ifdef DEBUG
                printf("Cycle %i: %s: Found word argument: 0x%04X\n", requested_cycles-cycles, opname.c_str(), word);
        #endif
    }
    #endif

    cycles-=2;
    program_counter+=2;
    return word;
}

/**
* Write word in processor memory.
*
* @param address Address to write in processor memory.
* @param value Value to write in processor memory.
* @param cycles Remaining cycles of processor reference.
* @param requested_cycles Entire number of requested cycles.
*/
void Processor::Processor::writeWord(const Word &address, Word value, Dword &cycles, const Dword &requested_cycles, std::string opname) {
    memory[address] = value & 0x00FF;
    memory[address+1] = (value >> 8);
    #ifdef DEBUG
        printf("Cycle %i: Write Word: Word 0x%04X written under addresses 0x%04X and 0x%04X\n", requested_cycles-cycles, value, address, address+1);
        if(opname != ""){
            printf("Cycle %i: %s: Word value 0x%04X saved under addresses (0x%04X and 0x%04X)\n", requested_cycles-cycles, opname.c_str(), value, address, address+1);
        }
    #endif
    cycles-=2;
}

/**
* Write byte in processor memory.
*
* @param address Address to write in processor memory.
* @param value Value to write in processor memory.
* @param cycles Remaining cycles of processor reference.
* @param requested_cycles Entire number of requested cycles.
*/
void Processor::Processor::writeByte(const Word &address, Byte value, Dword &cycles, const Dword &requested_cycles, std::string opname) {
    memory[address] = value;
    #ifdef DEBUG
        printf("Cycle %i: Write Byte: Byte 0x%04X written under address 0x%04X\n", requested_cycles-cycles, value, address);
    #endif
    cycles-=1;
}

/**
* Fetch word of instruction from processor memory.
*
* @param address Address in memory to read byte from.
* @param cycles Remaining cycles of processor reference.
* @param requested_cycles Entire number of requested cycles.
* @return Word of instruction from address and address+1 of current program counter value.
*/
Processor::Byte Processor::Processor::readByte(const Word &address, Dword &cycles, const Dword &requested_cycles, std::string opname) {
    Byte byte = memory[address];
    #ifdef DEBUG
        printf("Cycle %i: Read Byte: Read byte value: 0x%04X, address: 0x%04X\n", requested_cycles-cycles, byte, address);
    if(opname != "") {
        printf("Cycle %i: %s: Found value under address 0x%04X: 0x%04X\n", requested_cycles-cycles, opname.c_str(), address, byte);
    }
    #endif
    cycles--;
    return byte;
}

Processor::Word Processor::Processor::readWord(const Word &address, Dword &cycles, const Dword &requested_cycles, std::string opname) {
    Word word = 0x0000;

    word = (word & 0x00FF) | (memory[address]);
    word = word | memory[address + 1] << 8;

    #ifdef DEBUG
        printf("Cycle %i: Read Word: Read word value: 0x%04X, addresses: 0x%04X and 0x%04X\n", requested_cycles-cycles, word, address, address+1);
        if(opname != "") {
            printf("Cycle %i: %s: Found value under address 0x%04X and 0x%04X: 0x%04X\n", requested_cycles-cycles, opname.c_str(), address, address+1, word);
        }
    #endif
    cycles-=2;
    return word;
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
/**
* Set byte in memory under given address.
*
* @param address Address in memory to write byte.
* @param Byte Byte to write.
*/
void Processor::Processor::setMemoryByte(const Word &address, const Byte value) {
    memory[address] = value;
}

/**
* Set word in memory under given address and address + 1.
*
* @param address Address in memory to write word.
* @param Byte Word to write.
*/
void Processor::Processor::setMemoryWord(const Word &address, const Word value) {
    memory[address] = (value & 0x00FF);
    memory[address + 1] = (value >> 8);
}

/**
* Push byte to stack
*/
void Processor::Processor::pushByteToStack(Byte value, Dword &cycles, const Dword &requested_cycles, std::string opname) {
    #ifdef DEBUG
        printf("Cycle %i: %s: Current stack pointer pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
    #endif
    setStackPointer(getStackPointer()-1);
    #ifdef DEBUG
        printf("Cycle %i: %s: Stack pointer decremented by 1. Now pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
        printf("Cycle %i: %s: Pushing byte 0x%04X to stack under address 0x%04X\n", requested_cycles-cycles, opname.c_str(), value, getStackPointerMemoryAddress());
    #endif
    Word address = getStackPointerMemoryAddress();
    writeByte(address, value, cycles, requested_cycles, opname);
}

/**
* Pull byte from stack
*/
Processor::Byte Processor::Processor::pullByteFromStack(Dword &cycles, const Dword &requested_cycles, std::string opname) {
    #ifdef DEBUG
        printf("Cycle %i: %s: Current stack pointer pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
    #endif
    Word address = getStackPointerMemoryAddress();
    Byte value = readByte(address, cycles, requested_cycles, opname);
    #ifdef DEBUG
        printf("Cycle %i: %s: Byte pulled from memory address 0x%04X pointed by stack pointer: 0x%04X\n", requested_cycles-cycles, opname.c_str(), address, value);
    #endif
    setStackPointer(getStackPointer()+1);
    #ifdef DEBUG
        printf("Cycle %i: %s: Stack pointer incremented by 1. Now pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
    #endif
    return value;
}

/**
* Push word to stack
*/
void Processor::Processor::pushWordToStack(Word value, Dword &cycles, const Dword &requested_cycles, std::string opname) {
    #ifdef DEBUG
        printf("Cycle %i: %s: Current stack pointer pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
    #endif
    setStackPointer(getStackPointer()-2);
    #ifdef DEBUG
        printf("Cycle %i: %s: Stack pointer decremented by 2. Now pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
        printf("Cycle %i: %s: Pushing word 0x%04X to stack under addresses 0x%04X and 0x%04X\n", requested_cycles-cycles, opname.c_str(), value, getStackPointerMemoryAddress(), getStackPointerMemoryAddress()+1);
    #endif
    Word address = getStackPointerMemoryAddress();
    writeWord(address, value, cycles, requested_cycles, opname);
}

/**
* Pull word from stack
*/
Processor::Word Processor::Processor::pullWordFromStack(Dword &cycles, const Dword &requested_cycles, std::string opname) {
    #ifdef DEBUG
        printf("Cycle %i: %s: Current stack pointer pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
    #endif
    Word address = getStackPointerMemoryAddress();
    Word value = readWord(address, cycles, requested_cycles, opname);
    #ifdef DEBUG
        printf("Cycle %i: %s: Word pulled from memory address 0x%04X (and 0x%04X) pointed by stack pointer: 0x%04X\n", requested_cycles-cycles, opname.c_str(), address, address+1, value);
    #endif
    setStackPointer(getStackPointer()+2);
    #ifdef DEBUG
        printf("Cycle %i: %s: Stack pointer incremented by 2. Now pointing to: 0x%04X\n", requested_cycles-cycles, opname.c_str(), getStackPointerMemoryAddress());
    #endif
    return value;
}

/**
* Write block of instructions to processor memory
*/
void Processor::Processor::writeMemoryBlock(std::string reprString, Word starting_address) {
    std::istringstream iss(reprString);

    std::string byteStr;
    while(iss >> byteStr) {
        try {
            Byte byteValue = std::stoi(byteStr, nullptr, 16);
            setMemoryByte(starting_address, byteValue);
            starting_address++;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid byte: " << byteStr << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Byte out of range: " << byteStr << std::endl;
        }
    }
}

/**
* Get memory bank of address
*/
Processor::MemoryType Processor::Processor::getMemoryBankOfAddress(const Word address) {
    return memory.getMemoryBankOfAddress(address);
}

/**
* Check if cartridge is inserted
*/
bool Processor::Processor::isCartridgeInserted() const {
    return memory.isCartridgeInserted();
}

/**
* Set cartridge inserted or ejected
*/
void Processor::Processor::setCartridgeInserted(bool value) {
    memory.setCartridgeInserted(value);
}
