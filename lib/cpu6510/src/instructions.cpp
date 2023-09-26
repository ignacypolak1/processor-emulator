#include "../include/instructions.h"

#define NEGATIVE_MASK 0x80

std::unordered_map<Processor::Byte, Processor::InstructionFunction> Processor::Processor::instructionMap = {
        {INS_LDA_IMMEDIATE, &Processor::Processor::INS_LDA_IMMEDIATE_HANDLE},
        {INS_LDA_ABSOLUTE, &Processor::Processor::INS_LDA_ABSOLUTE_HANDLE},
        {INS_LDA_ABSOLUTE_X, &Processor::Processor::INS_LDA_ABSOLUTE_X_HANDLE},
        {INS_LDA_ABSOLUTE_Y, &Processor::Processor::INS_LDA_ABSOLUTE_Y_HANDLE},
        {INS_LDA_ZEROPAGE, &Processor::Processor::INS_LDA_ZEROPAGE_HANDLE},
        {INS_LDA_ZEROPAGE_X, &Processor::Processor::INS_LDA_ZEROPAGE_X_HANDLE},
        {INS_LDA_INDEXED_INDIRECT, &Processor::Processor::INS_LDA_INDEXED_INDIRECT_HANDLE},
        {INS_LDA_INDIRECT_INDEXED, &Processor::Processor::INS_LDA_INDIRECT_INDEXED_HANDLE},
        {INS_LDX_IMMEDIATE, &Processor::Processor::INS_LDX_IMMEDIATE_HANDLE},
        {INS_LDX_ABSOLUTE, &Processor::Processor::INS_LDX_ABSOLUTE_HANDLE},
        {INS_LDX_ABSOLUTE_Y, &Processor::Processor::INS_LDX_ABSOLUTE_Y_HANDLE},
        {INS_LDX_ZEROPAGE, &Processor::Processor::INS_LDX_ZEROPAGE_HANDLE},
        {INS_LDX_ZEROPAGE_Y, &Processor::Processor::INS_LDX_ZEROPAGE_Y_HANDLE},
        {INS_LDY_IMMEDIATE, &Processor::Processor::INS_LDY_IMMEDIATE_HANDLE},
        {INS_LDY_ABSOLUTE, &Processor::Processor::INS_LDY_ABSOLUTE_HANDLE},
        {INS_LDY_ABSOLUTE_X, &Processor::Processor::INS_LDY_ABSOLUTE_X_HANDLE},
        {INS_LDY_ZEROPAGE, &Processor::Processor::INS_LDY_ZEROPAGE_HANDLE},
        {INS_LDY_ZEROPAGE_X, &Processor::Processor::INS_LDY_ZEROPAGE_X_HANDLE},
        {INS_STA_ABSOLUTE, &Processor::Processor::INS_STA_ABSOLUTE_HANDLE},
        {INS_STA_ABSOLUTE_X, &Processor::Processor::INS_STA_ABSOLUTE_X_HANDLE},
        {INS_STA_ABSOLUTE_Y, &Processor::Processor::INS_STA_ABSOLUTE_Y_HANDLE},
        {INS_STA_ZEROPAGE, &Processor::Processor::INS_STA_ZEROPAGE_HANDLE},
        {INS_STA_ZEROPAGE_X, &Processor::Processor::INS_STA_ZEROPAGE_X_HANDLE},
        {INS_STA_INDEXED_INDIRECT, &Processor::Processor::INS_STA_INDEXED_INDIRECT_HANDLE},
        {INS_STA_INDIRECT_INDEXED, &Processor::Processor::INS_STA_INDIRECT_INDEXED_HANDLE},
        {INS_STX_ABSOLUTE, &Processor::Processor::INS_STX_ABSOLUTE_HANDLE},
        {INS_STX_ZEROPAGE, &Processor::Processor::INS_STX_ZEROPAGE_HANDLE},
        {INS_STX_ZEROPAGE_Y, &Processor::Processor::INS_STX_ZEROPAGE_Y_HANDLE},
        {INS_STY_ABSOLUTE, &Processor::Processor::INS_STY_ABSOLUTE_HANDLE},
        {INS_STY_ZEROPAGE, &Processor::Processor::INS_STY_ZEROPAGE_HANDLE},
        {INS_STY_ZEROPAGE_X, &Processor::Processor::INS_STY_ZEROPAGE_X_HANDLE},
        {INS_CLC, &Processor::Processor::INS_CLC_HANDLE},
        {INS_CLD, &Processor::Processor::INS_CLD_HANDLE},
        {INS_CLI, &Processor::Processor::INS_CLI_HANDLE},
        {INS_CLV, &Processor::Processor::INS_CLV_HANDLE},
        {INS_SEC, &Processor::Processor::INS_SEC_HANDLE},
        {INS_SED, &Processor::Processor::INS_SED_HANDLE},
        {INS_SEI, &Processor::Processor::INS_SEI_HANDLE},
        {INS_TAX, &Processor::Processor::INS_TAX_HANDLE},
        {INS_TAY, &Processor::Processor::INS_TAY_HANDLE},
        {INS_TXA, &Processor::Processor::INS_TXA_HANDLE},
        {INS_TYA, &Processor::Processor::INS_TYA_HANDLE},
        {INS_TSX, &Processor::Processor::INS_TSX_HANDLE},
        {INS_TXS, &Processor::Processor::INS_TXS_HANDLE},
        {INS_INC_ZEROPAGE, &Processor::Processor::INS_INC_ZEROPAGE_HANDLE},
        {INS_INC_ZEROPAGE_X, &Processor::Processor::INS_INC_ZEROPAGE_X_HANDLE},
        {INS_INC_ABSOLUTE, &Processor::Processor::INS_INC_ABSOLUTE_HANDLE},
        {INS_INC_ABSOLUTE_X, &Processor::Processor::INS_INC_ABSOLUTE_X_HANDLE},
        {INS_DEC_ZEROPAGE, &Processor::Processor::INS_DEC_ZEROPAGE_HANDLE},
        {INS_DEC_ZEROPAGE_X, &Processor::Processor::INS_DEC_ZEROPAGE_X_HANDLE},
        {INS_DEC_ABSOLUTE, &Processor::Processor::INS_DEC_ABSOLUTE_HANDLE},
        {INS_DEC_ABSOLUTE_X, &Processor::Processor::INS_DEC_ABSOLUTE_X_HANDLE},
        {INS_INX, &Processor::Processor::INS_INX_HANDLE},
        {INS_DEX, &Processor::Processor::INS_DEX_HANDLE},
        {INS_INY, &Processor::Processor::INS_INY_HANDLE},
        {INS_DEY, &Processor::Processor::INS_DEY_HANDLE},
        {INS_ADC_IMMEDIATE, &Processor::Processor::INS_ADC_IMMEDIATE_HANDLE},
        {INS_ADC_ZEROPAGE, &Processor::Processor::INS_ADC_ZEROPAGE_HANDLE},
        {INS_ADC_ZEROPAGE_X, &Processor::Processor::INS_ADC_ZEROPAGE_X_HANDLE},
        {INS_ADC_ABSOLUTE, &Processor::Processor::INS_ADC_ABSOLUTE_HANDLE},
        {INS_ADC_ABSOLUTE_X, &Processor::Processor::INS_ADC_ABSOLUTE_X_HANDLE},
        {INS_ADC_ABSOLUTE_Y, &Processor::Processor::INS_ADC_ABSOLUTE_Y_HANDLE},
        {INS_ADC_INDEXED_INDIRECT, &Processor::Processor::INS_ADC_INDEXED_INDIRECT_HANDLE},
        {INS_ADC_INDIRECT_INDEXED, &Processor::Processor::INS_ADC_INDIRECT_INDEXED_HANDLE},
        {INS_SBC_IMMEDIATE, &Processor::Processor::INS_SBC_IMMEDIATE_HANDLE},
        {INS_SBC_ZEROPAGE, &Processor::Processor::INS_SBC_ZEROPAGE_HANDLE},
        {INS_SBC_ZEROPAGE_X, &Processor::Processor::INS_SBC_ZEROPAGE_X_HANDLE},
        {INS_SBC_ABSOLUTE, &Processor::Processor::INS_SBC_ABSOLUTE_HANDLE},
        {INS_SBC_ABSOLUTE_X, &Processor::Processor::INS_SBC_ABSOLUTE_X_HANDLE},
        {INS_SBC_ABSOLUTE_Y, &Processor::Processor::INS_SBC_ABSOLUTE_Y_HANDLE},
        {INS_SBC_INDEXED_INDIRECT, &Processor::Processor::INS_SBC_INDEXED_INDIRECT_HANDLE},
        {INS_SBC_INDIRECT_INDEXED, &Processor::Processor::INS_SBC_INDIRECT_INDEXED_HANDLE},
        {INS_CMP_IMMEDIATE, &Processor::Processor::INS_CMP_IMMEDIATE_HANDLE},
        {INS_CMP_ZEROPAGE, &Processor::Processor::INS_CMP_ZEROPAGE_HANDLE},
        {INS_CMP_ZEROPAGE_X, &Processor::Processor::INS_CMP_ZEROPAGE_X_HANDLE},
        {INS_CMP_ABSOLUTE, &Processor::Processor::INS_CMP_ABSOLUTE_HANDLE},
        {INS_CMP_ABSOLUTE_X, &Processor::Processor::INS_CMP_ABSOLUTE_X_HANDLE},
        {INS_CMP_ABSOLUTE_Y, &Processor::Processor::INS_CMP_ABSOLUTE_Y_HANDLE},
        {INS_CMP_INDEXED_INDIRECT, &Processor::Processor::INS_CMP_INDEXED_INDIRECT_HANDLE},
        {INS_CMP_INDIRECT_INDEXED, &Processor::Processor::INS_CMP_INDIRECT_INDEXED_HANDLE},
        {INS_CPX_IMMEDIATE, &Processor::Processor::INS_CPX_IMMEDIATE_HANDLE},
        {INS_CPX_ZEROPAGE, &Processor::Processor::INS_CPX_ZEROPAGE_HANDLE},
        {INS_CPX_ABSOLUTE, &Processor::Processor::INS_CPX_ABSOLUTE_HANDLE},
        {INS_CPY_IMMEDIATE, &Processor::Processor::INS_CPY_IMMEDIATE_HANDLE},
        {INS_CPY_ZEROPAGE, &Processor::Processor::INS_CPY_ZEROPAGE_HANDLE},
        {INS_CPY_ABSOLUTE, &Processor::Processor::INS_CPY_ABSOLUTE_HANDLE},
        {INS_PHA, &Processor::Processor::INS_PHA_HANDLE},
        {INS_PLA, &Processor::Processor::INS_PLA_HANDLE},
        {INS_PHP, &Processor::Processor::INS_PHP_HANDLE},
        {INS_PLP, &Processor::Processor::INS_PLP_HANDLE},
        {INS_BCC, &Processor::Processor::INS_BCC_HANDLE},
        {INS_BCS, &Processor::Processor::INS_BCS_HANDLE},
        {INS_BEQ, &Processor::Processor::INS_BEQ_HANDLE},
        {INS_BMI, &Processor::Processor::INS_BMI_HANDLE},
        {INS_BNE, &Processor::Processor::INS_BNE_HANDLE},
        {INS_BPL, &Processor::Processor::INS_BPL_HANDLE},
        {INS_BVC, &Processor::Processor::INS_BVC_HANDLE},
        {INS_BVS, &Processor::Processor::INS_BVS_HANDLE},
        {INS_BIT_ZEROPAGE, &Processor::Processor::INS_BIT_ZEROPAGE_HANDLE},
        {INS_BIT_ABSOLUTE, &Processor::Processor::INS_BIT_ABSOLUTE_HANDLE},
        {INS_ANC_IMMEDIATE_ILLEGAL_1, &Processor::Processor::INS_ANC_IMMEDIATE_ILLEGAL_HANDLE},
        {INS_ANC_IMMEDIATE_ILLEGAL_2, &Processor::Processor::INS_ANC_IMMEDIATE_ILLEGAL_HANDLE},
        {INS_AND_IMMEDIATE, &Processor::Processor::INS_AND_IMMEDIATE_HANDLE},
        {INS_AND_ZEROPAGE, &Processor::Processor::INS_AND_ZEROPAGE_HANDLE},
        {INS_AND_ZEROPAGE_X, &Processor::Processor::INS_AND_ZEROPAGE_X_HANDLE},
        {INS_AND_ABSOLUTE, &Processor::Processor::INS_AND_ABSOLUTE_HANDLE},
        {INS_AND_ABSOLUTE_X, &Processor::Processor::INS_AND_ABSOLUTE_X_HANDLE},
        {INS_AND_ABSOLUTE_Y, &Processor::Processor::INS_AND_ABSOLUTE_Y_HANDLE},
        {INS_AND_INDEXED_INDIRECT, &Processor::Processor::INS_AND_INDEXED_INDIRECT_HANDLE},
        {INS_AND_INDIRECT_INDEXED, &Processor::Processor::INS_AND_INDIRECT_INDEXED_HANDLE},
        {INS_ORA_IMMEDIATE, &Processor::Processor::INS_ORA_IMMEDIATE_HANDLE},
        {INS_ORA_ZEROPAGE, &Processor::Processor::INS_ORA_ZEROPAGE_HANDLE},
        {INS_ORA_ZEROPAGE_X, &Processor::Processor::INS_ORA_ZEROPAGE_X_HANDLE},
        {INS_ORA_ABSOLUTE, &Processor::Processor::INS_ORA_ABSOLUTE_HANDLE},
        {INS_ORA_ABSOLUTE_X, &Processor::Processor::INS_ORA_ABSOLUTE_X_HANDLE},
        {INS_ORA_ABSOLUTE_Y, &Processor::Processor::INS_ORA_ABSOLUTE_Y_HANDLE},
        {INS_ORA_INDEXED_INDIRECT, &Processor::Processor::INS_ORA_INDEXED_INDIRECT_HANDLE},
        {INS_ORA_INDIRECT_INDEXED, &Processor::Processor::INS_ORA_INDIRECT_INDEXED_HANDLE},
        {INS_EOR_IMMEDIATE, &Processor::Processor::INS_EOR_IMMEDIATE_HANDLE},
        {INS_EOR_ZEROPAGE, &Processor::Processor::INS_EOR_ZEROPAGE_HANDLE},
        {INS_EOR_ZEROPAGE_X, &Processor::Processor::INS_EOR_ZEROPAGE_X_HANDLE},
        {INS_EOR_ABSOLUTE, &Processor::Processor::INS_EOR_ABSOLUTE_HANDLE},
        {INS_EOR_ABSOLUTE_X, &Processor::Processor::INS_EOR_ABSOLUTE_X_HANDLE},
        {INS_EOR_ABSOLUTE_Y, &Processor::Processor::INS_EOR_ABSOLUTE_Y_HANDLE},
        {INS_EOR_INDEXED_INDIRECT, &Processor::Processor::INS_EOR_INDEXED_INDIRECT_HANDLE},
        {INS_EOR_INDIRECT_INDEXED, &Processor::Processor::INS_EOR_INDIRECT_INDEXED_HANDLE},
        {INS_ROL_ACCUMULATOR, &Processor::Processor::INS_ROL_ACCUMULATOR_HANDLE},
        {INS_ROL_ABSOLUTE, &Processor::Processor::INS_ROL_ABSOLUTE_HANDLE},
        {INS_ROL_ABSOLUTE_X, &Processor::Processor::INS_ROL_ABSOLUTE_X_HANDLE},
        {INS_ROL_ZEROPAGE, &Processor::Processor::INS_ROL_ZEROPAGE_HANDLE},
        {INS_ROL_ZEROPAGE_X, &Processor::Processor::INS_ROL_ZEROPAGE_X_HANDLE},
        {INS_ROR_ACCUMULATOR, &Processor::Processor::INS_ROR_ACCUMULATOR_HANDLE},
        {INS_ROR_ABSOLUTE, &Processor::Processor::INS_ROR_ABSOLUTE_HANDLE},
        {INS_ROR_ABSOLUTE_X, &Processor::Processor::INS_ROR_ABSOLUTE_X_HANDLE},
        {INS_ROR_ZEROPAGE, &Processor::Processor::INS_ROR_ZEROPAGE_HANDLE},
        {INS_ROR_ZEROPAGE_X, &Processor::Processor::INS_ROR_ZEROPAGE_X_HANDLE},
        {INS_JMP_ABSOLUTE, &Processor::Processor::INS_JMP_ABSOLUTE_HANDLE},
        {INS_JMP_INDIRECT, &Processor::Processor::INS_JMP_INDIRECT_HANDLE},
        {INS_JSR, &Processor::Processor::INS_JSR_HANDLE},
        {INS_RTS, &Processor::Processor::INS_RTS_HANDLE},
        {INS_RTI, &Processor::Processor::INS_RTI_HANDLE},
};

