#include <iostream>
#include <ostream>

#include "pch.hpp"
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "saturnfx/Framework.hpp"

#include "saturnfx/Debugging/Log.hpp"
#include "saturnfx/Eventing/FunctionalEventListener.hpp"
#include "saturnfx/Windowing/Window.hpp"

using namespace saturnfx;

int main() {
    Framework::init({});
    const auto& framework = Framework::instance();

    if (!glfwInit())
        return -1;

    auto window = Windowing::Window::create({
        .title = "Hello Window",
        .width = 640,
        .height = 480,
    });

    std::cin.get();
    return 0;
}
