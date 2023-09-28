#ifndef PROCESSOR_EMULATOR_MEMORY_H
#define PROCESSOR_EMULATOR_MEMORY_H

#include <algorithm>
#include <stdexcept>
#include <cstdint>
#include <list>

#define MAX_MEMORY (1024*64)

namespace Processor {

    typedef uint8_t Byte;
    typedef uint16_t Word;
    typedef uint32_t Dword;

    inline bool inRange(Word, Word, Word);

    class Processor;
    typedef void (Processor::*InstructionFunction)(Dword &, const Dword &);

    enum MemoryType {
        M_UNDEFINED,
        M_RAM_ZEROPAGE,
        M_RAM_STACK,
        M_RAM_OS_AND_BASIC_POINTERS,
        M_RAM_SCREEN_MEMORY,
        M_RAM_FREE_BASIC_PROGRAM_STORAGE_AREA,
        M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_1,
        M_ROM_BASIC_INTERPRETER,
        M_ROM_CARTRIDGE_HIGH,
        M_ROM_KERNEL,
        M_ROM_CHARACTER_GENERATOR,
        M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_2,
        M_RAM_INTERFACE_EXTENSION,
        M_RAM_FREE_MACHINE_LANGUAGE_STORAGE_AREA_3,
        M_IO_CPU_IO_PORT,
        M_IO_VIC_II,
        M_IO_SID,
        M_IO_COLOR,
        M_IO_CIA_1,
        M_IO_CIA_2,
        M_IO_IO_1,
        M_IO_IO_2,
    };

    struct MemorySegment {
        Word start;
        Word end;
        MemoryType type;

        MemorySegment(Word, Word, MemoryType);
        MemoryType getType(const Byte, const bool) const;

    };

    struct Memory {

    private:
        bool bCartridgeInserted = false;
        static std::list<MemorySegment> segments;

    public:
        Byte data[MAX_MEMORY];
        Byte &operator[](Word address);

        void initialize();
        MemoryType getMemoryBankOfAddress(Word);

        bool isCartridgeInserted();
        void setCartridgeInserted(bool);
    };
}

#endif