void set_flags_NZ(Processor::Processor *processor, Processor::Byte value, Processor::Dword &cycles, const Processor::Dword &requested_cycles, const std::string opname) {

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: %s: Setting Zero Flag\n", requested_cycles-cycles, opname.c_str());
        #endif
        processor->setProcessorStatusFlag('Z');
        #ifdef DEBUG
                printf("Cycle %i: %s: Resetting Negative Flag\n", requested_cycles-cycles, opname.c_str());
        #endif
        processor->resetProcessorStatusFlag('N');
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: %s: Resetting Zero Flag\n", requested_cycles-cycles, opname.c_str());
        #endif
        processor->resetProcessorStatusFlag('Z');

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: %s: Setting Negative Flag\n", requested_cycles-cycles, opname.c_str());
            #endif
            processor->setProcessorStatusFlag('N');
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: %s: Resetting Negative Flag\n", requested_cycles-cycles, opname.c_str());
            #endif
            processor->resetProcessorStatusFlag('N');
        }
    }
}

void set_flags_C(Processor::Processor *processor, Processor::Byte value, Processor::Byte anotherValue, Processor::Byte mode, Processor::Dword &cycles, const Processor::Dword &requested_cycles, const std::string opname) {
    Processor::Word result;

    switch (mode) {
        case 0x00: {
            result = value + anotherValue;
            if (result > 0xFF) {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Setting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->setProcessorStatusFlag('C');
            } else {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Resseting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->resetProcessorStatusFlag('C');
            }
            break;
        }
        case 0x01: {
            if (value >= anotherValue) {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Setting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->setProcessorStatusFlag('C');
            } else {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Resseting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->resetProcessorStatusFlag('C');
            }
            break;
        }
        case 0x02: {
            if(value & 0x80) {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Setting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->setProcessorStatusFlag('C');
            }
            else {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Resseting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->resetProcessorStatusFlag('C');
            }
            break;
        }
        case 0x03: {
            if(value & 0x01) {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Setting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->setProcessorStatusFlag('C');
            }
            else {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Resseting Carry Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->resetProcessorStatusFlag('C');
            }
            break;
        }
    }
}

