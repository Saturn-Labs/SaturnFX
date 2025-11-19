#pragma once
#include "CommandType.hpp"

namespace saturnfx::Graphics {
    struct CommandContext;
    using CommandReturn = void;
    class ICommand {
    public:
        virtual ~ICommand() = default;
        virtual CommandType getType() const = 0;
        virtual std::string getName() const = 0;
        virtual CommandReturn execute(const CommandContext& ctx) = 0;
    };
}
