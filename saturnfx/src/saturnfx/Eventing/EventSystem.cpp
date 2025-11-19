#include "pch.hpp"
#include "saturnfx/Eventing/EventSystem.hpp"

#include "saturnfx/Debugging/Log.hpp"

namespace saturnfx::Eventing {
    uint32_t EventSystem::s_ThreadCounter = 0;

    EventSystem::EventSystem() : m_Running(true) {
        uint32_t id = s_ThreadCounter++;
        m_ThreadName = std::format("EVENTING THREAD #{}", id);
        m_QueueThread = std::thread([this] {
            run();
        });

        Log::debug("Created EventSystem with {}", m_ThreadName);
    }

    EventSystem::~EventSystem() {
        {
            std::unique_lock lock(m_QueueMutex);
            m_Running = false;
        }
        m_QueueCondition.notify_all();

        if (m_QueueThread.joinable())
            m_QueueThread.join();

        Log::debug("EventSystem destroyed and thread joined");
    }

    void EventSystem::run() {
        while (true) {
            std::shared_ptr<IEvent> evt;

            {
                std::unique_lock lock(m_QueueMutex);
                m_QueueCondition.wait(lock, [this] {
                    return !m_Queue.empty() || !m_Running;
                });

                if (!m_Running && m_Queue.empty())
                    break;

                if (!m_Queue.empty()) {
                    evt = m_Queue.front();
                    m_Queue.pop();
                }
            }

            if (evt)
                triggerEvent(evt);
        }
    }

    void EventSystem::onEvent(const std::shared_ptr<IEvent>& event) {
        std::unique_lock lock(m_QueueMutex);
        m_Queue.push(event);
        m_QueueCondition.notify_one();
    }

    void EventSystem::triggerEvent(const std::shared_ptr<IEvent>& event) {
        for (const auto& listener : m_Listeners) {
            listener->onEvent(event);
        }
    }

    void EventSystem::addListener(const std::shared_ptr<IEventListener>& listener) {
        m_Listeners.push_back(listener);
    }

    void EventSystem::removeListener(const std::shared_ptr<IEventListener>& listener) {
        std::erase(m_Listeners, listener);
    }

    std::string EventSystem::getName() {
        return std::format("EventSystem[{}]", m_ThreadName);
    }
}
