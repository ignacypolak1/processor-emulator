#include "../include/instructions.h"

#define NEGATIVE_MASK 0x80
#define WORD_LSB_MASK 0xFF00
#define WORD_MSB_MASK 0x00FF

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

    if(bAddressesOnDifferentPages(address, address+regYValue)) {
        cycles--;
    }

    Word valueAddress = readWord(address, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");
    Byte value = readByte(valueAddress, cycles, requested_cycles, "INS_LDA_INDIRECT_INDEXED");

    value += regYValue;

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
    Byte address = fetchByte(cycles, requested_cycles);
    Byte value = readByte(address, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    set_flags(this, value, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
    setRegisterValue('X', value, cycles, requested_cycles, "INS_LDX_ZEROPAGE_Y");
}