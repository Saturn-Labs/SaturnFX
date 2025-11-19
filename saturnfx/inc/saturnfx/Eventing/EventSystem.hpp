#pragma once
#include <condition_variable>
#include <queue>
#include <thread>

#include "saturnfx/Eventing/IEventListener.hpp"
#include "saturnfx/Eventing/IEventSource.hpp"

namespace saturnfx::Eventing {
    /**
     * Represents a EventSystem that listens to events from IEventSource(s)
     * enqueues them and processes/dispatches them in its own "EVENTING THREAD" thread.
     */
    class EventSystem final :
        public IEventListener,
        public IEventSource
    {
        std::mutex m_QueueMutex;
        std::thread m_QueueThread;
        std::condition_variable m_QueueCondition;
        std::queue<std::shared_ptr<IEvent>> m_Queue;
        std::vector<std::shared_ptr<IEventListener>> m_Listeners;
        std::string m_ThreadName;
        bool m_Running = true;

        static uint32_t s_ThreadCounter;

        EventSystem();

    public:
        ~EventSystem() override;

        EventSystem(const EventSystem&) = delete;
        EventSystem(EventSystem&&) = delete;
        EventSystem& operator=(const EventSystem&) = delete;
        EventSystem& operator=(EventSystem&&) = delete;

        void run();

        void onEvent(const std::shared_ptr<IEvent>& event) override;
        void triggerEvent(const std::shared_ptr<IEvent>& event) override;
        void addListener(const std::shared_ptr<IEventListener>& listener) override;
        void removeListener(const std::shared_ptr<IEventListener>& listener) override;
        std::string getName() override;

        template<typename... Args>
        static std::shared_ptr<EventSystem> create(Args&&... args) {
            auto shared = std::shared_ptr<EventSystem>(new EventSystem(std::forward<Args>(args)...));
            return shared;
        }
    };
}