void set_flags_V(Processor::Processor *processor, Processor::Byte value, Processor::Byte anotherValue, Processor::Byte mode, Processor::Dword &cycles, const Processor::Dword &requested_cycles, const std::string opname) {
    bool bValuePositive = (value & 0x80) == 0;
    bool bAnotherValuePositive = (anotherValue & 0x80) == 0;
    bool bResultPositive;

    switch (mode) {
        case 0x00: {
            bResultPositive = ((value + anotherValue) & 0x80) == 0;
            if (bValuePositive && bAnotherValuePositive && !bResultPositive) {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Setting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->setProcessorStatusFlag('V');
            } else if (!bValuePositive && !bAnotherValuePositive && bResultPositive) {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Setting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->setProcessorStatusFlag('V');
            } else {
                #ifdef DEBUG
                    printf("Cycle %i: %s: Resetting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                #endif
                processor->resetProcessorStatusFlag('V');
            }
            break;
        }
        case 0x01: {
            {
                bResultPositive = ((value - anotherValue) & 0x80) == 0;
                if (bValuePositive && !bAnotherValuePositive && !bResultPositive) {
                    #ifdef DEBUG
                        printf("Cycle %i: %s: Setting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                    #endif
                    processor->setProcessorStatusFlag('V');
                } else if (!bValuePositive && bAnotherValuePositive && bResultPositive) {
                    #ifdef DEBUG
                        printf("Cycle %i: %s: Setting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                    #endif
                    processor->setProcessorStatusFlag('V');
                } else {
                    #ifdef DEBUG
                        printf("Cycle %i: %s: Resetting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                    #endif
                    processor->resetProcessorStatusFlag('V');
                }
                break;
            }
        }
        case 0x02: {
            {
                if(value & 0x40) {
                    #ifdef DEBUG
                        printf("Cycle %i: %s: Setting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                    #endif
                    processor->setProcessorStatusFlag('V');
                }
                else {
                    #ifdef DEBUG
                        printf("Cycle %i: %s: Resetting Overflow Flag\n", requested_cycles - cycles, opname.c_str());
                    #endif
                    processor->resetProcessorStatusFlag('V');
                }
                break;
            }
        }
    }
}



bool bAddressesOnDifferentPages(Processor::Word address_1, Processor::Word address_2) {
    if(int(address_1 / 256) != int(address_2 / 256)) {
        return true;
    } else {
        return false;
    }
}

void Processor::Processor::INS_LDA_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_LDA_IMMEDIATE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_IMMEDIATE");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_IMMEDIATE");
}
void Processor::Processor::INS_LDA_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDA_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDA_ABSOLUTE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_ABSOLUTE");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ABSOLUTE");
}

void Processor::Processor::INS_LDA_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, address+regXValue)) {
        cycles--;
    }

    Byte value = readByte(address + regXValue, cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
}
void Processor::Processor::INS_LDA_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }

    Byte value = readByte(address + regYValue, cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
}

