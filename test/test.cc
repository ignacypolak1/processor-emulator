#include <gtest/gtest.h>
#include "processor.h"


class ProcessorTest:public ::testing::Test {
protected:
    Processor::Processor *processor;

    void SetUp() override {
        processor = new Processor::Processor();
    }

    void TearDown() override {
        delete processor;
    }
};

TEST_F(ProcessorTest, INITIALIZATION_TEST) {
    EXPECT_EQ(processor->getProgramCounter(), 0xFFFC) << "Program Counter initialized successfully";
    EXPECT_EQ(processor->getStackPointer(), 0x0100) << "Stack Pointer initialized successfully";

    bool nonZeroMemory = false;
    for(const auto& value: processor->getMemory()) {
        if(value != 0)
        {
            nonZeroMemory = true;
        }
    }
    EXPECT_FALSE(nonZeroMemory);

    bool nonZeroRegister = false;
    char generalPurposeRegisters[] = {'A', 'X', 'Y'};
    for(const auto& reg : generalPurposeRegisters) {
        if(processor->getRegisterValue(reg) != 0)
        {
            nonZeroRegister = true;
        }
    }
    EXPECT_FALSE(nonZeroRegister);
    EXPECT_EQ(processor->getProcessorStatusRegister(), 0x20);
}

TEST_F(ProcessorTest, INS_LDA_IMMEDIATE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xA9);
    processor->setMemoryByte(0xFFFD, 0x52);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA9);
    processor->setMemoryByte(0xFFFD, 0x00);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA9);
    processor->setMemoryByte(0xFFFD, 0xFD);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDA_ZEROPAGE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xA5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x08, 0x23);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x08, 0x00);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x08, 0xFB);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDA_ZEROPAGE_X_TEST) {
    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x0A, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x0A, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB5);
    processor->setMemoryByte(0xFFFD, 0x08);
    processor->setMemoryByte(0x0A, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDA_ABSOLUTE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xAD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4324, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4324, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4324, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDA_ABSOLUTE_X_TEST) {
    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xBD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4326, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xBD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4326, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xBD);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4326, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDA_ABSOLUTE_Y_TEST) {
    processor->setRegisterValue('Y', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB9);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4326, 0x23);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x23);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB9);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4326, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB9);
    processor->setMemoryWord(0xFFFD, 0x4324);
    processor->setMemoryByte(0x4326, 0xFB);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDA_INDEXED_INDIRECT_TEST) {
    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xA1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x34, 0x22);
    processor->setMemoryByte(0x35, 0x23);
    processor->setMemoryByte(0x2322, 0x46);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x46);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xA1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x34, 0x22);
    processor->setMemoryByte(0x35, 0x23);
    processor->setMemoryByte(0x2322, 0x00);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xA1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x34, 0x22);
    processor->setMemoryByte(0x35, 0x23);
    processor->setMemoryByte(0x2322, 0xFB);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDA_INDIRECT_INDEXED_TEST) {
    processor->setRegisterValue('Y', 0x01);

    processor->setMemoryByte(0xFFFC, 0xB1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x32, 0x21);
    processor->setMemoryByte(0x33, 0x25);
    processor->setMemoryByte(0x2522, 0x25);

    processor->execute(5);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);

    processor->setMemoryByte(0xFFFC, 0xB1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x32, 0x21);
    processor->setMemoryByte(0x33, 0x25);
    processor->setMemoryByte(0x2522, 0x00);

    processor->execute(5);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);

    processor->setMemoryByte(0xFFFC, 0xB1);
    processor->setMemoryWord(0xFFFD, 0x32);
    processor->setMemoryByte(0x32, 0x21);
    processor->setMemoryByte(0x33, 0x25);
    processor->setMemoryByte(0x2522, 0xFB);

    processor->execute(5);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDX_IMMEDIATE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xA2);
    processor->setMemoryByte(0xFFFD, 0x52);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA2);
    processor->setMemoryByte(0xFFFD, 0x00);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA2);
    processor->setMemoryByte(0xFFFD, 0xFD);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDX_ABSOLUTE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xAE);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2541, 0x52);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAE);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2541, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAE);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2541, 0xFD);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDX_ABSOLUTE_Y_TEST) {
    processor->setRegisterValue('Y', 0x01);

    processor->setMemoryByte(0xFFFC, 0xBE);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2542, 0x52);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);

    processor->setMemoryByte(0xFFFC, 0xBE);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2542, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);

    processor->setMemoryByte(0xFFFC, 0xBE);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2542, 0xFD);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDX_ZEROPAGE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xA6);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x25, 0x52);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA6);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x25, 0x00);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA6);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x25, 0xFD);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('X'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDX_ZEROPAGE_Y_TEST) {
    processor->setRegisterValue('Y', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB6);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x27, 0x52);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB6);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x27, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB6);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x27, 0xFD);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('X'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDY_IMMEDIATE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xA0);
    processor->setMemoryByte(0xFFFD, 0x52);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA0);
    processor->setMemoryByte(0xFFFD, 0x00);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA0);
    processor->setMemoryByte(0xFFFD, 0xFD);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDY_ABSOLUTE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xAC);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2541, 0x52);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAC);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2541, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xAC);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2541, 0xFD);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDY_ABSOLUTE_X_TEST) {
    processor->setRegisterValue('X', 0x01);

    processor->setMemoryByte(0xFFFC, 0xBC);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2542, 0x52);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);

    processor->setMemoryByte(0xFFFC, 0xBC);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2542, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);

    processor->setMemoryByte(0xFFFC, 0xBC);
    processor->setMemoryWord(0xFFFD, 0x2541);
    processor->setMemoryByte(0x2542, 0xFD);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDY_ZEROPAGE_TEST) {
    processor->setMemoryByte(0xFFFC, 0xA4);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x25, 0x52);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA4);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x25, 0x00);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xA4);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x25, 0xFD);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_LDY_ZEROPAGE_X_TEST) {
    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB4);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x27, 0x52);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x52);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB4);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x27, 0x00);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x02);

    processor->setMemoryByte(0xFFFC, 0xB4);
    processor->setMemoryByte(0xFFFD, 0x25);
    processor->setMemoryByte(0x27, 0xFD);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFD);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
}

