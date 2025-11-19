#pragma once
#include <string>

#include "GLFW/glfw3.h"
#include "saturnfx/Windowing/ClientAPI.hpp"
#include "saturnfx/Windowing/ContextCreationAPI.hpp"
#include "saturnfx/Windowing/ContextReleaseBehavior.hpp"
#include "saturnfx/Windowing/ContextRobustness.hpp"
#include "saturnfx/Windowing/OpenGLProfile.hpp"

namespace saturnfx::Windowing {
    struct WindowProperties {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool shouldVSync = true;
        GLFWmonitor* monitor = nullptr;
        bool resizable = true;
        bool visible = true;
        bool decorated = true;
        bool focused = true;
        bool autoIconify = true;
        bool floating = false;
        bool maximized = false;
        bool centerCursor = true;
        bool transparentFramebuffer = false;
        bool focusOnShow = true;
        bool scaleToMonitor = false;
        int redBits = 8;
        int greenBits = 8;
        int blueBits = 8;
        int alphaBits = 8;
        int depthBits = 24;
        int stencilBits = 8;
        int accumRedBits = 0;
        int accumGreenBits = 0;
        int accumBlueBits = 0;
        int accumAlphaBits = 0;
        int auxBuffers = 0;
        int samples = 0;
        int refreshRate = -1;
        bool stereoscopic = false;
        bool srgbCapable = false;
        bool doubleBuffer = true;
        ClientAPI clientApi = ClientAPI::OpenGL;
        ContextCreationAPI contextCreation = ContextCreationAPI::NativeContext;
        int contextVersionMajor = 1;
        int contextVersionMinor = 0;
        ContextRobustness contextRobustness = ContextRobustness::NoRobustness;
        ContextReleaseBehavior contextReleaseBehavior = ContextReleaseBehavior::Any;
        bool forwardCompatibility = false;
#ifdef DEBUG_BUILD
        bool debugContext = true;
#else
        bool debugContext = false;
#endif
        OpenGLProfile openGLProfile = OpenGLProfile::Any;
        bool cocoaRetinaFramebuffer = true;
        std::string cocoaFrameName;
        bool cocoaGraphicsSwitching = false;
        std::string x11ClassName;
        std::string x11InstanceName;
        bool contextNoError = false;
    };
}