void Processor::Processor::INS_LDA_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDA_ZEROPAGE");

    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_ZEROPAGE");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ZEROPAGE");
}
void Processor::Processor::INS_LDA_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    cycles--;

    address = (address + regXValue) % 256;
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");

    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");
}

void Processor::Processor::INS_LDA_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");

    cycles--; // Dummy cycle

    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
}

void Processor::Processor::INS_LDA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");
    Byte regYValue = getRegisterValue('Y');

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");

    if(bAddressesOnDifferentPages(valueAddress, valueAddress+regYValue)) {
        cycles--;
    }
    valueAddress = (valueAddress + regYValue) % 65536;
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");

    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");
}

void Processor::Processor::INS_LDX_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_LDX_IMMEDIATE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDX_IMMEDIATE");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_IMMEDIATE");
}
void Processor::Processor::INS_LDX_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDX_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDX_ABSOLUTE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDX_ABSOLUTE");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ABSOLUTE");
}
void Processor::Processor::INS_LDX_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }

    Byte value = readByte(address + regYValue, cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
}
void Processor::Processor::INS_LDX_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDX_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDX_ZEROPAGE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDX_ZEROPAGE");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ZEROPAGE");
}
void Processor::Processor::INS_LDX_ZEROPAGE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    Byte regYVal = getRegisterValue('Y');

    address = (address + regYVal) % 256;
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    cycles--;

    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
}

void Processor::Processor::INS_LDY_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_LDY_IMMEDIATE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDY_IMMEDIATE");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_IMMEDIATE");
}
void Processor::Processor::INS_LDY_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDY_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDY_ABSOLUTE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDY_ABSOLUTE");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_ABSOLUTE");
}
void Processor::Processor::INS_LDY_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, address+regXValue)) {
        cycles--;
    }

    Byte value = readByte(address + regXValue, cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
}
void Processor::Processor::INS_LDY_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDY_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDY_ZEROPAGE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDY_ZEROPAGE");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_ZEROPAGE");
}
void Processor::Processor::INS_LDY_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDY_ZEROPAGE_X");
    Byte regXVal = getRegisterValue('X');

    address = (address + regXVal) % 256;
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDY_ZEROPAGE_X");
    cycles--;

    set_flags_NZ(this, value, cycles, requested_cycles, "INS_LDY_ZEROPAGE_X");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_ZEROPAGE_X");
}

void Processor::Processor::INS_STA_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_STA_ABSOLUTE");
    Byte regAValue = getRegisterValue('A');
    writeByte(address, regAValue, cycles, requested_cycles, "INS_STA_ABSOLUTE");
}

void Processor::Processor::INS_STA_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_STA_ABSOLUTE_X");
    Byte regAValue = getRegisterValue('A');
    Byte regXValue = getRegisterValue('X');
    cycles--;
    writeByte(address+regXValue, regAValue, cycles, requested_cycles, "INS_STA_ABSOLUTE_X");
}

void Processor::Processor::INS_STA_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_STA_ABSOLUTE_Y");
    Byte regAValue = getRegisterValue('A');
    Byte regYValue = getRegisterValue('Y');
    cycles--;
    writeByte(address+regYValue, regAValue, cycles, requested_cycles, "INS_STA_ABSOLUTE_Y");
}

void Processor::Processor::INS_STA_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STA_ZEROPAGE");
    Byte regAValue = getRegisterValue('A');
    writeByte(address, regAValue, cycles, requested_cycles, "INS_STA_ZEROPAGE");
}

void Processor::Processor::INS_STA_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STA_ZEROPAGE_X");
    Byte regAValue = getRegisterValue('A');
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    cycles--;
    writeByte(address, regAValue, cycles, requested_cycles, "INS_STA_ZEROPAGE_X");
}

void Processor::Processor::INS_STA_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STA_INDEXED_INDIRECT");
    Byte regAValue = getRegisterValue('A');
    Byte regXValue = getRegisterValue('X');
    cycles--;

    address = (address + regXValue) % 256;

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_STA_INDEXED_INDIRECT");
    writeByte(valueAddress, regAValue, cycles, requested_cycles, "INS_STA_INDEXED_INDIRECT");
}

void Processor::Processor::INS_STA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STA_INDIRECT_INDEXED");
    Byte regAValue = getRegisterValue('A');
    Byte regYValue = getRegisterValue('Y');

    cycles--;

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_STA_INDIRECT_INDEXED");
    if(bAddressesOnDifferentPages(valueAddress, valueAddress+regYValue)) {
        cycles--;
    }
    valueAddress = (valueAddress + regYValue) % 65536;

    writeByte(valueAddress, regAValue, cycles, requested_cycles, "INS_STA_INDIRECT_INDEXED");
}

void Processor::Processor::INS_STX_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_STX_ABSOLUTE");
    Byte value = getRegisterValue('X');
    writeByte(address, value, cycles, requested_cycles, "INS_STX_ABSOLUTE");
}

void Processor::Processor::INS_STX_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STX_ZEROPAGE");
    Byte value = getRegisterValue('X');
    writeByte(address, value, cycles, requested_cycles, "INS_STX_ZEROPAGE");
}

void Processor::Processor::INS_STX_ZEROPAGE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STX_ZEROPAGE_Y");
    Byte value = getRegisterValue('X');
    Byte regYValue = getRegisterValue('Y');

    address = (address + regYValue) % 256;
    cycles--;
    writeByte(address, value, cycles, requested_cycles, "INS_STX_ZEROPAGE_Y");
}

void Processor::Processor::INS_STY_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_STX_ABSOLUTE");
    Byte value = getRegisterValue('Y');
    writeByte(address, value, cycles, requested_cycles, "INS_STX_ABSOLUTE");
}

void Processor::Processor::INS_STY_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STX_ZEROPAGE");
    Byte value = getRegisterValue('Y');
    writeByte(address, value, cycles, requested_cycles, "INS_STX_ZEROPAGE");
}

void Processor::Processor::INS_STY_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_STX_ZEROPAGE_Y");
    Byte value = getRegisterValue('Y');
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    cycles--;
    writeByte(address, value, cycles, requested_cycles, "INS_STX_ZEROPAGE_Y");
}

