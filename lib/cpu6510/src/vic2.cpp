#include "memory.h"
#include "vic2.h"
//0x07FF end of buffer

Processor::Vic2::Vic2(Byte *memory) {
    screenMemoryPtr = memory+0x0400;
}

void Processor::Vic2::showWindow() {

    if(!glfwInit()) {
        throw std::runtime_error("GLFW failed to initialize\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = glfwCreateWindow(320, 200, "Commodore64", NULL, NULL);

    if(!window) {
        glfwTerminate();
        throw std::runtime_error("GLFW window failed to create\n");
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        throw std::runtime_error("Cannot initialize glew\n");
    }

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

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(float), indices, GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

Processor::Vic2::~Vic2() {
    glfwTerminate();
}