TEST_F(ProcessorTest, INS_STA_ABSOLUTE_TEST) {
    processor->setRegisterValue('A', 0x23);

    processor->setMemoryByte(0xFFFC, 0x8D);
    processor->setMemoryWord(0xFFFD, 0x4324);

    processor->execute(4);

    EXPECT_EQ(processor->getMemory()[0x4324], 0x23);
}

TEST_F(ProcessorTest, INS_STA_ABSOLUTE_X_TEST) {
    processor->setRegisterValue('X', 0x02);
    processor->setRegisterValue('A', 0x23);

    processor->setMemoryByte(0xFFFC, 0x9D);
    processor->setMemoryWord(0xFFFD, 0x4324);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x4326], 0x23);
}

TEST_F(ProcessorTest, INS_STA_ABSOLUTE_Y_TEST) {
    processor->setRegisterValue('Y', 0x02);
    processor->setRegisterValue('A', 0x23);

    processor->setMemoryByte(0xFFFC, 0x99);
    processor->setMemoryWord(0xFFFD, 0x4324);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x4326], 0x23);
}

TEST_F(ProcessorTest, INS_STA_ZEROPAGE_TEST) {
    processor->setRegisterValue('A', 0x23);

    processor->setMemoryByte(0xFFFC, 0x85);
    processor->setMemoryByte(0xFFFD, 0x0024);

    processor->execute(3);

    EXPECT_EQ(processor->getMemory()[0x0024], 0x23);
}

TEST_F(ProcessorTest, INS_STA_ZEROPAGE_X_TEST) {
    processor->setRegisterValue('X', 0x02);
    processor->setRegisterValue('A', 0x23);

    processor->setMemoryByte(0xFFFC, 0x95);
    processor->setMemoryByte(0xFFFD, 0x24);

    processor->execute(4);

    EXPECT_EQ(processor->getMemory()[0x0026], 0x23);
}

TEST_F(ProcessorTest, INS_STA_ZEROPAGE_INDEXED_INDIRECT) {
    processor->setRegisterValue('X', 0x02);
    processor->setRegisterValue('A', 0x28);

    processor->setMemoryByte(0xFFFC, 0x81);
    processor->setMemoryByte(0xFFFD, 0x23);
    processor->setMemoryWord(0x25, 0x3421);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x3421], 0x28);
}

TEST_F(ProcessorTest, INS_STA_ZEROPAGE_INDIRECT_INDEXED) {
    processor->setRegisterValue('Y', 0x02);
    processor->setRegisterValue('A', 0x28);

    processor->setMemoryByte(0xFFFC, 0x91);
    processor->setMemoryByte(0xFFFD, 0x23);
    processor->setMemoryWord(0x23, 0x3421);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x3423], 0x28);
}

