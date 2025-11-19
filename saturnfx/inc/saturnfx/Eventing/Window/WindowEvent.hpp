#pragma once
#include "saturnfx/Eventing/ConsumableEvent.hpp"
#include "saturnfx/Eventing/EventType.hpp"
#include "saturnfx/Utils/FixedString.hpp"

namespace saturnfx::Eventing {
    /**
     * @brief Represents a base window event class that other window event classes can inherit from.
     * @tparam Type The type of the window event.
     * @tparam Name The name of the window event.
     */
    template<EventType Type, FixedString Name>
    class WindowEvent :
        public ConsumableEvent<Type, Name>
    {
    public:
        explicit WindowEvent(const std::shared_ptr<IEventSource>& source) :
            ConsumableEvent<Type, Name>(source)
        {
        }
    };
}
