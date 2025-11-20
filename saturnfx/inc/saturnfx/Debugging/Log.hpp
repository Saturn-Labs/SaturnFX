#pragma once
#include "saturnfx/Utils/Types.hpp"
#include "spdlog/common.h"
#include "spdlog/logger.h"

#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
    #if defined(__APPLE__)
        // macOS likes the built-in one
        #define DEBUG_BREAK() __builtin_debugtrap()
    #else
        #define DEBUG_BREAK() __builtin_trap()
    #endif
#else
    #include <signal.h>
    #define DEBUG_BREAK() raise(SIGTRAP)
#endif


namespace saturnfx {
    enum class LogSeverity {
        Debug,
        Trace,
        Info,
        Warning,
        Error,
        Critical
    };

    struct LogProperties {
        String Name = "SaturnFX";
        String LogFile = "logs/saturnfx.log";
        Vector<spdlog::sink_ptr> AdditionalSinks = {};
    };

    class Log {
        static SharedMutex sMutex;
        static LogProperties sProps;
        static Ref<spdlog::logger> sLogger;
        static bool sFailedInit;
    public:
        Log() = delete;
        ~Log() = delete;
        Log(const Log&) = delete;
        Log(Log&&) = delete;
        Log& operator=(const Log&) = delete;
        Log& operator=(Log&&) = delete;

        static void write(LogSeverity severity, const String& message);
        static void debug(const String& message);
        static void trace(const String& message);
        static void info(const String& message);
        static void warning(const String& message);
        static void error(const String& message);
        static void critical(const String& message);
        static void debugBreak();
        static void assertFail(const String& message);
        static void setProperties(const LogProperties& props);

        template<typename... Args>
        static void debug(std::format_string<Args...> fmt, Args&&... args) {
            debug(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void trace(std::format_string<Args...> fmt, Args&&... args) {
            trace(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void info(std::format_string<Args...> fmt, Args&&... args) {
            info(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void warning(std::format_string<Args...> fmt, Args&&... args) {
            warning(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void error(std::format_string<Args...> fmt, Args&&... args) {
            error(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void critical(std::format_string<Args...> fmt, Args&&... args) {
            critical(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void assertFail(std::format_string<Args...> fmt, Args&&... args) {
            assertFail(std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        static void assertFail(const bool condition, std::format_string<Args...> fmt, Args&&... args) {
            if (!condition) {
                assertFail(std::format(fmt, std::forward<Args>(args)...));
            }
        }

    private:
        static bool ensureInit();
        static void initInternal();
        static void shutdownInternal();
    };
}