TEST_F(ProcessorTest, INS_STX_ABSOLUTE_TEST) {
    processor->setRegisterValue('X', 0x28);

    processor->setMemoryByte(0xFFFC, 0x8E);
    processor->setMemoryWord(0xFFFD, 0x2346);

    processor->execute(4);

    EXPECT_EQ(processor->getMemory()[0x2346], 0x28);
}

TEST_F(ProcessorTest, INS_STX_ZEROPAGE_TEST) {
    processor->setRegisterValue('X', 0x28);

    processor->setMemoryByte(0xFFFC, 0x86);
    processor->setMemoryByte(0xFFFD, 0x25);

    processor->execute(3);

    EXPECT_EQ(processor->getMemory()[0x25], 0x28);
}

TEST_F(ProcessorTest, INS_STX_ZEROPAGE_Y_TEST) {
    processor->setRegisterValue('Y', 0x02);
    processor->setRegisterValue('X', 0x28);

    processor->setMemoryByte(0xFFFC, 0x96);
    processor->setMemoryByte(0xFFFD, 0x25);

    processor->execute(4);

    EXPECT_EQ(processor->getMemory()[0x27], 0x28);
}

TEST_F(ProcessorTest, INS_STY_ABSOLUTE_TEST) {
    processor->setRegisterValue('Y', 0x28);

    processor->setMemoryByte(0xFFFC, 0x8C);
    processor->setMemoryWord(0xFFFD, 0x2346);

    processor->execute(4);

    EXPECT_EQ(processor->getMemory()[0x2346], 0x28);
}

TEST_F(ProcessorTest, INS_STY_ZEROPAGE_TEST) {
    processor->setRegisterValue('Y', 0x28);

    processor->setMemoryByte(0xFFFC, 0x84);
    processor->setMemoryByte(0xFFFD, 0x25);

    processor->execute(3);

    EXPECT_EQ(processor->getMemory()[0x25], 0x28);
}

TEST_F(ProcessorTest, INS_STY_ZEROPAGE_X_TEST) {
    processor->setRegisterValue('X', 0x02);
    processor->setRegisterValue('Y', 0x28);

    processor->setMemoryByte(0xFFFC, 0x94);
    processor->setMemoryByte(0xFFFD, 0x25);

    processor->execute(4);

    EXPECT_EQ(processor->getMemory()[0x27], 0x28);
}

TEST_F(ProcessorTest, INS_CLC_TEST) {
    processor->setProcessorStatusFlag('C');
    processor->setMemoryByte(0xFFFC, 0x18);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CLD_TEST) {
    processor->resetProcessorStatusFlag('D');
    processor->setMemoryByte(0xFFFC, 0xD8);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('D'), 0);
}

TEST_F(ProcessorTest, INS_CLI_TEST) {
    processor->resetProcessorStatusFlag('I');
    processor->setMemoryByte(0xFFFC, 0x58);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('I'), 0);
}

TEST_F(ProcessorTest, INS_CLV_TEST) {
    processor->resetProcessorStatusFlag('V');
    processor->setMemoryByte(0xFFFC, 0xB8);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);
}

TEST_F(ProcessorTest, INS_SEC_TEST) {
    processor->setProcessorStatusFlag('C');
    processor->setMemoryByte(0xFFFC, 0x38);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
}

TEST_F(ProcessorTest, INS_SED_TEST) {
    processor->setProcessorStatusFlag('D');
    processor->setMemoryByte(0xFFFC, 0xF8);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('D'), 1);
}

TEST_F(ProcessorTest, INS_SEI_TEST) {
    processor->setProcessorStatusFlag('I');
    processor->setMemoryByte(0xFFFC, 0x78);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('I'), 1);
}

TEST_F(ProcessorTest, INS_TAX_TEST) {

    processor->setRegisterValue('A', 0x24);
    processor->setMemoryByte(0xFFFC, 0xAA);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('X'), 0x24);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x00);
    processor->setMemoryByte(0xFFFC, 0xAA);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);

    processor->resetCPU();

    processor->setRegisterValue('A', 0xFE);
    processor->setMemoryByte(0xFFFC, 0xAA);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('X'), 0xFE);
}

