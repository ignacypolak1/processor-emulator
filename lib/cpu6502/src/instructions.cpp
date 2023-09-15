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
        setProcessorStatus('Z', 1); // Set Zero Flag, if value is 0
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0); // Reset Negative Flag, if value loaded value is non negative
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0); // Reset Zero Flag, if value is not 0

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_IMMEDIATE: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1); // Set Negative Flag, if value loaded value is negative
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0); // Reset Negative Flag, if value loaded value is non negative
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_IMMEDIATE: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value); // Set value in Accumulator Register
}
void Processor::Processor::INS_LDA_ABSOLUTE_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = fetchByte(cycles, requested_cycles); // Get zero page address
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
        setProcessorStatus('Z', 1); // Set Zero Flag, if value is 0
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0); // Reset Negative Flag, if value loaded value is non negative
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0); // Reset Zero Flag, if value is not 0

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1); // Set Negative Flag, if value loaded value is negative
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0); // Reset Negative Flag, if value loaded value is non negative
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value); // Set value in Accumulator Register

}
void Processor::Processor::INS_LDA_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte address = 0x0000;

    Byte first_address = fetchByte(cycles, requested_cycles); // Get zero page address
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE_X: Found first argument: 0x%04X\n", requested_cycles-cycles, first_address);
    #endif

    Byte second_address = fetchByte(cycles, requested_cycles); // Get zero page address
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
        setProcessorStatus('Z', 1); // Set Zero Flag, if value is 0
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Resetting Negative Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('N', 0); // Reset Negative Flag, if value loaded value is non negative
    }

    else {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_ZEROPAGE: Resetting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 0); // Reset Zero Flag, if value is not 0

        if(value & NEGATIVE_MASK) {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE: Setting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 1); // Set Negative Flag, if value loaded value is negative
        }
        else {
            #ifdef DEBUG
                        printf("Cycle %i: INS_LDA_ZEROPAGE: Resetting Negative Flag\n", requested_cycles-cycles);
            #endif
            setProcessorStatus('N', 0); // Reset Negative Flag, if value loaded value is non negative
        }
    }

    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_ZEROPAGE: Setting Accumulator Register(A) with value 0x%04X\n", requested_cycles-cycles, value);
    #endif
    setRegisterValue('A', value); // Set value in Accumulator Register
}
void Processor::Processor::INS_LDA_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {

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