void Processor::Processor::INS_CLC_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    resetProcessorStatusFlag('C');
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Carry Flag\n", requested_cycles-cycles, "INS_CLC");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_CLD_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    resetProcessorStatusFlag('D');
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Decimal Flag\n", requested_cycles-cycles, "INS_CLD");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_CLI_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    resetProcessorStatusFlag('I');
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Interrupt Flag\n", requested_cycles-cycles, "INS_CLI");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_CLV_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    resetProcessorStatusFlag('V');
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Overflow Flag\n", requested_cycles-cycles, "INS_CLV");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_SEC_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatusFlag('C');
    #ifdef DEBUG
        printf("Cycle %i: %s: Setting Carry Flag\n", requested_cycles-cycles, "INS_SEC");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_SED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatusFlag('D');
    #ifdef DEBUG
        printf("Cycle %i: %s: Setting Decimal Flag\n", requested_cycles-cycles, "INS_SED");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_SEI_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatusFlag('I');
    #ifdef DEBUG
        printf("Cycle %i: %s: Setting Interrupt Flag\n", requested_cycles-cycles, "INS_SEI");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_TAX_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regAValue = getRegisterValue('A');
    setRegisterValue('X', regAValue, cycles, requested_cycles, "INS_TAX");
    cycles--;
    set_flags_NZ(this, regAValue, cycles, requested_cycles, "INS_TAX");
}

void Processor::Processor::INS_TAY_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regAValue = getRegisterValue('A');
    setRegisterValue('Y', regAValue, cycles, requested_cycles, "INS_TAY");
    cycles--;
    set_flags_NZ(this, regAValue, cycles, requested_cycles, "INS_TAY");
}

void Processor::Processor::INS_TXA_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regXValue = getRegisterValue('X');
    setRegisterValue('A', regXValue, cycles, requested_cycles, "INS_TXA");
    cycles--;
    set_flags_NZ(this, regXValue, cycles, requested_cycles, "INS_TXA");
}

void Processor::Processor::INS_TYA_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regYValue = getRegisterValue('Y');
    setRegisterValue('A', regYValue, cycles, requested_cycles, "INS_TYA");
    cycles--;
    set_flags_NZ(this, regYValue, cycles, requested_cycles, "INS_TYA");
}

void Processor::Processor::INS_TSX_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte stackValue = getStackPointer();
    setRegisterValue('X', stackValue, cycles, requested_cycles, "INS_TSX");
    cycles--;
    set_flags_NZ(this, stackValue, cycles, requested_cycles, "INS_TSX");
}

void Processor::Processor::INS_TXS_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regXValue = getRegisterValue('X');
    setStackPointer(regXValue);
    cycles--;
}

void Processor::Processor::INS_INC_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_INC_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_INC_ZEROPAGE");
    cycles--;
    value++;
    writeByte(address, value, cycles, requested_cycles, "INS_INC_ZEROPAGE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_INC_ZEROPAGE");
}

void Processor::Processor::INS_INC_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    cycles-=2;

    Byte value = readByte(address, cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
    value++;
    writeByte(address, value, cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
}

void Processor::Processor::INS_INC_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_INC_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_INC_ABSOLUTE");
    cycles--;
    value++;
    writeByte(address, value, cycles, requested_cycles, "INS_INC_ABSOLUTE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_INC_ABSOLUTE");
}

void Processor::Processor::INS_INC_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 65536;
    cycles-=2;

    Byte value = readByte(address, cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
    value++;
    writeByte(address, value, cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
}

void Processor::Processor::INS_DEC_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_DEC_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ZEROPAGE");
    cycles--;
    value--;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE");
}

void Processor::Processor::INS_DEC_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    cycles-=2;

    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
    value--;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
}

void Processor::Processor::INS_DEC_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_DEC_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ABSOLUTE");
    value--;
    cycles-=1;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE");
}

void Processor::Processor::INS_DEC_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 65536;
    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
    value--;
    cycles-=2;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
    set_flags_NZ(this, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
}

void Processor::Processor::INS_INX_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regXValue = getRegisterValue('X');
    regXValue++;
    cycles--;
    setRegisterValue('X', regXValue, cycles, requested_cycles, "INS_INX");
    set_flags_NZ(this, regXValue, cycles, requested_cycles, "INS_INX");
}

void Processor::Processor::INS_DEX_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regXValue = getRegisterValue('X');
    regXValue--;
    cycles--;
    setRegisterValue('X', regXValue, cycles, requested_cycles, "INS_DEX");
    set_flags_NZ(this, regXValue, cycles, requested_cycles, "INS_DEX");
}

void Processor::Processor::INS_INY_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regYValue = getRegisterValue('Y');
    regYValue++;
    cycles--;
    setRegisterValue('Y', regYValue, cycles, requested_cycles, "INS_INY");
    set_flags_NZ(this, regYValue, cycles, requested_cycles, "INS_INY");
}

void Processor::Processor::INS_DEY_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regYValue = getRegisterValue('Y');
    regYValue--;
    cycles--;
    setRegisterValue('Y', regYValue, cycles, requested_cycles, "INS_DEY");
    set_flags_NZ(this, regYValue, cycles, requested_cycles, "INS_DEY");
}

void Processor::Processor::INS_ADC_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_ADC_IMMEDIATE");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_IMMEDIATE");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_IMMEDIATE");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_IMMEDIATE");
}

void Processor::Processor::INS_ADC_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ADC_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ADC_ZEROPAGE");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_ZEROPAGE");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ZEROPAGE");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ZEROPAGE");
}

void Processor::Processor::INS_ADC_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ADC_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ADC_ZEROPAGE_X");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;
    cycles--;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_ZEROPAGE_X");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ZEROPAGE_X");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ZEROPAGE_X");
}

void Processor::Processor::INS_ADC_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ADC_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ADC_ABSOLUTE");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_ABSOLUTE");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ABSOLUTE");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ABSOLUTE");
}

void Processor::Processor::INS_ADC_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ADC_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, address+regXValue)) {
        cycles--;
    }

    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ADC_ABSOLUTE_X");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_ABSOLUTE_X");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ABSOLUTE_X");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ABSOLUTE_X");
}

void Processor::Processor::INS_ADC_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ADC_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }

    address = (address + regYValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ADC_ABSOLUTE_Y");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_ABSOLUTE_Y");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ABSOLUTE_Y");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_ABSOLUTE_Y");
}

void Processor::Processor::INS_ADC_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ADC_INDEXED_INDIRECT");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_ADC_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_ADC_INDEXED_INDIRECT");

    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;
    cycles--;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_INDEXED_INDIRECT");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_INDEXED_INDIRECT");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_INDEXED_INDIRECT");
}

void Processor::Processor::INS_ADC_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ADC_INDIRECT_INDEXED");
    Byte regYValue = getRegisterValue('Y');
    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_ADC_INDIRECT_INDEXED");

    if(bAddressesOnDifferentPages(valueAddress, address+regYValue)) {
        cycles--;
    }

    valueAddress = (valueAddress + regYValue) % 65536;

    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_ADC_INDIRECT_INDEXED");

    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + value + carry;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_ADC_INDIRECT_INDEXED");
        set_flags_V(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_INDIRECT_INDEXED");
    }
    set_flags_C(this, regAValue + carry, value, 0x00, cycles, requested_cycles, "INS_ADC_INDIRECT_INDEXED");
}

void Processor::Processor::INS_SBC_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_SBC_IMMEDIATE");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_IMMEDIATE");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_IMMEDIATE");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_INDIRECT_INDEXED");
}

