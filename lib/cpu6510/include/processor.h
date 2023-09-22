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
        Byte stack_pointer; // Stack Pointer
        Byte processor_status;
        Memory memory;

        std::map<char, Byte> registers = { // Registers
                {'A', 1},
                {'X', 1},
                {'Y', 1}
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

        void INS_INC_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_INC_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_INC_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_INC_ABSOLUTE_X_HANDLE(Dword&, const Dword&);

        void INS_DEC_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_DEC_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_DEC_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_DEC_ABSOLUTE_X_HANDLE(Dword&, const Dword&);

        void INS_INX_HANDLE(Dword&, const Dword&);
        void INS_DEX_HANDLE(Dword&, const Dword&);
        void INS_INY_HANDLE(Dword&, const Dword&);
        void INS_DEY_HANDLE(Dword&, const Dword&);

        void INS_ADC_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_ADC_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_ADC_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_ADC_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_ADC_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_ADC_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_ADC_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_ADC_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);

        void INS_SBC_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_SBC_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_SBC_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_SBC_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_SBC_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_SBC_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_SBC_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_SBC_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);

        void INS_CMP_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_CMP_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_CMP_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_CMP_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_CMP_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_CMP_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_CMP_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_CMP_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);

        void INS_CPX_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_CPX_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_CPX_ABSOLUTE_HANDLE(Dword&, const Dword&);

        void INS_CPY_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_CPY_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_CPY_ABSOLUTE_HANDLE(Dword&, const Dword&);

        void INS_PHA_HANDLE(Dword&, const Dword&);
        void INS_PLA_HANDLE(Dword&, const Dword&);
        void INS_PHP_HANDLE(Dword&, const Dword&);
        void INS_PLP_HANDLE(Dword&, const Dword&);

        void INS_BCC_HANDLE(Dword&, const Dword&);
        void INS_BCS_HANDLE(Dword&, const Dword&);
        void INS_BEQ_HANDLE(Dword&, const Dword&);
        void INS_BMI_HANDLE(Dword&, const Dword&);
        void INS_BNE_HANDLE(Dword&, const Dword&);
        void INS_BPL_HANDLE(Dword&, const Dword&);
        void INS_BVC_HANDLE(Dword&, const Dword&);
        void INS_BVS_HANDLE(Dword&, const Dword&);

        void INS_BIT_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_BIT_ABSOLUTE_HANDLE(Dword&, const Dword&);

        void INS_ANC_IMMEDIATE_ILLEGAL_HANDLE(Dword&, const Dword&);
        void INS_AND_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_AND_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_AND_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_AND_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_AND_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_AND_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_AND_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_AND_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);

        void INS_ORA_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_ORA_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_ORA_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_ORA_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_ORA_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_ORA_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_ORA_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_ORA_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);

        void INS_EOR_IMMEDIATE_HANDLE(Dword&, const Dword&);
        void INS_EOR_ZEROPAGE_HANDLE(Dword&, const Dword&);
        void INS_EOR_ZEROPAGE_X_HANDLE(Dword&, const Dword&);
        void INS_EOR_ABSOLUTE_HANDLE(Dword&, const Dword&);
        void INS_EOR_ABSOLUTE_X_HANDLE(Dword&, const Dword&);
        void INS_EOR_ABSOLUTE_Y_HANDLE(Dword&, const Dword&);
        void INS_EOR_INDEXED_INDIRECT_HANDLE(Dword&, const Dword&);
        void INS_EOR_INDIRECT_INDEXED_HANDLE(Dword&, const Dword&);

        void INS_JSR_HANDLE(Dword&, const Dword&);

    public:
        Processor();
        ~Processor();

        Word getProgramCounter() const;
        Byte getStackPointer() const;
        Word getStackPointerMemoryAddress() const;
        Byte getRegisterValue(const char&) const;
        Byte getProcessorStatusRegister() const;
        Byte getProcessorStatusFlag(const char&) const;
        std::array<Byte, MAX_MEMORY> getMemory() const;

        void setProgramCounter(const Word&, const std::optional<Dword> = std::nullopt, const std::optional<Dword> = std::nullopt, const std::string = "");
        void setStackPointer(const Byte&);
        void setRegisterValue(const char&, const Byte&, const std::optional<Dword> = std::nullopt, const std::optional<Dword> = std::nullopt, const std::string = "");
        void setProcessorStatusRegister(const Byte&);
        void setProcessorStatusFlag(const char&);
        void resetProcessorStatusFlag(const char&);

        void resetCPU();
        Byte fetchByte(Dword &cycles, const Dword &requested_cycles, std::string = "");
        Word fetchWord(Dword&, const Dword&, std::string = "");

        Byte readByte(const Word&, Dword&, const Dword&, std::string = "");
        Word readWord(const Word&, Dword&, const Dword&, std::string = "");
        Byte pullByteFromStack(Dword&, const Dword&, std::string = "");
        Word pullWordFromStack(Dword&, const Dword&, std::string = "");

        void writeWord(const Word&, Word, Dword&, const Dword&, std::string = "");
        void writeByte(const Word&, Byte, Dword&, const Dword&, std::string = "");
        void pushByteToStack(Byte, Dword&, const Dword&, std::string = "");
        void pushWordToStack(Word, Dword&, const Dword&, std::string = "");

        void setMemoryByte(const Word&, const Byte);
        void setMemoryWord(const Word&, const Word);

        void execute(Dword);
    };
}

#endif