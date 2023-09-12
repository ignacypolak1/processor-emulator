#include "processor.h"

int main() {
    Processor::Processor *processor = new Processor::Processor();

    printf("%x\n", processor->getStackPointer());
    printf("%x\n", processor->getProgramCounter());

    delete processor;
    return 0;
}
