#pragma once
#include <memory>

#include "saturnfx/Eventing/Window/WindowEvent.hpp"
#include "saturnfx/Eventing/EventType.hpp"
#include "saturnfx/Utils/FixedString.hpp"

namespace saturnfx::Eventing {
    class IEventSource;
    class WindowCloseEvent final :
        public WindowEvent<EventType::WindowClose, "WindowCloseEvent">
    {
    public:
        explicit WindowCloseEvent(const std::shared_ptr<IEventSource>& source) :
            WindowEvent(source)
        {
        }
    };
}
