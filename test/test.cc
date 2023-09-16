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

TEST(Processor, INS_LDA_ABSOLUTE_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xAD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4324, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4324, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4324, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 1) << "Negative flag expected to be set";

    delete processor;
}

TEST(Processor, INS_LDA_ABSOLUTE_X_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xBD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x4326, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xBD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x4326, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xBD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x4326, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 1) << "Negative flag expected to be set";

    delete processor;
}

TEST(Processor, INS_LDA_ABSOLUTE_Y_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xB9);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setRegisterValue('Y', 0x02);
    processor->setMemoryByte(0x4326, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xB9);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setRegisterValue('Y', 0x02);
    processor->setMemoryByte(0x4326, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xB9);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setRegisterValue('Y', 0x02);
    processor->setMemoryByte(0x4326, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 1) << "Negative flag expected to be set";

    delete processor;
}

TEST(Processor, INS_LDA_INDEXED_INDIRECT_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xA1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x34, 0x22);
    processor->setMemoryByte(0x35, 0x23);
    processor->setMemoryByte(0x2322, 0x46);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x46) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x34, 0x22);
    processor->setMemoryByte(0x35, 0x23);
    processor->setMemoryByte(0x2322, 0x00);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setRegisterValue('X', 0x02);
    processor->setMemoryByte(0x34, 0x22);
    processor->setMemoryByte(0x35, 0x23);
    processor->setMemoryByte(0x2322, 0xFB);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 1) << "Negative flag expected to be set";

    delete processor;
}

TEST(Processor, INS_LDA_INDIRECT_INDEXED_TEST) {
    Processor::Processor *processor = new Processor::Processor();

    processor->setMemoryByte(0xFFFC, 0xB1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x32, 0x21);
    processor->setMemoryByte(0x33, 0x25);
    processor->setMemoryByte(0x2521, 0x23);
    processor->setRegisterValue('Y', 0x02);

    processor->execute(5);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x25) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 0) << "Zero flag expected to be unset";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xB1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x32, 0x21);
    processor->setMemoryByte(0x33, 0x25);
    processor->setMemoryByte(0x2521, 0x00);
    processor->setRegisterValue('Y', 0x00);

    processor->execute(5);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00) << "Wrong accumulator status, operation failed";
    EXPECT_EQ(processor->getProcessorStatus('Z'), 1) << "Zero flag expected to be set";
    EXPECT_EQ(processor->getProcessorStatus('N'), 0) << "Negative flag expected to be unset";

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xB1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x32, 0x21);
    processor->setMemoryByte(0x33, 0x25);
    processor->setMemoryByte(0x2521, 0xFA);
    processor->setRegisterValue('Y', 0x01);

    processor->execute(5);

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