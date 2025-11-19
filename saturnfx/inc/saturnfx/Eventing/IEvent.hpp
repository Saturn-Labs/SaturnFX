#pragma once
#include <string>

#include "EventType.hpp"

namespace saturnfx::Eventing {
    /**
     * @brief Represents a basic interface class that all events inherit from.
     */
    class IEvent {
    public:
        virtual ~IEvent() = default;

        /**
         * @brief Gets the EventType of this event instance.
         * @return The EventType of this event instance.
         */
        virtual EventType getType() const = 0;

        /**
         * @brief Gets the name of this event instance.
         * @return The name of this event instance.
         */
        virtual std::string getName() const = 0;

        /**
         * @brief Checks if the event was handled.
         * @return Returns true if the event was handled, false if it wasn't.
         */
        virtual bool isHandled() const = 0;

        /**
         * @brief Marks this event as handled, can't be undone.
         */
        virtual void setHandled() = 0;

        /**
         * @brief Gets the source that triggered this event.
         * @returns The source that triggered this event.
         */
        virtual IEventSource* getSource() const = 0;
    };
}
