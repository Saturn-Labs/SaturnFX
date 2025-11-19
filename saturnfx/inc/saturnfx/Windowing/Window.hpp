#pragma once
#include <thread>

#include "GLFW/glfw3.h"
#include "saturnfx/Eventing/IEventSource.hpp"
#include "saturnfx/Graphics/GraphicsContext.hpp"
#include "saturnfx/Graphics/Command/CommandQueue.hpp"
#include "saturnfx/Windowing/WindowProperties.hpp"

namespace saturnfx::Eventing {
    class IEventListener;
}

namespace saturnfx::Windowing {
    class Window final :
        public Eventing::IEventSource,
        public std::enable_shared_from_this<Window>
    {
        GLFWwindow* m_Window = nullptr;
        std::thread m_WindowThread;
        Graphics::GraphicsContext m_GraphicsContext;
        Graphics::CommandQueue m_CommandQueue;

        std::mutex m_ListenersMutex;
        std::vector<std::shared_ptr<Eventing::IEventListener>> m_Listeners;

        explicit Window(const WindowProperties& props);
        void run();

    public:
        ~Window() override;
        virtual void triggerEvent(const std::shared_ptr<Eventing::IEvent>& event);
        virtual void addListener(const std::shared_ptr<Eventing::IEventListener>& listener);
        virtual void removeListener(const std::shared_ptr<Eventing::IEventListener>& listener);
        virtual std::string getName();

        static std::shared_ptr<Window> create(const WindowProperties& props);
    };
}