void Processor::Processor::INS_SBC_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_SBC_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_SBC_ZEROPAGE");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_ZEROPAGE");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ZEROPAGE");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ZEROPAGE");
}

void Processor::Processor::INS_SBC_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_SBC_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;

    Byte value = readByte(address, cycles, requested_cycles, "INS_SBC_ZEROPAGE_X");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);
    cycles--;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_ZEROPAGE_X");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ZEROPAGE_X");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ZEROPAGE_X");

}

void Processor::Processor::INS_SBC_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_SBC_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_SBC_ABSOLUTE");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_ABSOLUTE");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ABSOLUTE");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ABSOLUTE");

}

void Processor::Processor::INS_SBC_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_SBC_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, address+regXValue)) {
        cycles--;
    }

    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_SBC_ABSOLUTE_X");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_ABSOLUTE_X");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ABSOLUTE_X");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ABSOLUTE_X");

}

void Processor::Processor::INS_SBC_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_SBC_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }

    address = (address + regYValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_SBC_ABSOLUTE_Y");
    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_ABSOLUTE_Y");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ABSOLUTE_Y");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_ABSOLUTE_Y");
}

void Processor::Processor::INS_SBC_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_SBC_INDEXED_INDIRECT");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_SBC_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_SBC_INDEXED_INDIRECT");

    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);
    cycles--;

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_INDEXED_INDIRECT");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_INDEXED_INDIRECT");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_INDEXED_INDIRECT");
}

void Processor::Processor::INS_SBC_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_SBC_INDIRECT_INDEXED");
    Byte regYValue = getRegisterValue('Y');
    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_SBC_INDIRECT_INDEXED");

    if(bAddressesOnDifferentPages(valueAddress, valueAddress+regYValue)) {
        cycles--;
    }

    valueAddress = (valueAddress + regYValue) % 65536;

    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_SBC_INDIRECT_INDEXED");

    Byte regAValue = getRegisterValue('A');
    Byte carry = getProcessorStatusFlag('C');

    Byte result = regAValue + (~value) + 1 - (1-carry);

    setRegisterValue('A', result);

    if(!getProcessorStatusFlag('D')) {
        set_flags_NZ(this, result, cycles, requested_cycles, "INS_SBC_INDIRECT_INDEXED");
        set_flags_V(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_INDIRECT_INDEXED");
    }
    set_flags_C(this, regAValue - carry, value, 0x01, cycles, requested_cycles, "INS_SBC_INDIRECT_INDEXED");
}

void Processor::Processor::INS_CMP_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_CMP_IMMEDIATE");
    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_IMMEDIATE");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_IMMEDIATE");
}

void Processor::Processor::INS_CMP_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_CMP_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_CMP_ZEROPAGE");

    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_ZEROPAGE");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_ZEROPAGE");
}

void Processor::Processor::INS_CMP_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_CMP_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;

    Byte value = readByte(address, cycles, requested_cycles, "INS_CMP_ZEROPAGE_X");

    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;
    cycles--;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_ZEROPAGE_X");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_ZEROPAGE_X");
}

void Processor::Processor::INS_CMP_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_CMP_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_CMP_ABSOLUTE");

    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_ABSOLUTE");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_ABSOLUTE");
}

void Processor::Processor::INS_CMP_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_CMP_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, address+regXValue)) {
        cycles--;
    }
    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_CMP_ABSOLUTE_X");
    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_ABSOLUTE_X");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_ABSOLUTE_X");
}

void Processor::Processor::INS_CMP_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_CMP_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }
    address = (address + regYValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_CMP_ABSOLUTE_Y");
    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_ABSOLUTE_X");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_ABSOLUTE_X");
}

void Processor::Processor::INS_CMP_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_CMP_INDEXED_INDIRECT");
    Byte regYValue = getRegisterValue('X');

    address = (address + regYValue) % 256;

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_CMP_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_CMP_INDEXED_INDIRECT");
    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;
    cycles--;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_INDEXED_INDIRECT");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_INDEXED_INDIRECT");
}

void Processor::Processor::INS_CMP_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_CMP_INDIRECT_INDEXED");
    Byte regYValue = getRegisterValue('Y');

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_CMP_INDIRECT_INDEXED");

    if(bAddressesOnDifferentPages(valueAddress, valueAddress+regYValue)) {
        cycles--;
    }
    valueAddress = (valueAddress + regYValue) % 65536;

    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_CMP_INDIRECT_INDEXED");
    Byte regAValue = getRegisterValue('A');

    Byte result = regAValue + (~value) + 1;
    cycles--;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CMP_INDIRECT_INDEXED");
    set_flags_C(this, regAValue, value, 0x01, cycles, requested_cycles, "INS_CMP_INDIRECT_INDEXED");
}

void Processor::Processor::INS_CPX_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_CPX_IMMEDIATE");
    Byte regXValue = getRegisterValue('X');

    Byte result = regXValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CPX_IMMEDIATE");
    set_flags_C(this, regXValue, value, 0x01, cycles, requested_cycles, "INS_CPX_IMMEDIATE");
}

void Processor::Processor::INS_CPX_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_CPX_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_CPX_ZEROPAGE");

    Byte regXValue = getRegisterValue('X');

    Byte result = regXValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CPX_ZEROPAGE");
    set_flags_C(this, regXValue, value, 0x01, cycles, requested_cycles, "INS_CPX_ZEROPAGE");
}

void Processor::Processor::INS_CPX_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_CPX_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_CPX_ABSOLUTE");

    Byte regXValue = getRegisterValue('X');

    Byte result = regXValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CPX_ABSOLUTE");
    set_flags_C(this, regXValue, value, 0x01, cycles, requested_cycles, "INS_CPX_ABSOLUTE");
}

void Processor::Processor::INS_CPY_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_CPY_IMMEDIATE");
    Byte regYValue = getRegisterValue('Y');

    Byte result = regYValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CPY_IMMEDIATE");
    set_flags_C(this, regYValue, value, 0x01, cycles, requested_cycles, "INS_CPY_IMMEDIATE");
}
void Processor::Processor::INS_CPY_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_CPY_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_CPY_ZEROPAGE");

    Byte regYValue = getRegisterValue('Y');

    Byte result = regYValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CPY_ZEROPAGE");
    set_flags_C(this, regYValue, value, 0x01, cycles, requested_cycles, "INS_CPY_ZEROPAGE");
}
void Processor::Processor::INS_CPY_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_CPY_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_CPY_ABSOLUTE");

    Byte regYValue = getRegisterValue('Y');

    Byte result = regYValue + (~value) + 1;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_CPY_ABSOLUTE");
    set_flags_C(this, regYValue, value, 0x01, cycles, requested_cycles, "INS_CPY_ABSOLUTE");
}


void Processor::Processor::INS_PHA_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regAvalue = getRegisterValue('A');
    pushByteToStack(regAvalue, cycles, requested_cycles, "INS_PHA");
    cycles--;
}

void Processor::Processor::INS_PLA_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = pullByteFromStack(cycles, requested_cycles, "INS_PLA");
    setRegisterValue('A', value);
    cycles-=2;
}

void Processor::Processor::INS_PHP_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regStatusValue = getProcessorStatusRegister();
    pushByteToStack(regStatusValue, cycles, requested_cycles, "INS_PHP");
    cycles--;
}

