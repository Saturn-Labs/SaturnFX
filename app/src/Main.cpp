#include <iostream>
#include <ostream>

#include "pch.hpp"
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "saturnfx/Framework.hpp"

#include "saturnfx/Debugging/Log.hpp"
#include "saturnfx/Eventing/FunctionalEventListener.hpp"
#include "saturnfx/Eventing/Window/WindowCloseEvent.hpp"

using namespace saturnfx;

int main() {
    Framework::init({});
    const auto& framework = Framework::instance();

    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
        return -1;



    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
