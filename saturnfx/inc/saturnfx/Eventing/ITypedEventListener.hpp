#pragma once
#include <type_traits>

#include "saturnfx/Eventing/Event.hpp"
#include "saturnfx/Eventing/IEventListener.hpp"

namespace saturnfx::Eventing {
    /**
     * @brief Represents an interface that can listen to a specific event.
     * @tparam TEvent The event type to listen to.
     */
    template <typename TEvent = InvalidEvent>
    requires std::is_base_of_v<IEvent, TEvent> && (!std::is_abstract_v<TEvent>)
    class ITypedEventListener :
        public IEventListener
    {
    public:
        void onEvent(const std::shared_ptr<IEvent>& event) override {
            if (TEvent::getStaticType() != event->getType())
                return;
            onTypedEvent(std::dynamic_pointer_cast<TEvent>(event));
        }

        /**
         * @brief Called when the event of type TEvent is triggered.
         * @param event The event that triggered this onTypedEvent(...) function.
         */
        virtual void onTypedEvent(const std::shared_ptr<TEvent>& event) = 0;
    };
}
