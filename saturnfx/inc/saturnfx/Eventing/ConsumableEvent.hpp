#pragma once
#include "Event.hpp"
#include "EventType.hpp"
#include "saturnfx/Utils/FixedString.hpp"

namespace saturnfx::Eventing {
    /**
     * @brief Represents a consumable event class that other event classes can inherit from.
     * @tparam Type The type of the event.
     * @tparam Name The name of the event.
     */
    template<EventType Type, FixedString Name>
    class ConsumableEvent :
        public Event<Type, Name>
    {
        bool m_Handled = false;
    public:
        explicit ConsumableEvent(const std::shared_ptr<IEventSource>& source) :
            Event<Type, Name>(source)
        {
        }

        bool isHandled() const override {
            return m_Handled;
        }

        void setHandled() override {
            m_Handled = true;
        }
    };
}
