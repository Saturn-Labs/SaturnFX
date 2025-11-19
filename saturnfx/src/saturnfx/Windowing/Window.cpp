#include "pch.hpp"
#include "saturnfx/Windowing/Window.hpp"

#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "saturnfx/Framework.hpp"
#include "saturnfx/Eventing/Window/WindowCloseEvent.hpp"
#include "saturnfx/Graphics/Command/FunctionCommand.hpp"

namespace saturnfx::Windowing {
    Window::Window(const WindowProperties& props) :
        IEventSource(),
        m_GraphicsContext(*this),
        m_CommandQueue(*this)
    {
        GLFWmonitor* monitor = nullptr;
        bool debugContext = false;
        // Sets all glfw window hints
        glfwWindowHint(GLFW_RESIZABLE, props.resizable);
        glfwWindowHint(GLFW_VISIBLE, props.visible);
        glfwWindowHint(GLFW_DECORATED, props.decorated);
        glfwWindowHint(GLFW_FOCUSED, props.focused);
        glfwWindowHint(GLFW_AUTO_ICONIFY, props.autoIconify);
        glfwWindowHint(GLFW_FLOATING, props.floating);
        glfwWindowHint(GLFW_MAXIMIZED, props.maximized);
        glfwWindowHint(GLFW_CENTER_CURSOR, props.centerCursor);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, props.transparentFramebuffer);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, props.focusOnShow);
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, props.scaleToMonitor);
        glfwWindowHint(GLFW_RED_BITS, props.redBits);
        glfwWindowHint(GLFW_GREEN_BITS, props.greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, props.blueBits);
        glfwWindowHint(GLFW_ALPHA_BITS, props.alphaBits);
        glfwWindowHint(GLFW_DEPTH_BITS, props.depthBits);
        glfwWindowHint(GLFW_STENCIL_BITS, props.stencilBits);
        glfwWindowHint(GLFW_ACCUM_RED_BITS, props.accumRedBits);
        glfwWindowHint(GLFW_ACCUM_GREEN_BITS, props.accumGreenBits);
        glfwWindowHint(GLFW_ACCUM_BLUE_BITS, props.accumBlueBits);
        glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, props.accumAlphaBits);
        glfwWindowHint(GLFW_AUX_BUFFERS, props.auxBuffers);
        glfwWindowHint(GLFW_SAMPLES, props.samples);
        glfwWindowHint(GLFW_REFRESH_RATE, props.refreshRate);
        glfwWindowHint(GLFW_STEREO, props.stereoscopic);
        glfwWindowHint(GLFW_SRGB_CAPABLE, props.srgbCapable);
        glfwWindowHint(GLFW_DOUBLEBUFFER, props.doubleBuffer);
        glfwWindowHint(GLFW_CLIENT_API, static_cast<int>(props.clientApi));
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, static_cast<int>(props.contextCreation));
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, props.contextVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, props.contextVersionMinor);
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int>(props.contextRobustness));
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, static_cast<int>(props.contextReleaseBehavior));
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, props.forwardCompatibility);
        glfwWindowHint(GLFW_CONTEXT_DEBUG, props.debugContext);
        debugContext = props.debugContext;
        glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(props.openGLProfile));
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, props.cocoaRetinaFramebuffer);
        glfwWindowHintString(GLFW_COCOA_FRAME_NAME, props.cocoaFrameName.c_str());
        glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, props.cocoaGraphicsSwitching);
        glfwWindowHintString(GLFW_X11_CLASS_NAME, props.x11ClassName.c_str());
        glfwWindowHintString(GLFW_X11_INSTANCE_NAME, props.x11InstanceName.c_str());
        glfwWindowHint(GLFW_CONTEXT_NO_ERROR, props.contextNoError);

        m_WindowThread = std::thread([this, props, monitor] {
            m_Window = glfwCreateWindow(
                static_cast<int>(props.width),
                static_cast<int>(props.height),
                props.title.c_str(),
                monitor,
                nullptr
            );

            glfwDefaultWindowHints();
            glfwMakeContextCurrent(m_Window);
            glfwSetWindowUserPointer(m_Window, this);
            run();
        });

        m_CommandQueue.push(std::make_unique<Graphics::FunctionCommand>([=, this](auto& ctx) {
            if (debugContext) {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
                    Log::info("OpenGL Message");
                }, this);
            }
        }));
    }

    void Window::run() {
        while (!glfwWindowShouldClose(m_Window)) {
            m_CommandQueue.processAll({});
            glfwPollEvents();
        }
        triggerEvent(std::make_shared<Eventing::WindowCloseEvent>(shared_from_this()));
    }

    Window::~Window() {
        if (m_WindowThread.joinable())
            m_WindowThread.join();
        glfwDestroyWindow(m_Window);
    }

    void Window::triggerEvent(const std::shared_ptr<Eventing::IEvent>& event) {
        std::lock_guard lock(m_ListenersMutex);
        for (const auto& listener : m_Listeners) {
            listener->onEvent(event);
        }
    }

    void Window::addListener(const std::shared_ptr<Eventing::IEventListener>& listener) {
        m_Listeners.push_back(listener);
    }

    void Window::removeListener(const std::shared_ptr<Eventing::IEventListener>& listener) {
        std::erase(m_Listeners, listener);
    }

    std::string Window::getName() {
        return glfwGetWindowTitle(m_Window);
    }

    std::shared_ptr<Window> Window::create(const WindowProperties &props) {
        return std::shared_ptr<Window>(new Window(props));
    }
}
