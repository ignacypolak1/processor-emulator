#include <gtest/gtest.h>
#include "processor.h"

// Demonstrate some basic assertions.
TEST(Processor, Initialization) {
    Processor::Processor *processor = new Processor::Processor();

    EXPECT_EQ(processor->getProgramCounter(), 0xFFFC) << "Program Counter initialized successfully";
    EXPECT_EQ(processor->getStackPointer(), 0x0100) << "Stack Pointer initialized successfully";

    bool nonZeroMemory = false;
    for(const auto& value: processor->getMemory()) {
        if(value != 0)
        {
            nonZeroMemory = true;
        }
    }
    EXPECT_FALSE(nonZeroMemory) << "Memory initialization failed, expected all memory cleared";

    bool nonZeroRegister = false;
    char generalPurposeRegisters[] = {'A', 'X', 'Y'};
    for(const auto& reg : generalPurposeRegisters) {
        if(processor->getRegisterValue(reg) != 0)
        {
            nonZeroRegister = true;
        }
    }
    EXPECT_FALSE(nonZeroRegister) << "General purpose registers initialization failed, expected all registers cleared";

    bool nonZeroStatus = false;
    char statusBits[] = {'C', 'Z', 'I', 'D', 'B', 'V', 'N'};
    for(const auto& bit : statusBits) {
        if(processor->getProcessorStatus(bit) != 0)
        {
            nonZeroRegister = true;
        }
    }
    EXPECT_FALSE(nonZeroStatus) << "Status register initialization failed, expected all bits cleared";
    delete processor;
}