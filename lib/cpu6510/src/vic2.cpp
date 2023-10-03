#include "memory.h"
#include "vic2.h"

#define ASSERT(x) (!(x)) ? __builtin_trap() : (void)(0);
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__));

static void GLClearError() {
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {
    while(GLenum error = glGetError()) {
        printf("[OpenGL Error] (%d) \n File: %s, Function: %s, Line: %i \n", error, file, function, line);
        return false;
    }
    return true;
}

const char* Shaders::vertexShader = "#version 330 core\n"
                                    "layout(location=0) in vec4 position;\n"
                                    "\n"
                                    "out vec2 TexCoord;\n"
                                    "\n"
                                    "void main()\n"
                                    "{\n"
                                    "gl_Position = position;\n"
                                    "TexCoord = vec2((position.x + 1.0) / 2.0, float(1 - ((position.y + 1.0) / 2.0)));\n"
                                    "}";

const char* Shaders::fragmentShaderBitmap = "#version 330 core\n"
                                      "#extension GL_ARB_separate_shader_objects : enable\n"
                                      "layout(location=0) out vec4 color;\n"
                                      "void main()\n"
                                      "{\n"
                                      "     color = vec4(0.0, 0.0, 1.0, 1.0);\n"
                                      "}";

const char* Shaders::fragmentShaderText = "#version 330 core\n"
                                          "#extension GL_ARB_separate_shader_objects : enable\n"
                                          "uniform sampler2D u_CharacterTexture;\n"
                                          "\n"
                                          "layout(location=0) out vec4 color;\n"
                                          "in vec2 TexCoord;\n"
                                          "vec4 textureColor;\n"
                                          "\n"
                                          "void main()\n"
                                          "{\n"
                                          "    textureColor = vec4(texture(u_CharacterTexture, TexCoord).rrr, 1.0);\n"
                                          "    if(textureColor.r == 0.0) {\n"
                                          "       color = vec4(0.094, 0.094, 0.694, 1.0);\n"
                                          "       return;\n"
                                          "    }\n"
                                          "    color = textureColor;\n"
                                          "}";


unsigned int Processor::Vic2::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        printf("Failed to compile %s shader\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        printf("%s\n", message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Processor::Vic2::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

Processor::Vic2::Vic2(Byte *memory) {

    screenMemoryPtr = memory+0x0400;
    baseAddressPtr = memory+0xD000;
    characterGeneratorPtr = memory+0xD100;

    xResolution = 320;
    yResolution = 200;

    aspectRatio = (float)xResolution/(float)yResolution;
    std::fill(translatedCharacters, translatedCharacters+0x40, 0xFF);
    std::fill(translatedCharacters+0x40, translatedCharacters+0xFA00, 0x00);
}

void Processor::Vic2::showWindow() {

    if(!glfwInit()) {
        throw std::runtime_error("GLFW failed to initialize\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = glfwCreateWindow(xResolution, yResolution, "Commodore64", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!window) {
        glfwTerminate();
        throw std::runtime_error("GLFW window failed to create\n");
    }

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        throw std::runtime_error("Cannot initialize glew\n");
    }

    program_text = createShader(Shaders::vertexShader, Shaders::fragmentShaderText);

    float positions[] = {
            -1.0f, -1.0f,
            1.0f, -1.0f,
            1.0f, 1.0f,
            -1.0f, 1.0f,
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), indices, GL_STATIC_DRAW);

    GLCall(glUseProgram(program_text));

    unsigned int textureID;
    GLCall(glGenTextures(1, &textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 40*8, 25*8, 0, GL_RED, GL_UNSIGNED_BYTE, translatedCharacters));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));

    int location = glGetUniformLocation(program_text, "u_CharacterTexture");
    GLCall(glUniform1i(location, 0));

    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));

    glfwSetWindowAspectRatio(window, xResolution, yResolution);
    glfwSetWindowSizeLimits(window, xResolution, yResolution, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int windowWidth, int windowHeight) {
        glViewport(0, 0, windowWidth, windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    });

    while(!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        translateCharactersFromScreenMemory();
        GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 40*8, 25*8, GL_RED, GL_UNSIGNED_BYTE, translatedCharacters));

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Processor::Vic2::translateCharactersFromScreenMemory() {
    int width = 40 * 8;
    int height = 25 * 8;

    Byte byteOfChar;
    int charIndex;

    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 40; col++) {
            charIndex = row * 40 + col;

            for (int y = 0; y < 8; ++y) {
                byteOfChar = characterGeneratorPtr[screenMemoryPtr[charIndex] * 8 + y];

                for (int x = 0; x < 8; x++) {
                    int destIndex = (row * 8 + y) * width + (col * 8 + x);
                    translatedCharacters[destIndex] = ((byteOfChar >> (7 - x)) & 1) * 0xFF;
                }
            }
        }
    }
}

Processor::Vic2::~Vic2() {
    glfwTerminate();
}