#ifndef PROCESSOR_EMULATOR_VIC2_H
#define PROCESSOR_EMULATOR_VIC2_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>

namespace Shaders {
    extern const char* vertexShader;
    extern const char* fragmentShader;
}

namespace Processor {

    class Vic2 {
    friend Processor;
    private:
        unsigned int VBO;
        unsigned int IBO;
        Byte* screenMemoryPtr;
        GLFWwindow* window;

    public:
        Vic2(Byte*);
        ~Vic2();

        void showWindow();

    };
}
#endif
