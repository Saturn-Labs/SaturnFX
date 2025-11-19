#pragma once
#include <memory>

namespace saturnfx::Eventing {
    class IEvent;
    class IEventListener;
    class IEventSource {
    public:
        virtual ~IEventSource() = default;
        virtual void triggerEvent(const std::shared_ptr<IEvent>& event) = 0;
        virtual void addListener(const std::shared_ptr<IEventListener>& listener) = 0;
        virtual void removeListener(const std::shared_ptr<IEventListener>& listener) = 0;
        virtual std::string getName() = 0;
    };
}
