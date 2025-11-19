#pragma once
#include <cstddef>

namespace saturnfx {
    template<std::size_t N>
    struct FixedString {
        char data[N]{};

        constexpr FixedString(const char (&str)[N]) {
            for (std::size_t i = 0; i < N; ++i)
                data[i] = str[i];
        }

        constexpr operator const char*() const { return data; }
        constexpr std::size_t size() const { return N - 1; } // exclude null terminator
    };
}
