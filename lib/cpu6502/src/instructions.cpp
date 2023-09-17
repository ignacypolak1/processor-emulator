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
        {INS_JSR, &Processor::Processor::INS_JSR_HANDLE},
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
        {INS_DEC_ABSOLUTE_X, &Processor::Processor::INS_DEC_ABSOLUTE_X_HANDLE}
};

void set_flags(Processor::Processor *processor, Processor::Byte value, Processor::Dword &cycles, const Processor::Dword &requested_cycles, const std::string opname) {

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: %s: Setting Zero Flag\n", requested_cycles-cycles, opname.c_str());
        #endif
        processor->setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: %s: Resetting Negative Flag\n", requested_cycles-cycles, opname.c_str());
        #endif
        processor->setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: %s: Resetting Zero Flag\n", requested_cycles-cycles, opname.c_str());
        #endif
        processor->setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: %s: Setting Negative Flag\n", requested_cycles-cycles, opname.c_str());
            #endif
            processor->setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: %s: Resetting Negative Flag\n", requested_cycles-cycles, opname.c_str());
            #endif
            processor->setProcessorStatus('N', 0);
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
    set_flags(this, value, cycles, requested_cycles, "INS_LDA_IMMEDIATE");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_IMMEDIATE");
}
void Processor::Processor::INS_LDA_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDA_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDA_ABSOLUTE");
    set_flags(this, value, cycles, requested_cycles, "INS_LDA_ABSOLUTE");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ABSOLUTE");
}

void Processor::Processor::INS_LDA_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, address+regXValue)) {
        cycles--;
    }

    Byte value = readByte(address + regXValue, cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
    set_flags(this, value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_X");
}
void Processor::Processor::INS_LDA_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }

    Byte value = readByte(address + regYValue, cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
    set_flags(this, value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ABSOLUTE_Y");
}

void Processor::Processor::INS_LDA_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDA_ZEROPAGE");

    set_flags(this, value, cycles, requested_cycles, "INS_LDA_ZEROPAGE");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ZEROPAGE");
}
void Processor::Processor::INS_LDA_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    cycles--;

    address = (address + regXValue) % 256;
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");

    set_flags(this, value, cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_ZEROPAGE_X");
}

void Processor::Processor::INS_LDA_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
    Byte regXValue = getRegisterValue('X');

    Word valueAddress = readWord(address + regXValue, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");

    cycles--; // Dummy cycle

    set_flags(this, value, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_INDEXED_INDIRECT");
}

void Processor::Processor::INS_LDA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");
    Byte regYValue = getRegisterValue('Y');

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");

    if(bAddressesOnDifferentPages(valueAddress, valueAddress+regYValue)) {
        cycles--;
    }

    Byte value = readByte(valueAddress + regYValue, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");

    set_flags(this, value, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");
    setRegisterValue('A', value, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");
}

void Processor::Processor::INS_JSR_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word subroutineAddress = fetchWord(cycles, requested_cycles, "INS_JSR");

    writeWord(stack_pointer, program_counter-1, cycles, requested_cycles, "INS_JSR");
    setProgramCounter(subroutineAddress, cycles, requested_cycles, "INS_JSR");
    cycles--;
}

void Processor::Processor::INS_LDX_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_LDX_IMMEDIATE");
    set_flags(this, value, cycles, requested_cycles, "INS_LDX_IMMEDIATE");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_IMMEDIATE");
}
void Processor::Processor::INS_LDX_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDX_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDX_ABSOLUTE");
    set_flags(this, value, cycles, requested_cycles, "INS_LDX_ABSOLUTE");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ABSOLUTE");
}
void Processor::Processor::INS_LDX_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
    Byte regYValue = getRegisterValue('Y');

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }

    Byte value = readByte(address + regYValue, cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
    set_flags(this, value, cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ABSOLUTE_Y");
}
void Processor::Processor::INS_LDX_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDX_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDX_ZEROPAGE");
    set_flags(this, value, cycles, requested_cycles, "INS_LDX_ZEROPAGE");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ZEROPAGE");
}
void Processor::Processor::INS_LDX_ZEROPAGE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    Byte regYVal = getRegisterValue('Y');

    address = (address + regYVal) % 256;
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    cycles--;

    set_flags(this, value, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
}

void Processor::Processor::INS_LDY_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles, "INS_LDY_IMMEDIATE");
    set_flags(this, value, cycles, requested_cycles, "INS_LDY_IMMEDIATE");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_IMMEDIATE");
}
void Processor::Processor::INS_LDY_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDY_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDY_ABSOLUTE");
    set_flags(this, value, cycles, requested_cycles, "INS_LDY_ABSOLUTE");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_ABSOLUTE");
}
void Processor::Processor::INS_LDY_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    if(bAddressesOnDifferentPages(address, address+regXValue)) {
        cycles--;
    }

    Byte value = readByte(address + regXValue, cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
    set_flags(this, value, cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_ABSOLUTE_X");
}
void Processor::Processor::INS_LDY_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDY_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDY_ZEROPAGE");
    set_flags(this, value, cycles, requested_cycles, "INS_LDY_ZEROPAGE");
    setRegisterValue('Y', value, cycles, requested_cycles, "INS_LDY_ZEROPAGE");
}
void Processor::Processor::INS_LDY_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_LDY_ZEROPAGE_X");
    Byte regXVal = getRegisterValue('X');

    address = (address + regXVal) % 256;
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDY_ZEROPAGE_X");
    cycles--;

    set_flags(this, value, cycles, requested_cycles, "INS_LDY_ZEROPAGE_X");
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
    Word address = fetchByte(cycles, requested_cycles, "INS_STA_INDEXED_INDIRECT");
    Byte regAValue = getRegisterValue('A');
    Byte regXValue = getRegisterValue('X');
    cycles--;
    Word valueAddress = readWord(address+regXValue, cycles, requested_cycles, "INS_STA_INDEXED_INDIRECT");
    writeByte(valueAddress, regAValue, cycles, requested_cycles, "INS_STA_INDEXED_INDIRECT");
}

