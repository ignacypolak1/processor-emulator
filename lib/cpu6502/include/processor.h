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
    public:
        static std::unordered_map<Byte, InstructionFunction> instructionMap;

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