TEST_F(ProcessorTest, INS_TAY_TEST) {

    processor->setRegisterValue('A', 0x24);
    processor->setMemoryByte(0xFFFC, 0xA8);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('Y'), 0x24);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x00);
    processor->setMemoryByte(0xFFFC, 0xA8);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);

    processor->resetCPU();

    processor->setRegisterValue('A', 0xFE);
    processor->setMemoryByte(0xFFFC, 0xA8);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFE);
}

TEST_F(ProcessorTest, INS_TXA_TEST) {

    processor->setRegisterValue('X', 0x24);
    processor->setMemoryByte(0xFFFC, 0x8A);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('A'), 0x24);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x00);
    processor->setMemoryByte(0xFFFC, 0x8A);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);

    processor->resetCPU();

    processor->setRegisterValue('X', 0xFE);
    processor->setMemoryByte(0xFFFC, 0x8A);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('A'), 0xFE);
}

TEST_F(ProcessorTest, INS_TYA_TEST) {

    processor->setRegisterValue('Y', 0x24);
    processor->setMemoryByte(0xFFFC, 0x98);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('A'), 0x24);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x00);
    processor->setMemoryByte(0xFFFC, 0x98);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0xFE);
    processor->setMemoryByte(0xFFFC, 0x98);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('A'), 0xFE);
}

TEST_F(ProcessorTest, INS_TSX_TEST) {

    processor->setStackPointer(0x24);
    processor->setMemoryByte(0xFFFC, 0xBA);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('X'), 0x24);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setStackPointer(0x00);
    processor->setMemoryByte(0xFFFC, 0xBA);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setStackPointer(0xFE);
    processor->setMemoryByte(0xFFFC, 0xBA);

    processor->execute(2);
    EXPECT_EQ(processor->getRegisterValue('X'), 0xFE);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_TXS_TEST) {

    processor->setRegisterValue('X', 0x24);
    processor->setMemoryByte(0xFFFC, 0x9A);

    processor->execute(2);
    EXPECT_EQ(processor->getStackPointer(), 0x0124);
}

TEST_F(ProcessorTest, INS_INC_ZEROPAGE_TEST) {

    processor->setMemoryByte(0xFFFC, 0xE6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x22, 0x24);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x22], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xE6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x22, 0xFF);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x22], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xE6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x22, 0xFA);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x22], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_INC_ZEROPAGE_X_TEST) {
    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xF6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x23, 0x24);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x23], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xF6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x23, 0xFF);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x23], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xF6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x23, 0xFA);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x23], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_INC_ABSOLUTE_TEST) {

    processor->setMemoryByte(0xFFFC, 0xEE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2041, 0x24);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x2041], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xEE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2041, 0xFF);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x2041], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xEE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2041, 0xFA);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x2041], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_INC_ABSOLUTE_X_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xFE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2042, 0x24);

    processor->execute(7);

    EXPECT_EQ(processor->getMemory()[0x2042], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xFE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2042, 0xFF);

    processor->execute(7);

    EXPECT_EQ(processor->getMemory()[0x2042], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xFE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2042, 0xFA);

    processor->execute(7);

    EXPECT_EQ(processor->getMemory()[0x2042], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_DEC_ZEROPAGE_TEST) {

    processor->setMemoryByte(0xFFFC, 0xC6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x22, 0x26);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x22], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xC6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x22, 0x01);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x22], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xC6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x22, 0xFC);

    processor->execute(5);

    EXPECT_EQ(processor->getMemory()[0x22], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_DEC_ZEROPAGE_X_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xD6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x23, 0x26);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x23], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xD6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x23, 0x01);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x23], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xD6);
    processor->setMemoryByte(0xFFFD, 0x22);
    processor->setMemoryByte(0x23, 0xFC);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x23], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_DEC_ABSOLUTE_TEST) {

    processor->setMemoryByte(0xFFFC, 0xCE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2041, 0x26);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x2041], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xCE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2041, 0x01);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x2041], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setMemoryByte(0xFFFC, 0xCE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2041, 0xFC);

    processor->execute(6);

    EXPECT_EQ(processor->getMemory()[0x2041], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_DEC_ABSOLUTE_X_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xDE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2042, 0x26);

    processor->execute(7);

    EXPECT_EQ(processor->getMemory()[0x2042], 0x25);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xDE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2042, 0x01);

    processor->execute(7);

    EXPECT_EQ(processor->getMemory()[0x2042], 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xDE);
    processor->setMemoryWord(0xFFFD, 0x2041);
    processor->setMemoryByte(0x2042, 0xFC);

    processor->execute(7);

    EXPECT_EQ(processor->getMemory()[0x2042], 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_INX_TEST) {
    processor->setRegisterValue('X', 0x23);
    processor->setMemoryByte(0xFFFC, 0xE8);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x24);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0xFF);
    processor->setMemoryByte(0xFFFC, 0xE8);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0xFA);
    processor->setMemoryByte(0xFFFC, 0xE8);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_DEX_TEST) {
    processor->setRegisterValue('X', 0x25);
    processor->setMemoryByte(0xFFFC, 0xCA);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x24);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setMemoryByte(0xFFFC, 0xCA);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0xFC);
    processor->setMemoryByte(0xFFFC, 0xCA);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('X'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_INY_TEST) {
    processor->setRegisterValue('Y', 0x23);
    processor->setMemoryByte(0xFFFC, 0xC8);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x24);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0xFF);
    processor->setMemoryByte(0xFFFC, 0xC8);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0xFA);
    processor->setMemoryByte(0xFFFC, 0xC8);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_DEY_TEST) {
    processor->setRegisterValue('Y', 0x25);
    processor->setMemoryByte(0xFFFC, 0x88);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x24);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);
    processor->setMemoryByte(0xFFFC, 0x88);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0xFC);
    processor->setMemoryByte(0xFFFC, 0x88);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('Y'), 0xFB);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
}

