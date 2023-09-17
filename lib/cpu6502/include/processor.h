#ifndef PROCESSOR_EMULATOR_PROCESSOR_H
#define PROCESSOR_EMULATOR_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <cstdint>
#include <array>
#include <string>
#include <optional>

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

#define INS_STA_ABSOLUTE 0x8D
#define INS_STA_ABSOLUTE_X 0x9D
#define INS_STA_ABSOLUTE_Y 0x99
#define INS_STA_ZEROPAGE 0x85
#define INS_STA_ZEROPAGE_X 0x95
#define INS_STA_INDEXED_INDIRECT 0x81
#define INS_STA_INDIRECT_INDEXED 0x91

#define INS_LDX_IMMEDIATE 0xA2
#define INS_LDX_ABSOLUTE 0xAE
#define INS_LDX_ABSOLUTE_Y 0xBE
#define INS_LDX_ZEROPAGE 0xA6
#define INS_LDX_ZEROPAGE_Y 0xB6

#define INS_STX_ABSOLUTE 0x8E
#define INS_STX_ZEROPAGE 0x86
#define INS_STX_ZEROPAGE_Y 0x96

#define INS_LDY_IMMEDIATE 0xA0
#define INS_LDY_ABSOLUTE 0xAC
#define INS_LDY_ABSOLUTE_X 0xBC
#define INS_LDY_ZEROPAGE 0xA4
#define INS_LDY_ZEROPAGE_X 0xB4

#define INS_STY_ABSOLUTE 0x8C
#define INS_STY_ZEROPAGE 0x84
#define INS_STY_ZEROPAGE_X 0x94

#define INS_CLC 0x18
#define INS_CLD 0xD8
#define INS_CLI 0x58
#define INS_CLV 0xB8
#define INS_SEC 0x38
#define INS_SED 0xF8
#define INS_SEI 0x78

#define INS_TAX 0xAA
#define INS_TAY 0xA8
#define INS_TXA 0x8A
#define INS_TYA 0x98
#define INS_TSX 0xBA
#define INS_TXS 0x9A

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

        void INS_STA_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_STA_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_STA_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_STA_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_STA_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_STA_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_STA_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);

        void INS_LDX_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_LDX_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_LDX_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_LDX_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_LDX_ZEROPAGE_Y_HANDLE(Dword&, const Dword&);

        void INS_STX_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_STX_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_STX_ZEROPAGE_Y_HANDLE(Dword&, const Dword&);

        void INS_LDY_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_LDY_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_LDY_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_LDY_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_LDY_ZEROPAGE_X_HANDLE(Dword&, const Dword&);

        void INS_STY_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_STY_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_STY_ZEROPAGE_X_HANDLE(Dword&, const Dword&);

        void INS_CLC_HANDLE(Dword&, const Dword&);
        void INS_CLD_HANDLE(Dword&, const Dword&);
        void INS_CLI_HANDLE(Dword&, const Dword&);
        void INS_CLV_HANDLE(Dword&, const Dword&);
        void INS_SEC_HANDLE(Dword&, const Dword&);
        void INS_SED_HANDLE(Dword&, const Dword&);
        void INS_SEI_HANDLE(Dword&, const Dword&);

        void INS_TAX_HANDLE(Dword&, const Dword&);
        void INS_TAY_HANDLE(Dword&, const Dword&);
        void INS_TXA_HANDLE(Dword&, const Dword&);
        void INS_TYA_HANDLE(Dword&, const Dword&);
        void INS_TSX_HANDLE(Dword&, const Dword&);
        void INS_TXS_HANDLE(Dword&, const Dword&);

        void INS_JSR_HANDLE(Dword&, const Dword&);

    public:
        Processor();
        ~Processor();

        Word getProgramCounter() const;
        Word getStackPointer() const;
        Byte getRegisterValue(const char&) const;
        Byte getProcessorStatus(const char&) const;
        std::array<Byte, MAX_MEMORY> getMemory() const;

        void setProgramCounter(const Word&, const std::optional<Dword> = std::nullopt, const std::optional<Dword> = std::nullopt, const std::string = "");
        void setStackPointer(const Byte&);
        void setRegisterValue(const char&, const Byte&, const std::optional<Dword> = std::nullopt, const std::optional<Dword> = std::nullopt, const std::string = "");
        void setProcessorStatus(const char&, const Byte&);

        void resetCPU();
        Byte fetchByte(Dword &cycles, const Dword &requested_cycles, std::string = "");
        Word fetchWord(Dword&, const Dword&, std::string = "");

        Byte readByte(const Word&, Dword&, const Dword&, std::string = "");
        Word readWord(const Word&, Dword&, const Dword&, std::string = "");

        void writeWord(const Word&, Word, Dword&, const Dword&, std::string = "");
        void writeByte(const Word&, Byte, Dword&, const Dword&, std::string = "");

        void setMemoryByte(const Word&, const Byte);
        void setMemoryWord(const Word&, const Word);

        void execute(Dword);
    };
}

#endif