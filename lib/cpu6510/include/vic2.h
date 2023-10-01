#ifndef PROCESSOR_EMULATOR_VIC2_H
#define PROCESSOR_EMULATOR_VIC2_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#define VIC_M0X_OFFSET 0x0000
#define VIC_M0Y_OFFSET 0x0001
#define VIC_M1X_OFFSET 0x0002
#define VIC_M1Y_OFFSET 0x0003
#define VIC_M2X_OFFSET 0x0004
#define VIC_M2Y_OFFSET 0x0005
#define VIC_M3X_OFFSET 0x0006
#define VIC_M3Y_OFFSET 0x0007
#define VIC_M4X_OFFSET 0x0008
#define VIC_M4Y_OFFSET 0x0009
#define VIC_M5X_OFFSET 0x000A
#define VIC_M5Y_OFFSET 0x000B
#define VIC_M6X_OFFSET 0x000C
#define VIC_M6Y_OFFSET 0x000D
#define VIC_M7X_OFFSET 0x000E
#define VIC_M7Y_OFFSET 0x000F
#define VIC_MSB_X_OFFSET 0x0010
#define VIC_CONTROL_1_OFFSET 0x0011
#define VIC_RASTER_OFFSET 0x0012
#define VIC_LIGHT_PEN_X_OFFSET 0x0013
#define VIC_LIGHT_PEN_Y_OFFSET 0x0014
#define VIC_SPRITE_ENABLE_OFFSET 0x0015
#define VIC_CONTROL_2_OFFSET 0x0016
#define VIC_SPRITE_Y_EXPAND_OFFSET 0x0017
#define VIC_MEMORY_POINTERS_OFFSET 0x0018
#define VIC_INTERRUPT_REGISTER_OFFSET 0x0019
#define VIC_INTERRUPT_ENABLE_OFFSET 0x001A
#define VIC_SPRITE_PRIORITY_OFFSET 0x001B
#define VIC_SPRITE_MULTICOLOR_OFFSET 0x001C
#define VIC_SPRITE_X_EXPAND_OFFSET 0x001D
#define VIC_SPRITE_COLLISION_OFFSET 0x001E
#define VIC_SPRITE_DATA_COLISION_OFFSET 0x001F
#define VIC_BORDER_COLOR_OFFSET 0x0020
#define VIC_BACKGROUND_COLOR_0_OFFSET 0x0021
#define VIC_BACKGROUND_COLOR_1_OFFSET 0x0022
#define VIC_BACKGROUND_COLOR_2_OFFSET 0x0023
#define VIC_BACKGROUND_COLOR_3_OFFSET 0x0024
#define VIC_SPRITE_MULTICOLOR_0_OFFSET 0x0025
#define VIC_SPRITE_MULTICOLOR_1_OFFSET 0x0026
#define VIC_SPRITE_COLOR_0_OFFSET 0x0027
#define VIC_SPRITE_COLOR_1_OFFSET 0x0028
#define VIC_SPRITE_COLOR_2_OFFSET 0x0029
#define VIC_SPRITE_COLOR_3_OFFSET 0x002A
#define VIC_SPRITE_COLOR_4_OFFSET 0x002B
#define VIC_SPRITE_COLOR_5_OFFSET 0x002C
#define VIC_SPRITE_COLOR_6_OFFSET 0x002D
#define VIC_SPRITE_COLOR_7_OFFSET 0x002E

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
        Byte* baseAddressPtr;
        Byte* characterGeneratorPtr;
        Byte translatedCharacters[40*8*25*8];

        GLFWwindow* window;

        unsigned int compileShader(unsigned int, const std::string&);
        unsigned int createShader(const std::string&, const std::string&);
        void translateCharactersFromScreenMemory();

    public:
        Vic2(Byte*);
        ~Vic2();

        void showWindow();


    };
}
#endif
