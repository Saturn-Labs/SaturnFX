#pragma once
#include <memory>

namespace saturnfx::Eventing {
    class IEvent;

    /**
     * @brief Represents an interface that can listen to events.
     */
    class IEventListener {
    public:
        virtual ~IEventListener() = default;

        /**
         * @brief Called when any event is triggered.
         * @param event The event that triggered this onEvent(...) function.
         */
        virtual void onEvent(const std::shared_ptr<IEvent>& event) = 0;
    };
}
