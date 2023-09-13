#include "processor.h"

int main() {
    Processor::Processor *processor = new Processor::Processor();

    processor->resetCPU();
    processor->execute(5);

    delete processor;
    return 0;
}
