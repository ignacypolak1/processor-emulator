#include "processor.h"

int main() {
    Processor::Processor *processor = new Processor::Processor();

    printf("Accumulator value: 0x%04X\n", processor->getRegisterValue('A'));
    processor->resetCPU();
    processor->execute(8);
    printf("Accumulator value: 0x%04X\n", processor->getRegisterValue('A'));

    delete processor;
    return 0;
}
