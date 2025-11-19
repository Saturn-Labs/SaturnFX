#include "pch.hpp"
#include "saturnfx/Debugging/Log.hpp"
#include <utility>

namespace saturnfx {
    std::shared_ptr<spdlog::logger> Log::s_ConsoleLogger = nullptr;
    std::mutex Log::s_InitMutex;

    void Log::init(const LogOptions& options) {
        std::lock_guard lock(s_InitMutex);
        if (s_ConsoleLogger)
            return;
        s_ConsoleLogger = spdlog::stdout_color_mt(options.name);
        s_ConsoleLogger->set_pattern("%^[%T] [%l] %v%$");
        spdlog::set_level(spdlog::level::trace);
    }

    void Log::trace(const std::string& message) {
        s_ConsoleLogger->trace(message);
    }

    void Log::info(const std::string& message) {
        s_ConsoleLogger->info(message);
    }

    void Log::warn(const std::string& message) {
        s_ConsoleLogger->warn(message);
    }

    void Log::error(const std::string& message) {
        s_ConsoleLogger->error(message);
    }

    void Log::debug(const std::string& message) {
#ifdef DEBUG
        trace(message);
#endif
    }

    void Log::assertFail(const bool condition, const std::string& message) {
        if (!condition) {
            error(message);
#ifdef DEBUG
            debugBreak();
#endif
        }
    }

    void Log::assertFail(const std::string& message) {
        error(message);
#ifdef DEBUG
        debugBreak();
        std::unreachable();
#endif
    }

    void Log::shutdown() {
        std::lock_guard lock(s_InitMutex);
        if (!s_ConsoleLogger)
            return;
        s_ConsoleLogger.reset();
        spdlog::shutdown();
    }
}
