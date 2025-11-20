#include "pch.hpp"
#include "saturnfx/Debugging/Log.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace saturnfx {
    SharedMutex Log::sMutex = {};
    LogProperties Log::sProps = {};
    Ref<spdlog::logger> Log::sLogger = nullptr;
    bool Log::sFailedInit = false;

    void Log::write(const LogSeverity severity, const String& message) {
        Ref<spdlog::logger> loggerCopy;
        bool logInitialized = false;

        {
            SharedLock read(sMutex);
            loggerCopy = sLogger;
            logInitialized = sFailedInit || loggerCopy != nullptr;
        }

        if (!logInitialized)
            ensureInit();

        if (!loggerCopy) {
            SharedLock read(sMutex);
            loggerCopy = sLogger;
        }

        switch (severity) {
            case LogSeverity::Debug:
#ifdef DEBUG
                loggerCopy->debug(message);
#endif
                break;
            case LogSeverity::Trace:
                loggerCopy->trace(message);
                break;
            case LogSeverity::Info:
                loggerCopy->info(message);
                break;
            case LogSeverity::Warning:
                loggerCopy->warn(message);
                break;
            case LogSeverity::Error:
                loggerCopy->error(message);
                break;
            case LogSeverity::Critical:
                loggerCopy->critical(message);
                std::terminate();
        }
    }

    void Log::debug(const String& message) {
        write(LogSeverity::Debug, message);
    }

    void Log::trace(const String& message) {
        write(LogSeverity::Trace, message);
    }

    void Log::info(const String& message) {
        write(LogSeverity::Info, message);
    }

    void Log::warning(const String& message) {
        write(LogSeverity::Warning, message);
    }

    void Log::error(const String& message) {
        write(LogSeverity::Error, message);
    }

    void Log::critical(const String& message) {
        write(LogSeverity::Critical, message);
    }

    void Log::debugBreak() {
#ifdef DEBUG
        DEBUG_BREAK();
#else
        std::terminate();
#endif
    }

    void Log::assertFail(const String& message) {
        error(message);
        debugBreak();
        std::unreachable();
    }

    void Log::setProperties(const LogProperties& props) {
        sProps = props;
        shutdownInternal();
        ensureInit();
    }

    bool Log::ensureInit() {
        UniqueLock lock(sMutex);
        try {
            initInternal();
            return true;
        }
        catch (...) {
            sLogger = spdlog::default_logger();
            sFailedInit = true;

            sLogger->info("Failed to initialize logging system.");
            sLogger->info("Using fallback!");
            return false;
        }
    }

    void Log::initInternal() {
        if (sLogger)
            return;

        Vector<spdlog::sink_ptr> sinks;

        const auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_level(spdlog::level::trace);
        consoleSink->set_pattern("%^[%T] [%l] %v%$");
        sinks.push_back(consoleSink);

        if (!sProps.LogFile.empty()) {
            const auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(sProps.LogFile, true);
            fileSink->set_level(spdlog::level::trace);
            sinks.push_back(fileSink);
        }

        for (const auto& s : sProps.AdditionalSinks)
            sinks.push_back(s);

        sLogger = std::make_shared<spdlog::logger>(sProps.Name, sinks.begin(), sinks.end());
        sLogger->set_level(spdlog::level::trace);
        sLogger->flush_on(spdlog::level::err);

        spdlog::register_logger(sLogger);
        spdlog::set_default_logger(sLogger);
    }

    void Log::shutdownInternal() {
        UniqueLock lock(sMutex);

        if (!sLogger) {
            sFailedInit = false;
            return;
        }

        try {
            sLogger->flush();
            spdlog::drop(sProps.Name);
            sLogger.reset();
            sFailedInit = false;
        }
        catch (...) {
            // This should never really fail, but hey, safety.
            sLogger.reset();
            sFailedInit = false;
        }
    }
}
