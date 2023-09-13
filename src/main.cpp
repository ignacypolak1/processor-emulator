#include "processor.h"

int main() {
    Processor::Processor *processor = new Processor::Processor();

    printf("Register A value: 0x%04X\n", processor->getRegisterValue('A'));
    processor->resetCPU();
    processor->execute(2);
    printf("Register A value: 0x%04X\n", processor->getRegisterValue('A'));

    delete processor;
    return 0;
}
