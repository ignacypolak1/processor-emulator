#include "memory.h"

/**
* Function checking if given address is in specified range
*/
inline bool Processor::inRange(Word value, Word x, Word y) {
    return value >= x && value <= y;
}

/**
* Memory segment constructor
*/
Processor::MemorySegment::MemorySegment(Word start, Word end, MemoryType type) {
    this->start = start;
    this->end = end;
    this->type = type;
}

/**
* Get type of memory bank, taking into account IO control byte (0x0001)
*/
Processor::MemoryType Processor::MemorySegment::getType(const Byte control, const bool bCartridgeInserted) const {
    if (!(control & 0x04) &&
        (type == M_IO_VIC_II ||
         type == M_IO_SID ||
         type == M_IO_COLOR ||
         type == M_IO_CIA_1 ||
         type == M_IO_CIA_2 ||
         type == M_IO_IO_1 ||
         type == M_IO_IO_2)) {
        return M_ROM_CHARACTER_GENERATOR;
    }

    if (!(control & 0x01) && type == M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_1) {
        return bCartridgeInserted ? M_ROM_CARTRIDGE_HIGH : M_ROM_BASIC_INTERPRETER;
    }

    if (!(control & 0x02) && type == M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_2) {
        return bCartridgeInserted ? M_ROM_CARTRIDGE_HIGH : M_ROM_KERNEL;
    }

    return type;
}

/**
* Get bank of memory, which contains given address
*/
Processor::MemoryType Processor::Memory::getMemoryBankOfAddress(Word address) {
    for(const auto& segment : segments) {
        if(inRange(address, segment.start, segment.end)) {
            return segment.getType(data[0x0001], bCartridgeInserted);
        }
    }
    return M_UNDEFINED;
}

/**
* Static variable of class Memory - list of processor memory mapped segments
*/
std::list<Processor::MemorySegment> Processor::Memory::segments = {
    MemorySegment(0x0000, 0x0001, M_IO_CPU_IO_PORT),
    MemorySegment(0x0000, 0x00FF, M_RAM_ZEROPAGE),
    MemorySegment(0x0100, 0x01FF, M_RAM_STACK),
    MemorySegment(0x0200, 0x03FF, M_RAM_OS_AND_BASIC_POINTERS),
    MemorySegment(0x0400, 0x07FF, M_RAM_SCREEN_MEMORY),
    MemorySegment(0x0800, 0x9FFF, M_RAM_FREE_BASIC_PROGRAM_STORAGE_AREA),
    MemorySegment(0xA000, 0xBFFF, M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_1),
    MemorySegment(0xC000, 0xCFFF, M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_2),

    MemorySegment(0xD000, 0xD3FF, M_IO_VIC_II),
    MemorySegment(0xD400, 0xD7FF, M_IO_SID),
    MemorySegment(0xD800, 0xDBFF, M_IO_COLOR),
    MemorySegment(0xDC00, 0xDCFF, M_IO_CIA_1),
    MemorySegment(0xDD00, 0xDDFF, M_IO_CIA_2),
    MemorySegment(0xDE00, 0xDEFF, M_IO_IO_1),
    MemorySegment(0xDF00, 0xDFFF, M_IO_IO_2),

    MemorySegment(0xE000, 0xFFFF, M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_3),
};


/**
* Initialize of processor memory (fill entire processor memory with 0's).
*/
void Processor::Memory::initialize() {
    std::fill(data, data+MAX_MEMORY, 0x00);
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

/**
* Check if cartridge is inserted
*/
bool Processor::Memory::isCartridgeInserted() const {
    return bCartridgeInserted;
}

/**
* Set cartridge status (function will be replaced with real inserting of virtual cartridges)
*/
void Processor::Memory::setCartridgeInserted(bool val) {
    bCartridgeInserted = val;
}

