#include "processor.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main() {

    Processor::Processor *processor;
    processor = new Processor::Processor();

    processor->vic2.showWindow();

    delete processor;

    return 0;
}