TEST_F(ProcessorTest, INS_ADC_IMMEDIATE_TEST) {

    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x69);
    processor->setMemoryByte(0xFFFD, 0x01);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0x00);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x69);
    processor->setMemoryByte(0xFFFD, 0x10);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x82);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_ADC_ZEROPAGE_TEST) {

    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x65);
    processor->setMemoryByte(0xFFFD, 0x28);
    processor->setMemoryByte(0x28, 0x01);

    processor->execute(3);
    processor->setMemoryByte(0x0025, 0x00);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x65);
    processor->setMemoryByte(0xFFFD, 0x29);
    processor->setMemoryByte(0x29, 0x10);

    processor->execute(3);
    processor->setMemoryByte(0x0026, 0x82);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_ADC_ZEROPAGE_X_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x75);
    processor->setMemoryByte(0xFFFD, 0x28);
    processor->setMemoryByte(0x29, 0x01);

    processor->execute(4);
    processor->setMemoryByte(0x0025, 0x00);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x75);
    processor->setMemoryByte(0xFFFD, 0x29);
    processor->setMemoryByte(0x2A, 0x10);

    processor->execute(4);
    processor->setMemoryByte(0x0026, 0x82);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_ADC_ABSOLUTE_TEST) {

    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x6D);
    processor->setMemoryWord(0xFFFD, 0x2843);
    processor->setMemoryByte(0x2843, 0x01);


    processor->execute(4);
    processor->setMemoryByte(0x0025, 0x00);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x6D);
    processor->setMemoryWord(0xFFFD, 0x2843);
    processor->setMemoryByte(0x2843, 0x10);

    processor->execute(4);
    processor->setMemoryByte(0x0026, 0x82);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_ADC_ABSOLUTE_X_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x7D);
    processor->setMemoryWord(0xFFFD, 0x2843);
    processor->setMemoryByte(0x2844, 0x01);

    processor->execute(4);
    processor->setMemoryByte(0x0025, 0x00);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x7D);
    processor->setMemoryWord(0xFFFD, 0x2843);
    processor->setMemoryByte(0x2844, 0x10);

    processor->execute(4);
    processor->setMemoryByte(0x0026, 0x82);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_ADC_ABSOLUTE_Y_TEST) {

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x79);
    processor->setMemoryWord(0xFFFD, 0x2843);
    processor->setMemoryByte(0x2844, 0x01);

    processor->execute(4);
    processor->setMemoryByte(0x0025, 0x00);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x79);
    processor->setMemoryWord(0xFFFD, 0x2843);
    processor->setMemoryByte(0x2844, 0x10);

    processor->execute(4);
    processor->setMemoryByte(0x0026, 0x82);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_ADC_INDEXED_INDIRECT) {

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x61);
    processor->setMemoryWord(0xFFFD, 0x42);
    processor->setMemoryWord(0x43, 0x4848);
    processor->setMemoryByte(0x4848, 0x01);

    processor->execute(6);
    processor->setMemoryByte(0x0025, 0x00);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x61);
    processor->setMemoryByte(0xFFFD, 0x42);
    processor->setMemoryWord(0x43, 0x4848);
    processor->setMemoryByte(0x4848, 0x10);

    processor->execute(6);
    processor->setMemoryByte(0x0026, 0x82);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_ADC_INDIRECT_INDEXED) {

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0xFF);
    processor->setMemoryByte(0xFFFC, 0x71);
    processor->setMemoryByte(0xFFFD, 0x42);
    processor->setMemoryWord(0x42, 0x4848);
    processor->setMemoryByte(0x4849, 0x01);

    processor->execute(5);
    processor->setMemoryByte(0x0025, 0x00);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x00);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x71);
    processor->setMemoryByte(0xFFFC, 0x71);
    processor->setMemoryByte(0xFFFD, 0x42);
    processor->setMemoryWord(0x42, 0x4848);
    processor->setMemoryByte(0x4849, 0x10);

    processor->execute(5);
    processor->setMemoryByte(0x0026, 0x82);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x82);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x8200);
}

