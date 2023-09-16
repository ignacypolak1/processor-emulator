#include "../include/instructions.h"

#define NEGATIVE_MASK 0x80
#define WORD_LSB_MASK 0xFF00
#define WORD_MSB_MASK 0x00FF


void Processor::Processor::INS_LDA_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetchByte(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_IMMEDIATE: Found first argument: 0x%04X\n", requested_cycles-cycles, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_IMMEDIATE: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_IMMEDIATE: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}
void Processor::Processor::INS_LDA_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE: Found first word argument: 0x%04X\n", requested_cycles-cycles, address);
    #endif

    Byte value = readByte(address, cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE: Found value under address (0x%04X): 0x%04X\n", requested_cycles-cycles, address, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ABSOLUTE: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ABSOLUTE: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}

void Processor::Processor::INS_LDA_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE_X: Found first word argument: 0x%04X\n", requested_cycles-cycles, address);
    #endif
    Byte regXValue = getRegisterValue('X');

    if(int(address / 256) != int((address + regXValue) / 256)) {
        cycles--; // If address + regXValue crossed page in which base address is, decrement cycles by 1
    }

    Byte value = readByte(address + regXValue, cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE_X: Found value under address (0x%04X): 0x%04X\n", requested_cycles-cycles, address, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE_X: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE_X: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE_X: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ABSOLUTE_X: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ABSOLUTE_X: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE_X: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}
void Processor::Processor::INS_LDA_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word address = fetchWord(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Found first word argument: 0x%04X\n", requested_cycles-cycles, address);
    #endif
    Byte regYValue = getRegisterValue('Y');

    if(int(address / 256) != int((address + regYValue) / 256)) {
        cycles--; // If address + regYValue crossed page in which base address is, decrement cycles by 1
    }

    Byte value = readByte(address + regYValue, cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Found value under address (0x%04X): 0x%04X\n", requested_cycles-cycles, address, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ABSOLUTE_Y: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}

void Processor::Processor::INS_LDA_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE: Found first argument: 0x%04X\n", requested_cycles-cycles, address);
    #endif
    Byte value = readByte(address, cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE: Found value under address (0x%04X): 0x%04X\n", requested_cycles-cycles, address, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}
void Processor::Processor::INS_LDA_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = 0x0000;

    Byte first_address = fetchByte(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE_X: Found first argument: 0x%04X\n", requested_cycles-cycles, first_address);
    #endif

    Byte second_address = getRegisterValue('X');
    cycles--;
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE_X: Found second argument: 0x%04X\n", requested_cycles-cycles, second_address);
    #endif

    address = (first_address + second_address) % 256;
    Byte value = readByte(address, cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE_X: Found value under address (0x%04X): 0x%04X\n", requested_cycles-cycles, address, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE_X: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE_X: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE_X: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE_X: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE_X: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE_X: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}

void Processor::Processor::INS_LDA_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Found first argument: 0x%04X\n", requested_cycles-cycles, address);
    #endif
    Byte regXValue = getRegisterValue('X');

    Word valueAddress = readWord(address + regXValue, cycles, requested_cycles);
    Byte value = readByte(valueAddress, cycles, requested_cycles);
    cycles--; // Dummy cycle

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Found value under address (0x%04X): 0x%04X\n", requested_cycles-cycles, valueAddress, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_INDEXED_INDIRECT: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}
void Processor::Processor::INS_LDA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles);
    Byte regYValue = getRegisterValue('Y');
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Found first argument: 0x%04X\n", requested_cycles-cycles, address);
    #endif

    if(int(address / 256) != int((address + regYValue) / 256)) {
        cycles--; // If address + regXValue crossed page in which base address is, decrement cycles by 1
    }

    Word valueAddress = readWord(address, cycles, requested_cycles);
    Byte value = readByte(valueAddress, cycles, requested_cycles);

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Found value under address (0x%04X): 0x%04X, adding 0x%04X (Register X Value)\n", requested_cycles-cycles, valueAddress, value, regYValue);
    #endif
    value += regYValue;

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1);
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0);
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0);

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1);
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0);
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_INDIRECT_INDEXED: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value);
}

void Processor::Processor::INS_JSR_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Word subroutineAddress = fetchWord(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_JSR: Found first word argument: 0x%04X\n", requested_cycles-cycles, subroutineAddress);
    #endif
    writeWord(stack_pointer, program_counter-1, cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_JSR: Current program counter address (0x%04X) saved on stack addresses (0x%04X and 0x%04X)\n", requested_cycles-cycles, program_counter, stack_pointer, stack_pointer+1);
    #endif
    program_counter = subroutineAddress;
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_JSR: Current program counter set to subroutine address (0x%04X)\n", requested_cycles-cycles, subroutineAddress);
    #endif
    cycles--;
}