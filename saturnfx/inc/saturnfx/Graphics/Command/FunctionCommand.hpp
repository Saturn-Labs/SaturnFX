#pragma once
#include <functional>

#include "CommandContext.hpp"
#include "saturnfx/Graphics/Command/Command.hpp"

namespace saturnfx::Graphics {
    class FunctionCommand :
        public Command<CommandType::FunctionCommand, "FunctionCommand">
    {
        using FunctionType = std::function<CommandReturn(const CommandContext&)>;
        FunctionType m_Command;
    public:
        FunctionCommand() = delete;
        explicit FunctionCommand(const FunctionType& command);

        void setCommand(const FunctionType& command);
        const FunctionType& getCommand() const;
        CommandReturn execute(const CommandContext& context) override;
    };
}