TEST_F(ProcessorTest, INS_SBC_IMMEDIATE_TEST) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xE9);
    processor->setMemoryByte(0xFFFD, 0x02);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE9);
    processor->setMemoryByte(0xFFFD, 0x10);

    processor->execute(2);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_SBC_ZEROPAGE_TEST) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xE5);
    processor->setMemoryByte(0xFFFD, 0x03);
    processor->setMemoryByte(0x03, 0x02);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE5);
    processor->setMemoryByte(0xFFFD, 0x03);
    processor->setMemoryByte(0x03, 0x10);

    processor->execute(3);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_SBC_ZEROPAGE_X_TEST) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xF5);
    processor->setMemoryByte(0xFFFD, 0x03);
    processor->setMemoryByte(0x04, 0x02);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xF5);
    processor->setMemoryByte(0xFFFD, 0x03);
    processor->setMemoryByte(0x04, 0x10);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_SBC_ABSOLUTE_TEST) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xED);
    processor->setMemoryWord(0xFFFD, 0x4354);
    processor->setMemoryByte(0x4354, 0x02);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xED);
    processor->setMemoryWord(0xFFFD, 0x4354);
    processor->setMemoryByte(0x4354, 0x10);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_SBC_ABSOLUTE_X_TEST) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xFD);
    processor->setMemoryWord(0xFFFD, 0x4354);
    processor->setMemoryByte(0x4355, 0x02);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xFD);
    processor->setMemoryWord(0xFFFD, 0x4354);
    processor->setMemoryByte(0x4355, 0x10);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_SBC_ABSOLUTE_Y_TEST) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xF9);
    processor->setMemoryWord(0xFFFD, 0x4354);
    processor->setMemoryByte(0x4355, 0x02);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xF9);
    processor->setMemoryWord(0xFFFD, 0x4354);
    processor->setMemoryByte(0x4355, 0x10);

    processor->execute(4);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_SBC_INDEXED_INDIRECT) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xE1);
    processor->setMemoryByte(0xFFFD, 0x65);
    processor->setMemoryWord(0x66, 0x3738);
    processor->setMemoryByte(0x3738, 0x02);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE1);
    processor->setMemoryByte(0xFFFD, 0x65);
    processor->setMemoryWord(0x66, 0x3738);
    processor->setMemoryByte(0x3738, 0x10);

    processor->execute(6);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_SBC_INDIRECT_INDEXED) {

    processor->setProcessorStatusFlag('C');
    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x01);
    processor->setMemoryByte(0xFFFC, 0xF1);
    processor->setMemoryByte(0xFFFD, 0x65);
    processor->setMemoryWord(0x65, 0x3738);
    processor->setMemoryByte(0x3739, 0x02);

    processor->execute(5);

    EXPECT_EQ(processor->getRegisterValue('A'), 0xFF);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 0);

    processor->setMemoryByte(0x0025, 0xFF);

    processor->setProgramCounter(0xFFFC);

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xF1);
    processor->setMemoryByte(0xFFFD, 0x65);
    processor->setMemoryWord(0x65, 0x3738);
    processor->setMemoryByte(0x3739, 0x10);

    processor->execute(5);

    EXPECT_EQ(processor->getRegisterValue('A'), 0x71);
    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('V'), 1);

    processor->setMemoryByte(0x0026, 0x71);

    Processor::Word value = 0x0000;
    value = (value & 0x00FF) | processor->getMemory()[0x0025];
    value = value | (processor->getMemory()[0x0026] << 8);
    EXPECT_EQ(value, 0x71FF);
}

