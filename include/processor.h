#ifndef PROCESSOR_EMULATOR_PROCESSOR_H
#define PROCESSOR_EMULATOR_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <map>
#include <stdexcept>

namespace Processor {

    typedef uint8_t Byte;
    typedef uint16_t Word;
    typedef uint32_t Dword;

    struct Memory {
        static constexpr Dword MAX_MEMORY = 1024 * 64;
        Byte data[MAX_MEMORY];

        void initialize();
        Byte operator [](Dword address) const;
    };

    class Processor {
    private:
        Word program_counter; // Program Counter
        Word stack_pointer; // Stack Pointer
        Memory memory;

        std::map<char, Byte> registers = { // Registers
                {'A', 1},
                {'X', 1},
                {'Y', 1}
        };

        std::map<char, Byte> processor_status = { // Processor Status Register
                {'C', 1},
                {'Z', 1},
                {'I', 1},
                {'D', 1},
                {'B', 1},
                {'V', 1},
                {'N', 1}
        };
    public:
        Processor();
        ~Processor();

        Word getProgramCounter() const;
        Word getStackPointer() const;
        Byte getRegisterValue(const char&) const;
        Byte getProcessorStatus(const char&) const;

        void setProgramCounter(const Word&);
        void setStackPointer(const Word&);
        void setRegisterValue(const char&, const Byte&);
        void setProcessorStatus(const char&, const Byte&);

        void resetCPU();
        Byte fetch(Dword&);
        void execute(Dword);
    };
}

#endif