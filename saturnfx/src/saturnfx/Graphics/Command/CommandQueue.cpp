#include "pch.hpp"
#include "saturnfx/Graphics/Command/CommandQueue.hpp"
#include "saturnfx/Graphics/Command/ICommand.hpp"

namespace saturnfx::Graphics {
    CommandQueue::CommandQueue(Windowing::Window& window) :
        m_Window(&window)
    {
    }

    ICommand& CommandQueue::push(std::unique_ptr<ICommand>&& command) {
        std::lock_guard lock(m_QueueMutex);
        m_Commands.push(std::move(command));
        return *m_Commands.front();
    }

    void CommandQueue::processAll(const CommandContext& ctx) {
        while (true) {
            std::unique_ptr<ICommand> cmd;
            {
                std::lock_guard lock(m_QueueMutex);
                if (m_Commands.empty()) break;
                cmd = std::move(m_Commands.front());
                m_Commands.pop();
            }
            if (cmd)
                cmd->execute(ctx);
        }
    }

    size_t CommandQueue::size() {
        std::lock_guard lock(m_QueueMutex);
        return m_Commands.size();
    }

    void CommandQueue::clear() {
        std::lock_guard lock(m_QueueMutex);
        while (!m_Commands.empty())
            m_Commands.pop();
    }
}
