#pragma once
#include "GLFW/glfw3.h"

namespace saturnfx::Windowing {
    enum class ContextRobustness {
        NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
        LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET,
        NoRobustness = GLFW_NO_ROBUSTNESS
    };
}