#include "pch.hpp"
#include "saturnfx/Graphics/Command/FunctionCommand.hpp"

namespace saturnfx::Graphics {
    FunctionCommand::FunctionCommand(const FunctionType& command) :
        m_Command(command)
    {
    }

    void FunctionCommand::setCommand(const FunctionType& command) {
        m_Command = command;
    }

    const FunctionCommand::FunctionType& FunctionCommand::getCommand() const {
        return m_Command;
    }

    CommandReturn FunctionCommand::execute(const CommandContext &context) {
        if (m_Command)
            return m_Command(context);
        return CommandReturn();
    }
}
