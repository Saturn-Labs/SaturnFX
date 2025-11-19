#pragma once
#include <memory>

namespace saturnfx::Windowing {
    class Window;
}

namespace saturnfx::Graphics {
    class GraphicsContext {
        std::weak_ptr<Windowing::Window> m_Window;

        explicit GraphicsContext(const std::shared_ptr<Windowing::Window>& window);
    public:
        ~GraphicsContext();
    };
}