TEST_F(ProcessorTest, INS_CMP_IMMEDIATE_TEST) {

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC9);
    processor->setMemoryByte(0xFFFD, 0x80);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC9);
    processor->setMemoryByte(0xFFFD, 0x82);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC9);
    processor->setMemoryByte(0xFFFD, 0x85);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CMP_ZEROPAGE_TEST) {

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC5);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x80);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC5);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x82);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC5);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x85);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CMP_ZEROPAGE_X_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD5);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x21, 0x80);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD5);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x21, 0x82);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD5);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x21, 0x85);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CMP_ABSOLUTE_TEST) {

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xCD);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x80);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xCD);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x82);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xCD);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x85);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CMP_ABSOLUTE_X_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xDD);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2001, 0x80);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xDD);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2001, 0x82);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xDD);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2001, 0x85);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CMP_ABSOLUTE_Y_TEST) {

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD9);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2001, 0x80);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD9);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2001, 0x82);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD9);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2001, 0x85);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CMP_INDEXED_INDIRECT_TEST) {

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC1);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryWord(0x21, 0x4356);
    processor->setMemoryByte(0x4356, 0x80);

    processor->execute(6);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC1);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryWord(0x21, 0x4356);
    processor->setMemoryByte(0x4356, 0x82);

    processor->execute(6);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC1);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryWord(0x21, 0x4356);
    processor->setMemoryByte(0x4356, 0x85);

    processor->execute(6);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CMP_INDIRECT_INDEXED_TEST) {

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD1);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryWord(0x20, 0x4356);
    processor->setMemoryByte(0x4357, 0x80);

    processor->execute(5);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD1);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryWord(0x20, 0x4356);
    processor->setMemoryByte(0x4357, 0x82);

    processor->execute(5);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x01);
    processor->setRegisterValue('A', 0x82);
    processor->setMemoryByte(0xFFFC, 0xD1);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryWord(0x20, 0x4356);
    processor->setMemoryByte(0x4357, 0x85);

    processor->execute(5);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CPX_IMMEDIATE_TEST) {

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE7);
    processor->setMemoryByte(0xFFFD, 0x80);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE7);
    processor->setMemoryByte(0xFFFD, 0x82);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE7);
    processor->setMemoryByte(0xFFFD, 0x85);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CPX_ZEROPAGE_TEST) {

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE4);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x80);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE4);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x82);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xE4);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x85);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CPX_ABSOLUTE_TEST) {

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xEC);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x80);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xEC);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x82);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('X', 0x82);
    processor->setMemoryByte(0xFFFC, 0xEC);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x85);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CPY_IMMEDIATE_TEST) {

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC0);
    processor->setMemoryByte(0xFFFD, 0x80);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC0);
    processor->setMemoryByte(0xFFFD, 0x82);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC0);
    processor->setMemoryByte(0xFFFD, 0x85);

    processor->execute(2);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CPY_ZEROPAGE_TEST) {

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC4);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x80);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC4);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x82);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xC4);
    processor->setMemoryByte(0xFFFD, 0x20);
    processor->setMemoryByte(0x20, 0x85);

    processor->execute(3);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_CPY_ABSOLUTE_TEST) {

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xCC);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x80);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xCC);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x82);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 1);

    processor->resetCPU();

    processor->setRegisterValue('Y', 0x82);
    processor->setMemoryByte(0xFFFC, 0xCC);
    processor->setMemoryWord(0xFFFD, 0x2000);
    processor->setMemoryByte(0x2000, 0x85);

    processor->execute(4);

    EXPECT_EQ(processor->getProcessorStatusFlag('N'), 1);
    EXPECT_EQ(processor->getProcessorStatusFlag('Z'), 0);
    EXPECT_EQ(processor->getProcessorStatusFlag('C'), 0);
}

TEST_F(ProcessorTest, INS_JSR_TEST) {
    processor->setMemoryByte(0xFFFC, 0x20);
    processor->setMemoryWord(0xFFFD, 0x4243);

    processor->execute(6);

    EXPECT_EQ(processor->getProgramCounter(), 0x4243);
}