#pragma once
#include <thread>

#include "GLFW/glfw3.h"
#include "saturnfx/Eventing/IEventSource.hpp"
#include "saturnfx/Graphics/GraphicsContext.hpp"
#include "saturnfx/Graphics/Command/CommandQueue.hpp"
#include "saturnfx/Windowing/WindowProperties.hpp"

namespace saturnfx::Windowing {
    class Window :
        public Eventing::IEventSource
    {
        GLFWwindow* m_Window = nullptr;
        std::thread m_WindowThread;
        Graphics::GraphicsContext m_GraphicsContext;
        Graphics::CommandQueue m_CommandQueue;

        explicit Window(const WindowProperties& props);
        void run();

    public:
        ~Window() override;

        std::shared_ptr<Window> create(const WindowProperties& props);
    };
}
