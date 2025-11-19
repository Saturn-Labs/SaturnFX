#pragma once
#include <memory>

namespace saturnfx::Windowing {
    class Window;
}

namespace saturnfx::Graphics {
    class GraphicsContext {
        friend class Windowing::Window;
        Windowing::Window& m_Window;

        explicit GraphicsContext(Windowing::Window& window);
    public:
        ~GraphicsContext() = default;
    };
}