void Processor::Processor::INS_STA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchByte(cycles, requested_cycles, "INS_STA_INDIRECT_INDEXED");
    Byte regAValue = getRegisterValue('A');
    Byte regYValue = getRegisterValue('Y');
    cycles--;
    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_STA_INDIRECT_INDEXED");
    writeByte(valueAddress+regYValue, regAValue, cycles, requested_cycles, "INS_STA_INDIRECT_INDEXED");
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
    setProcessorStatus('C', 0);
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Carry Flag\n", requested_cycles-cycles, "INS_CLC");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_CLD_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatus('D', 0);
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Decimal Flag\n", requested_cycles-cycles, "INS_CLD");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_CLI_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatus('I', 0);
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Interrupt Flag\n", requested_cycles-cycles, "INS_CLI");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_CLV_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatus('V', 0);
    #ifdef DEBUG
        printf("Cycle %i: %s: Resetting Overflow Flag\n", requested_cycles-cycles, "INS_CLV");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_SEC_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatus('C', 1);
    #ifdef DEBUG
        printf("Cycle %i: %s: Setting Carry Flag\n", requested_cycles-cycles, "INS_SEC");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_SED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatus('D', 1);
    #ifdef DEBUG
        printf("Cycle %i: %s: Setting Decimal Flag\n", requested_cycles-cycles, "INS_SED");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_SEI_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    setProcessorStatus('I', 1);
    #ifdef DEBUG
        printf("Cycle %i: %s: Setting Interrupt Flag\n", requested_cycles-cycles, "INS_SEI");
    #endif
    cycles-=1;
}

void Processor::Processor::INS_TAX_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regAValue = getRegisterValue('A');
    setRegisterValue('X', regAValue, cycles, requested_cycles, "INS_TAX");
    cycles--;
    set_flags(this, regAValue, cycles, requested_cycles, "INS_TAX");
}

void Processor::Processor::INS_TAY_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regAValue = getRegisterValue('A');
    setRegisterValue('Y', regAValue, cycles, requested_cycles, "INS_TAY");
    cycles--;
    set_flags(this, regAValue, cycles, requested_cycles, "INS_TAY");
}

void Processor::Processor::INS_TXA_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regXValue = getRegisterValue('X');
    setRegisterValue('A', regXValue, cycles, requested_cycles, "INS_TXA");
    cycles--;
    set_flags(this, regXValue, cycles, requested_cycles, "INS_TXA");
}

void Processor::Processor::INS_TYA_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte regYValue = getRegisterValue('Y');
    setRegisterValue('A', regYValue, cycles, requested_cycles, "INS_TYA");
    cycles--;
    set_flags(this, regYValue, cycles, requested_cycles, "INS_TYA");
}

void Processor::Processor::INS_TSX_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte stackValue = getStackPointer();
    setRegisterValue('X', stackValue, cycles, requested_cycles, "INS_TSX");
    cycles--;
    set_flags(this, stackValue, cycles, requested_cycles, "INS_TSX");
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
    set_flags(this, value, cycles, requested_cycles, "INS_INC_ZEROPAGE");
}

void Processor::Processor::INS_INC_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    cycles-=2;

    Byte value = readByte(address, cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
    value++;
    writeByte(address, value, cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
    set_flags(this, value, cycles, requested_cycles, "INS_INC_ZEROPAGE_X");
}

void Processor::Processor::INS_INC_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_INC_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_INC_ABSOLUTE");
    cycles--;
    value++;
    writeByte(address, value, cycles, requested_cycles, "INS_INC_ABSOLUTE");
    set_flags(this, value, cycles, requested_cycles, "INS_INC_ABSOLUTE");
}

void Processor::Processor::INS_INC_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 65536;
    cycles-=2;

    Byte value = readByte(address, cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
    value++;
    writeByte(address, value, cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
    set_flags(this, value, cycles, requested_cycles, "INS_INC_ABSOLUTE_X");
}

void Processor::Processor::INS_DEC_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_DEC_ZEROPAGE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ZEROPAGE");
    cycles--;
    value--;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE");
    set_flags(this, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE");
}

void Processor::Processor::INS_DEC_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 256;
    cycles-=2;

    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
    value--;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
    set_flags(this, value, cycles, requested_cycles, "INS_DEC_ZEROPAGE_X");
}

void Processor::Processor::INS_DEC_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_DEC_ABSOLUTE");
    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ABSOLUTE");
    value--;
    cycles-=1;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE");
    set_flags(this, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE");
}

void Processor::Processor::INS_DEC_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
    Byte regXValue = getRegisterValue('X');

    address = (address + regXValue) % 65536;
    Byte value = readByte(address, cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
    value--;
    cycles-=2;
    writeByte(address, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
    set_flags(this, value, cycles, requested_cycles, "INS_DEC_ABSOLUTE_X");
}
