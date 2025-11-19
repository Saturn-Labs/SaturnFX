#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <format>
#include <memory>
#include <mutex>
#include <string>

#if defined(_MSC_VER)
#define SATFX_BREAKPOINT() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#include <signal.h>
#define SATFX_BREAKPOINT() raise(SIGTRAP)
#else
#error "Platform not supported for SATFX_BREAKPOINT"
#endif

namespace saturnfx {
    /**
     * @struct LogOptions
     * Logger configuration.
     */
    struct LogOptions {
        std::string name = "saturnfx";
    };

    /**
     * @class Log
     * @brief Singleton logging system for SaturnFX framework.
     *
     * Provides thread-safe initialization and shutdown, colored console logging,
     * cross-platform debug break support, and formatted message templates.
     */
    class Log {
        static std::shared_ptr<spdlog::logger> s_ConsoleLogger;
        static std::mutex s_InitMutex;

    public:
        /**
         * @brief Trigger a platform-specific debug break.
         */
        inline static void debugBreak() { SATFX_BREAKPOINT(); }

        /**
         * @brief Initialize the logger.
         * @param options Configuration options (e.g., logger name).
         * @note Thread-safe; safe to call multiple times.
         */
        static void init(const LogOptions& options = {});

        /**
         * @brief Shutdown the logger and release resources. Thread-safe.
         */
        static void shutdown();

        /**
         * @brief Log a trace message.
         */
        static void trace(const std::string& message);

        /**
         * @brief Log an info message.
         */
        static void info(const std::string& message);

        /**
         * @brief Log a warning message.
         */
        static void warn(const std::string& message);

        /**
         * @brief Log an error message.
         */
        static void error(const std::string& message);

        /**
         * @brief Log a debug message.
         * Basically a trace but only in Debug mode
         */
        static void debug(const std::string& message);

        /**
         * @brief Trigger an assertion failure if condition is false.
         * @param condition The condition to check.
         * @param message Message to log if assertion fails.
         */
        static void assertFail(bool condition, const std::string& message);

        /**
         * @brief Trigger an unconditional assertion failure.
         * @param message Message to log before breaking.
         */
        static void assertFail(const std::string& message);

        // ===============================
        // Template formatting overloads
        // ===============================

        /**
         * @brief Log a trace message using a format string and arguments.
         * @tparam Args Format argument types.
         * @param fmt Format string.
         * @param args Arguments to format.
         */
        template<typename... Args>
        static void trace(std::format_string<Args...> fmt, Args&&... args) {
            trace(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Log an info message using a format string and arguments.
         * @tparam Args Format argument types.
         * @param fmt Format string.
         * @param args Arguments to format.
         */
        template<typename... Args>
        static void info(std::format_string<Args...> fmt, Args&&... args) {
            info(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Log a warning message using a format string and arguments.
         * @tparam Args Format argument types.
         * @param fmt Format string.
         * @param args Arguments to format.
         */
        template<typename... Args>
        static void warn(std::format_string<Args...> fmt, Args&&... args) {
            warn(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Log an error message using a format string and arguments.
         * @tparam Args Format argument types.
         * @param fmt Format string.
         * @param args Arguments to format.
         */
        template<typename... Args>
        static void error(std::format_string<Args...> fmt, Args&&... args) {
            error(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Log a debug message using a format string and arguments.
         * @tparam Args Format argument types.
         * @param fmt Format string.
         * @param args Arguments to format.
         */
        template<typename... Args>
        static void debug(std::format_string<Args...> fmt, Args&&... args) {
            debug(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Trigger an unconditional assertion failure using a format string.
         * @tparam Args Format argument types.
         * @param fmt Format string.
         * @param args Arguments to format.
         */
        template<typename... Args>
        static void assertFail(std::format_string<Args...> fmt, Args&&... args) {
            assertFail(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Trigger an assertion failure using a format string if condition is false.
         * @tparam Args Format argument types.
         * @param condition The condition to check.
         * @param fmt Format string.
         * @param args Arguments to format.
         */
        template<typename... Args>
        static void assertFail(bool condition, std::format_string<Args...> fmt, Args&&... args) {
            assertFail(condition, std::format(fmt, std::forward<Args>(args)...));
        }
    };

/**
 * @brief Assert macro that automatically includes file and line info.
 *
 * Example:
 * SATFX_ASSERT(x > 0, "Value must be positive, got {}", x);
 */
#define SATFX_ASSERT(cond, msg, ...) \
    saturnfx::Log::assertFail(cond, std::format("[{}:{}] " msg, __FILE__, __LINE__, ##__VA_ARGS__))
} // namespace saturnfx
