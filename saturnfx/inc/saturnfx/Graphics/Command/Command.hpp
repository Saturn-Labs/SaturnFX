#pragma once
#include <string>

#include "saturnfx/Graphics/Command/ICommand.hpp"
#include "saturnfx/Graphics/Command/CommandType.hpp"
#include "saturnfx/Utils/FixedString.hpp"

namespace saturnfx::Graphics {
    template<CommandType Type, FixedString Name>
    class Command :
        public ICommand
    {
    public:
        CommandType getType() const override {
            return getStaticType();
        }

        std::string getName() const override {
            return getStaticName();
        }

        constexpr static std::string getStaticName() {
            return Name.data;
        }

        constexpr static CommandType getStaticType() {
            return Type;
        }
    };
}
