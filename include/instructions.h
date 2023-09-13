#ifndef PROCESSOR_EMULATOR_INSTRUCTIONS_H
#define PROCESSOR_EMULATOR_INSTRUCTIONS_H

static constexpr Processor::Byte INS_LDA_IMMEDIATE = 0xA9;
static constexpr Processor::Byte INS_LDA_ABSOLUTE = 0xAD;
static constexpr Processor::Byte INS_LDA_ABSOLUTE_X = 0xBD;
static constexpr Processor::Byte INS_LDA_ABSSOLUTE_Y = 0xB9;
static constexpr Processor::Byte INS_LDA_ZEROPAGE = 0xA5;
static constexpr Processor::Byte INS_LDA_ZEROPAGE_X = 0xB5;
static constexpr Processor::Byte INS_LDA_INDEXED_INDIRECT = 0xA1;
static constexpr Processor::Byte INS_LDA_INDIRECT_INDEXED = 0xB1;

#endif