void Processor::Processor::INS_PLP_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = pullByteFromStack(cycles, requested_cycles, "INS_PLP");
    setProcessorStatusRegister(value);
    cycles-=2;
}

void Processor::Processor::INS_BCC_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte C = getProcessorStatusFlag('C');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BCC");
    Word pc = getProgramCounter();

    if(!C) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BCC");
        cycles--;
    }
    else {
        cycles--;
    }
}
void Processor::Processor::INS_BCS_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte C = getProcessorStatusFlag('C');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BCS");
    Word pc = getProgramCounter();

    if(C) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BCS");
        cycles--;
    }
    else {
        cycles--;
    }
}
void Processor::Processor::INS_BEQ_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte Z = getProcessorStatusFlag('Z');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BEQ");
    Word pc = getProgramCounter();

    if(Z) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BEQ");
        cycles--;
    }
    else {
        cycles--;
    }
}
void Processor::Processor::INS_BMI_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte N = getProcessorStatusFlag('N');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BMI");
    Word pc = getProgramCounter();

    if(N) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BMI");
        cycles--;
    }
    else {
        cycles--;
    }
}
void Processor::Processor::INS_BNE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte Z = getProcessorStatusFlag('Z');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BNE");
    Word pc = getProgramCounter();

    if(!Z) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BNE");
        cycles--;
    }
    else {
        cycles--;
    }
}
void Processor::Processor::INS_BPL_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte N = getProcessorStatusFlag('N');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BPL");
    Word pc = getProgramCounter();

    if(!N) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BPL");
        cycles--;
    }
    else {
        cycles--;
    }
}
void Processor::Processor::INS_BVC_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte V = getProcessorStatusFlag('V');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BVC");
    Word pc = getProgramCounter();

    if(!V) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BVC");
        cycles--;
    }
    else {
        cycles--;
    }
}
void Processor::Processor::INS_BVS_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte V = getProcessorStatusFlag('V');
    int8_t value = fetchByte(cycles, requested_cycles, "INS_BVS");
    Word pc = getProgramCounter();

    if(V) {
        if(bAddressesOnDifferentPages(pc, pc+value)) {
            cycles--;
        }
        pc = (pc + value) % 65536;
        setProgramCounter(pc, cycles, requested_cycles, "INS_BVS");
        cycles--;
    }
    else {
        cycles--;
    }
}

void Processor::Processor::INS_BIT_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_BIT_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_BIT_ZEROPAGE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_BIT_ZEROPAGE");
    set_flags_V(this, result, 0, 0x02, cycles, requested_cycles, "INS_BIT_ZEROPAGE");
}
void Processor::Processor::INS_BIT_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_BIT_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_BIT_ABSOLUTE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_BIT_ABSOLUTE");
    set_flags_V(this, result, 0, 0x02, cycles, requested_cycles, "INS_BIT_ABSOLUTE");
}

void Processor::Processor::INS_ANC_IMMEDIATE_ILLEGAL_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_ANC_IMMEDIATE_ILLEGAL");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ANC_IMMEDIATE_ILLEGAL");
    if(getProcessorStatusFlag('N'))
    {
        setProcessorStatusFlag('C');
    }
    else {
        resetProcessorStatusFlag('C');
    }
}

void Processor::Processor::INS_AND_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_AND_IMMEDIATE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_IMMEDIATE");
}

void Processor::Processor::INS_AND_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_AND_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_AND_ZEROPAGE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_ZEROPAGE");
}

void Processor::Processor::INS_AND_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_AND_ZEROPAGE_X");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Byte value = readByte(address, cycles, requested_cycles, "INS_AND_ZEROPAGE_X");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    cycles--;

    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_ZEROPAGE_X");
}

void Processor::Processor::INS_AND_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_AND_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_AND_ABSOLUTE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_ABSOLUTE");
}

void Processor::Processor::INS_AND_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_AND_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, (address+regXValue) % 65536)) {
        cycles--;
    }
    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_AND_ABSOLUTE_X");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_ABSOLUTE_X");
}

void Processor::Processor::INS_AND_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_AND_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, (address+regYValue) % 65536)) {
        cycles--;
    }
    address = (address + regYValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_AND_ABSOLUTE_Y");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_ABSOLUTE_Y");
}

void Processor::Processor::INS_AND_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");

    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    cycles--;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");
}

void Processor::Processor::INS_AND_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");

    Byte regYValue = getRegisterValue('Y');
    valueAddress = (valueAddress + regYValue) % 65536;

    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");

    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue & value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_AND_INDEXED_INDIRECT");
}

void Processor::Processor::INS_ORA_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_ORA_IMMEDIATE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_IMMEDIATE");
}
void Processor::Processor::INS_ORA_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ORA_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ORA_ZEROPAGE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_ZEROPAGE");
}

void Processor::Processor::INS_ORA_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ORA_ZEROPAGE_X");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ORA_ZEROPAGE_X");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    cycles--;

    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_ZEROPAGE_X");
}

void Processor::Processor::INS_ORA_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ORA_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ORA_ABSOLUTE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_ABSOLUTE");
}

void Processor::Processor::INS_ORA_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ORA_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, (address+regXValue) % 65536)) {
        cycles--;
    }
    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ORA_ABSOLUTE_X");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_ABSOLUTE_X");
}

void Processor::Processor::INS_ORA_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ORA_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, (address+regYValue) % 65536)) {
        cycles--;
    }
    address = (address + regYValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ORA_ABSOLUTE_Y");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_ABSOLUTE_Y");
}

void Processor::Processor::INS_ORA_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ORA_INDEXED_INDIRECT");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_ORA_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_ORA_INDEXED_INDIRECT");

    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    cycles--;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_INDEXED_INDIRECT");
}

void Processor::Processor::INS_ORA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ORA_INDIRECT_INDEXED");

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_ORA_INDIRECT_INDEXED");

    Byte regYValue = getRegisterValue('Y');
    valueAddress = (valueAddress + regYValue) % 65536;

    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_ORA_INDIRECT_INDEXED");

    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue | value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ORA_INDIRECT_INDEXED");
}

void Processor::Processor::INS_EOR_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_EOR_IMMEDIATE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_IMMEDIATE");
}

void Processor::Processor::INS_EOR_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_EOR_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_EOR_ZEROPAGE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_ZEROPAGE");
}

void Processor::Processor::INS_EOR_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_EOR_ZEROPAGE_X");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Byte value = readByte(address, cycles, requested_cycles, "INS_EOR_ZEROPAGE_X");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    cycles--;

    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_ZEROPAGE_X");
}

void Processor::Processor::INS_EOR_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_EOR_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_EOR_ABSOLUTE");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_ABSOLUTE");
}

void Processor::Processor::INS_EOR_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_EOR_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, (address+regXValue) % 65536)) {
        cycles--;
    }
    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_EOR_ABSOLUTE_X");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_ABSOLUTE_X");
}

void Processor::Processor::INS_EOR_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_EOR_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, (address+regYValue) % 65536)) {
        cycles--;
    }
    address = (address + regYValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_EOR_ABSOLUTE_Y");
    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_ABSOLUTE_Y");
}

