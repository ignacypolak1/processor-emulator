#include <gtest/gtest.h>
#include "processor.h"

// Demonstrate some basic assertions.
TEST(Processor, INITIALIZATION_TEST) {
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

TEST(Processor, INS_LDA_IMMEDIATE_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xA9);
    processor->setMemoryByte(0xFFFD, 0x52);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x52) << "Wrong accumulator status, operation failed";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA9);
    processor->setMemoryByte(0xFFFD, 0x00);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA9);
    processor->setMemoryByte(0xFFFD, 0xFD);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFD) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 1) << "Negative flag expected to be set";

    delete processor;
}

TEST(Processor, INS_LDA_ZEROPAGE_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xA5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x08, 0x23);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x08, 0x00);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x08, 0xFB);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 1) << "Negative flag expected to be set";

    delete processor;
}

TEST(Processor, INS_LDA_ZEROPAGE_X_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xB5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x0A, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xB5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x0A, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xB5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x0A, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 1) << "Negative flag expected to be set";

    delete processor;
}

TEST(Processor, INS_JSR_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0x20);
    processor->setMemoryWord(0xFFFD, 0x4243);

    processor->execute(6);

    EXPECT_EQ(processor->getProgramCounter(), 0x4243) << "Wrong program counter value, operation failed";

    delete processor;
}