#include "instructions.h"

#define NEGATIVE_MASK 0x80

void Processor::Processor::INS_LDA_IMMEDIATE_HANDLE(Dword &cycles, const Dword &requested_cycles) {
    Byte value = fetch(cycles, requested_cycles);
    #ifdef DEBUG
        printf("Cycle %i: INS_LDA_IMMEDIATE: Found first argument: 0x%04X\n", requested_cycles-cycles, value);
    #endif

    if(!value) {
        #ifdef DEBUG
                printf("Cycle %i: INS_LDA_IMMEDIATE: Setting Zero Flag\n", requested_cycles-cycles);
        #endif
        setProcessorStatus('Z', 1); // Set Zero Flag, if value is 0
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
    Word address = 0x0000;

    address = (address & 0xFF00) | fetch(cycles, requested_cycles); // Set LSB of address
    address = (address & 0x00FF) | (fetch(cycles, requested_cycles) << 8); // Set MSB of address

}
void Processor::Processor::INS_LDA_ABSOLUTE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_ABSOLUTE_Y_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_ZEROPAGE_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_ZEROPAGE_X_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_INDEXED_INDIRECT_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}
void Processor::Processor::INS_LDA_INDIRECT_INDEXED_HANDLE(Dword &cycles, const Dword &requested_cycles) {

}