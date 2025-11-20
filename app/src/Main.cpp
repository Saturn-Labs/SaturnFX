#include "pch.hpp"
#include "saturnfx/Debugging/Log.hpp"

using namespace saturnfx;

int main() {
    Log::debug("Test debug {}", 0);
    Log::trace("Test trace {}", 0);
    Log::info("Test info {}", 0);
    Log::warning("Test warning {}", 0);
    Log::error("Test error {}", 0);
    Log::assertFail("Assert {}", 0);
    return 0;
}
