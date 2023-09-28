//
// Created by ignacy on 27.09.23.
//

#ifndef PROCESSOR_EMULATOR_MEMORY_H
#define PROCESSOR_EMULATOR_MEMORY_H

#include <algorithm>
#include <stdexcept>
#include <cstdint>

#define MEM_ZEROPAGE_START 0x0000
#define MEM_ZEROPAGE_END 0x00FF

#define MEM_STACK_START 0x0100
#define MEM_STACK_END 0x01FF

#define MEM_OS_AND_BASIC_POINTERS_START 0x0200
#define MEM_OS_AND_BASIC_POINTERS_END 0x03FF

#define MEM_SCREEN_START 0x0400
#define MEM_SCREEN_END 0x07FF

#define MEM_FREE_BASIC_PROGRAM_STORAGE_AREA_START 0x0800
#define MEM_FREE_BASIC_PROGRAM_STORAGE_AREA_END 0x9FFF

#define MEM_FREE_MACHINE_LANGUAGE_PROGRAM_STORAGE_AREA_1_START 0xA000
#define MEM_FREE_MACHINE_LANGUAGE_PROGRAM_STORAGE_AREA_1_END 0xBFFF

#define MEM_FREE_MACHINE_LANGUAGE_PROGRAM_STORAGE_AREA_2_START 0xC000
#define MEM_FREE_MACHINE_LANGUAGE_PROGRAM_STORAGE_AREA_2_END 0xCFFF

#define MEM_INTERFACE_EXTENSION_START 0xDE00
#define MEM_INTERFACE_EXTENSION_END 0xDFFF

#define MEM_FREE_MACHINE_LANGUAGE_PROGRAM_STORAGE_AREA_3_START 0xE000
#define MEM_FREE_MACHINE_LANGUAGE_PROGRAM_STORAGE_AREA_3_END 0xFFFF

#define MAX_MEMORY (1024*64)

namespace Processor {

    typedef uint8_t Byte;
    typedef uint16_t Word;
    typedef uint32_t Dword;

    class Processor;

    typedef void (Processor::*InstructionFunction)(Dword &, const Dword &);

    struct Memory {
        Byte data[MAX_MEMORY];

        void initialize();
        Byte &operator[](Word address);
    };
}

#endif
