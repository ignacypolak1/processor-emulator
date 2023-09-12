#ifndef PROCESSOR_EMULATOR_PROCESSOR_H
#define PROCESSOR_EMULATOR_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <map>

namespace Processor {

    typedef uint8_t Byte;
    typedef uint16_t Word;

    class Processor {
    private:
        Word program_counter; // Program Counter
        Word stack_register; // Stack Register

        std::map<char, Byte> registers = { // Registers
                {'A', 0},
                {'X', 0},
                {'Y', 0}
        };

        std::map<char, bool> processor_status = { // Processor Status Register
                {'C', false},
                {'Z', false},
                {'I', false},
                {'D', false},
                {'B', false},
                {'V', false},
                {'N', false}
        };
    public:
        Processor();
        ~Processor();

        Word getProgramCounter() const;
        Word getStackRegister() const;
        Byte getRegisterValue(const char&) const;
        bool getProcessorStatus(const char&) const;

        void setProgramCounter(const Word&);
        void setStackRegister(const Word&);
        void setRegisterValue(const char&, const Byte&);
        void setProcessorStatus(const char&, const bool&);
    };
}

#endif //PROCESSOR_EMULATOR_PROCESSOR_H