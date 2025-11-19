#pragma once
#include <memory>
#include <queue>
#include <vector>

#include "CommandContext.hpp"

namespace saturnfx::Windowing {
    class Window;
}

namespace saturnfx::Graphics {
    class ICommand;
    class CommandQueue {
        friend class Windowing::Window;
        Windowing::Window* m_Window;
        std::queue<std::unique_ptr<ICommand>> m_Commands;
        std::mutex m_QueueMutex;

        explicit CommandQueue(Windowing::Window& window);
    public:
        CommandQueue() = delete;
        CommandQueue(const CommandQueue&) = delete;
        CommandQueue& operator=(const CommandQueue&) = delete;
        CommandQueue(CommandQueue&&) = delete;
        CommandQueue& operator=(CommandQueue&&) = delete;
        ~CommandQueue() = default;

        ICommand& push(std::unique_ptr<ICommand>&& command);
        void processAll(const CommandContext& ctx);
        size_t size();
        void clear();
    };
}
