#pragma once
#include "GLFW/glfw3.h"

namespace saturnfx::Windowing {
    enum class OpenGLProfile {
        Core = GLFW_OPENGL_CORE_PROFILE,
        Compatibility = GLFW_OPENGL_COMPAT_PROFILE,
        Any = GLFW_OPENGL_ANY_PROFILE
    };
}