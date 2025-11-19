#pragma once
#include <memory>

#include "saturnfx/Debugging/Log.hpp"
#include "saturnfx/Eventing/EventSystem.hpp"

namespace saturnfx {
    /**
     * @struct FrameworkOptions
     * @brief Configuration options for initializing the framework.
     */
    struct FrameworkOptions {
        LogOptions logOptions;
    };


    /**
     * @class Framework
     * @brief Core singleton class for the SaturnFX framework.
     *
     * Handles initialization, shutdown, and global subsystems (like logging).
     * Only one instance exists at a time.
     */
    class Framework {
    private:
        static std::unique_ptr<Framework> s_Instance;
        static std::mutex s_InitMutex;

        std::shared_ptr<Eventing::EventSystem> m_EventSystem = nullptr;

        /**
         * @brief Private constructor called by init().
         * @param options Initialization options.
         */
        explicit Framework(const FrameworkOptions& options);

    public:
        Framework(const Framework&) = delete;
        Framework& operator=(const Framework&) = delete;
        Framework(Framework&&) = delete;
        Framework& operator=(Framework&&) = delete;
        ~Framework();

        /**
         * @brief Gets the main event system.
         * @return The main event system.
         */
        Eventing::EventSystem& getEventSystem() const;

        /**
         * @brief Initialize the framework singleton.
         * @param options Initialization options.
         * @note Thread-safe. Safe to call multiple times.
         */
        static void init(const FrameworkOptions& options);

        /**
         * @brief Get the singleton instance of the framework.
         * @return Reference to the framework instance.
         * Asserts If init() was not called.
         */
        static Framework& instance();

        /**
         * @brief Shutdown the framework and release resources.
         * @note Thread-safe.
         */
        static void shutdown();
    };
}
