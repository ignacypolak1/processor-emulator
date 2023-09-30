#ifndef PROCESSOR_EMULATOR_VIC2_H
#define PROCESSOR_EMULATOR_VIC2_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>

namespace Shaders {
    extern const char* vertexShader;
    extern const char* fragmentShaderBitmap;
    extern const char* fragmentShaderText;
}

namespace Processor {

    class Vic2 {
    private:

        int xResolution;
        int yResolution;
        float aspectRatio;

        unsigned int VBO;
        unsigned int IBO;

        unsigned int program_bitmap;
        unsigned int program_text;

        Byte* screenMemoryPtr;
        GLFWwindow* window;

        unsigned int compileShader(unsigned int, const std::string&);

    public:
        Vic2(Byte*);
        ~Vic2();

        unsigned int createShader(const std::string&, const std::string&);
        void showWindow();

    };
}
#endif
