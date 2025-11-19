#pragma once
#include <functional>

#include "saturnfx/Eventing/ITypedEventListener.hpp"
#include "saturnfx/Eventing/Event.hpp"

namespace saturnfx::Eventing {
    /**
     * @brief Represents an event listener than can accept functions.
     * @tparam TEvent The event type to listen to.
     */
    template <typename TEvent = InvalidEvent>
    requires std::is_base_of_v<IEvent, TEvent> && (!std::is_abstract_v<TEvent>)
    class FunctionalEventListener final :
        public ITypedEventListener<TEvent>
    {
        std::function<void(const std::shared_ptr<TEvent>& event)> m_Listener;

        /**
         * @brief Constructs an instance of this FunctionalEventListener with the specified function.
         * @param listener The listener function.
         */
        explicit FunctionalEventListener(const std::function<void(const std::shared_ptr<TEvent>& event)>& listener) :
            ITypedEventListener<TEvent>(),
            m_Listener(listener)
        {
        }
    public:
        FunctionalEventListener() = delete;

        void onTypedEvent(const std::shared_ptr<TEvent>& event) override {
            m_Listener(event);
        }

        /**
         * @brief Sets the internal listener function.
         * @param listener The listener function to set to.
         */
        void setListener(const std::function<void(const std::shared_ptr<TEvent>& event)>& listener) {
            m_Listener = listener;
        }

        /**
         * @brief Gets the current listener function.
         * @return The current listener function.
         */
        const std::function<void(const std::shared_ptr<TEvent>& event)>& getListener() const {
            return m_Listener;
        }

        static std::shared_ptr<FunctionalEventListener> create(const std::function<void(const std::shared_ptr<TEvent>& event)>& listenerFn) {
            return std::shared_ptr<FunctionalEventListener>(new FunctionalEventListener(listenerFn));
        }
    };
}
