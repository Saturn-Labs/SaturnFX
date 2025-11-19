#pragma once
#include <string>

#include "saturnfx/Eventing/IEvent.hpp"
#include "saturnfx/Eventing/EventType.hpp"
#include "saturnfx/Utils/FixedString.hpp"

namespace saturnfx::Eventing {
    /**
     * @brief Represents a base event class that other event classes can inherit from.
     * @tparam Type The type of the event.
     * @tparam Name The name of the event.
     */
    template<EventType Type, FixedString Name>
    class Event :
        public IEvent
    {
    protected:
        std::weak_ptr<IEventSource> m_Source = {};

        explicit Event(const std::shared_ptr<IEventSource>& source) :
            m_Source(source)
        {
        }

    public:
        EventType getType() const override {
            return getStaticType();
        }

        std::string getName() const override {
            return getStaticName();
        }

        bool isHandled() const override {
            return false;
        }

        void setHandled() override {}

        IEventSource* getSource() const override {
            const auto ptr = m_Source.lock();
            return ptr ? ptr.get() : nullptr;
        }

        constexpr static std::string getStaticName() {
            return Name.data;
        }

        constexpr static EventType getStaticType() {
            return Type;
        }
    };

    class InvalidEvent final :
        public Event<EventType::Invalid, "InvalidEvent">
    {
    public:
        explicit InvalidEvent(const std::shared_ptr<IEventSource>& source) :
            Event(source)
        {
        }
    };
}
