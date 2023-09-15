#ifndef PROCESSOR_EMULATOR_PROCESSOR_H
#define PROCESSOR_EMULATOR_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <cstdint>
#include <array>

#include <map>
#include <unordered_map>

#define INS_LDA_IMMEDIATE 0xA9
#define INS_LDA_ABSOLUTE  0xAD
#define INS_LDA_ABSOLUTE_X 0xBD
#define INS_LDA_ABSOLUTE_Y 0xB9
#define INS_LDA_ZEROPAGE 0xA5
#define INS_LDA_ZEROPAGE_X 0xB5
#define INS_LDA_INDEXED_INDIRECT 0xA1
#define INS_LDA_INDIRECT_INDEXED 0xB1
#define INS_JSR 0x20

#define MAX_MEMORY (1024*64)

namespace Processor {

    typedef uint8_t Byte;
    typedef uint16_t Word;
    typedef uint32_t Dword;

    class Processor;
    typedef void (Processor::*InstructionFunction)(Dword&, const Dword&);

    struct Memory {
        Byte data[MAX_MEMORY];
        void initialize();
        Byte& operator [](Word address);
    };

    class Processor {
    private:
        std::unordered_map<Byte, InstructionFunction> instructionMap;

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

        void INS_LDA_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_LDA_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_LDA_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_LDA_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_LDA_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_LDA_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_LDA_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_LDA_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);
        void INS_JSR_HANDLE(Dword&, const Dword&);

    public:
        Processor();
        ~Processor();

        Word getProgramCounter() const;
        Word getStackPointer() const;
        Byte getRegisterValue(const char&) const;
        Byte getProcessorStatus(const char&) const;
        std::array<Byte, MAX_MEMORY> getMemory() const;

        void setProgramCounter(const Word&);
        void setStackPointer(const Word&);
        void setRegisterValue(const char&, const Byte&);
        void setProcessorStatus(const char&, const Byte&);

        void resetCPU();
        Byte fetchByte(Dword &cycles, const Dword &requested_cycles);
        Word fetchWord(Dword&, const Dword&);
        Byte readByte(Byte, Dword&, const Dword&);
        void writeWord(const Word&, Word, Dword&, const Dword&);
        void execute(Dword);

        void setMemoryByte(const Word&, const Byte);
        void setMemoryWord(const Word&, const Word);
    };
}

#endif