#pragma once
#include "GLFW/glfw3.h"

namespace saturnfx::Windowing {
    enum class ContextReleaseBehavior {
        None = GLFW_RELEASE_BEHAVIOR_NONE,
        Any = GLFW_ANY_RELEASE_BEHAVIOR,
        Flush = GLFW_RELEASE_BEHAVIOR_FLUSH
    };
}