void Processor::Processor::INS_EOR_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_EOR_INDEXED_INDIRECT");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_EOR_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_EOR_INDEXED_INDIRECT");

    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    cycles--;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_INDEXED_INDIRECT");
}

void Processor::Processor::INS_EOR_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_EOR_INDIRECT_INDEXED");

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_EOR_INDIRECT_INDEXED");

    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(valueAddress, (valueAddress + regYValue) % 65536)){
        cycles--;
    }
    valueAddress = (valueAddress + regYValue) % 65536;

    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_EOR_INDIRECT_INDEXED");

    Byte regAValue = getRegisterValue('A');
    Byte result = regAValue ^ value;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_EOR_INDIRECT_INDEXED");
}

void Processor::Processor::INS_ROL_ACCUMULATOR_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regAValue = getRegisterValue('A');
    Byte result = (regAValue << 1) | getProcessorStatusFlag('C');
    cycles--;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROL_ACCUMULATOR");
    set_flags_C(this, regAValue, 0, 0x02, cycles, requested_cycles, "INS_ROL_ACCUMULATOR");
}

void Processor::Processor::INS_ROL_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ROL_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ROL_ABSOLUTE");
    Byte result = (value << 1) | getProcessorStatusFlag('C');
    cycles--;

    writeByte(address, result, cycles, requested_cycles, "INS_ROL_ABSOLUTE");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROL_ABSOLUTE");
    set_flags_C(this, value, 0, 0x02, cycles, requested_cycles, "INS_ROL_ABSOLUTE");
}

void Processor::Processor::INS_ROL_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ROL_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ROL_ABSOLUTE_X");
    Byte result = (value << 1) | getProcessorStatusFlag('C');
    cycles-=2;
    writeByte(address, result, cycles, requested_cycles, "INS_ROL_ABSOLUTE_X");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROL_ABSOLUTE_X");
    set_flags_C(this, value, 0, 0x02, cycles, requested_cycles, "INS_ROL_ABSOLUTE_X");
}

void Processor::Processor::INS_ROL_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ROL_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ROL_ZEROPAGE");

    Byte result = (value << 1) | getProcessorStatusFlag('C');
    cycles--;
    writeByte(address, result, cycles, requested_cycles, "INS_ROL_ZEROPAGE");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROL_ZEROPAGE");
    set_flags_C(this, value, 0, 0x02, cycles, requested_cycles, "INS_ROL_ZEROPAGE");
}

void Processor::Processor::INS_ROL_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ROL_ZEROPAGE_X");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ROL_ZEROPAGE_X");
    Byte result = (value << 1) | getProcessorStatusFlag('C');
    cycles-=2;
    writeByte(address, result, cycles, requested_cycles, "INS_ROL_ZEROPAGE_X");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROL_ZEROPAGE_X");
    set_flags_C(this, value, 0, 0x02, cycles, requested_cycles, "INS_ROL_ZEROPAGE_X");
}

void Processor::Processor::INS_ROR_ACCUMULATOR_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regAValue = getRegisterValue('A');
    Byte result = (regAValue >> 1) | (getProcessorStatusFlag('C') << 7);
    cycles--;
    setRegisterValue('A', result);

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROR_ACCUMULATOR");
    set_flags_C(this, regAValue, 0, 0x03, cycles, requested_cycles, "INS_ROR_ACCUMULATOR");
}

void Processor::Processor::INS_ROR_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ROR_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ROR_ABSOLUTE");
    Byte result = (value >> 1) | (getProcessorStatusFlag('C') << 7);
    cycles--;
    writeByte(address, result, cycles, requested_cycles, "INS_ROR_ABSOLUTE");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROR_ABSOLUTE");
    set_flags_C(this, value, 0, 0x03, cycles, requested_cycles, "INS_ROR_ABSOLUTE");
}

void Processor::Processor::INS_ROR_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_ROR_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 65536;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ROR_ABSOLUTE_X");
    Byte result = (value >> 1) | (getProcessorStatusFlag('C') << 7);
    cycles-=2;
    writeByte(address, result, cycles, requested_cycles, "INS_ROR_ABSOLUTE_X");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROR_ABSOLUTE_X");
    set_flags_C(this, value, 0, 0x03, cycles, requested_cycles, "INS_ROR_ABSOLUTE_X");
}

void Processor::Processor::INS_ROR_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ROR_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_ROR_ZEROPAGE");

    Byte result = (value >> 1) | (getProcessorStatusFlag('C') << 7);
    cycles--;

    writeByte(address, result, cycles, requested_cycles, "INS_ROR_ZEROPAGE");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROR_ZEROPAGE");
    set_flags_C(this, value, 0, 0x03, cycles, requested_cycles, "INS_ROR_ZEROPAGE");
}

void Processor::Processor::INS_ROR_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_ROR_ZEROPAGE_X");

    Byte regXValue = getRegisterValue('X');
    address = (address + regXValue) % 256;

    Byte value = readByte(address, cycles, requested_cycles, "INS_ROR_ZEROPAGE_X");
    Byte result = (value >> 1) | (getProcessorStatusFlag('C') << 7);
    cycles-=2;
    writeByte(address, result, cycles, requested_cycles, "INS_ROR_ZEROPAGE_X");

    set_flags_NZ(this, result, cycles, requested_cycles, "INS_ROR_ZEROPAGE_X");
    set_flags_C(this, value, 0, 0x03, cycles, requested_cycles, "INS_ROR_ZEROPAGE_X");
}

void Processor::Processor::INS_JMP_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_JMP_ABSOLUTE");
    setProgramCounter(address, cycles, requested_cycles, "INS_JMP_ABSOLUTE");
}

void Processor::Processor::INS_JMP_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word addressAddress = fetchWord(cycles, requested_cycles, "INS_JMP_INDIRECT");

    Byte addressLSB = readByte(addressAddress, cycles, requested_cycles, "INS_JMP_INDIRECT");
    Byte addressMSB = readByte((addressAddress & 0xFF00) | (((addressAddress & 0x00FF) + 1) % 256), cycles, requested_cycles, "INS_JMP_INDIRECT");

    Word address = (addressMSB << 8) | addressLSB;

    setProgramCounter(address, cycles, requested_cycles, "INS_JMP_INDIRECT");
}

void Processor::Processor::INS_JSR_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word subroutineAddress = fetchWord(cycles, requested_cycles, "INS_JSR");
    pushWordToStack(getProgramCounter() - 1, cycles, requested_cycles, "INS_JSR");
    setProgramCounter(subroutineAddress, cycles, requested_cycles, "INS_JSR");
    cycles--;
}

void Processor::Processor::INS_RTS_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = pullWordFromStack(cycles, requested_cycles, "INS_RTS");
    setProgramCounter(address + 1, cycles, requested_cycles, "INS_RTS");
    cycles-=3;
}

void Processor::Processor::INS_RTI_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte status = pullByteFromStack(cycles, requested_cycles, "INS_RTI");
    setProcessorStatusRegister(status);

    Word address = pullWordFromStack(cycles, requested_cycles, "INS_RTI");
    setProgramCounter(address);
    cycles-=2;
}
