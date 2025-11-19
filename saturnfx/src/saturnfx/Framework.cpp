#include "pch.hpp"
#include "saturnfx/Framework.hpp"

#include "saturnfx/Debugging/Log.hpp"

namespace saturnfx {
    std::unique_ptr<Framework> Framework::s_Instance = nullptr;
    std::mutex Framework::s_InitMutex;

    Framework::Framework(const FrameworkOptions& options) {
        Log::init(options.logOptions);
        Log::trace("Initializing saturnfx::Framework...");
        m_EventSystem = Eventing::EventSystem::create();
    }

    Framework::~Framework() {
        Log::shutdown();
    }

    Eventing::EventSystem& Framework::getEventSystem() const {
        if (!m_EventSystem)
            Log::assertFail("Failed to get main event system because it was nullptr!");
        return *m_EventSystem;
    }

    void Framework::init(const FrameworkOptions& options) {
        std::lock_guard lock(s_InitMutex);
        if (s_Instance) {
            Log::init(options.logOptions);
            Log::assertFail("Can't initialize saturnfx::Framework. Instance already initialized, please use Framework::instance(...).");
        }
        s_Instance = std::unique_ptr<Framework>(new Framework(options));
    }

    Framework& Framework::instance() {
        std::lock_guard lock(s_InitMutex);
        if (!s_Instance) {
            Log::init();
            Log::assertFail("saturnfx::Framework wasn't initialized, are you sure you called Framework::init(...)?");
        }
        return *s_Instance;
    }

    void Framework::shutdown() {
        std::lock_guard lock(s_InitMutex);
        s_Instance.reset();
    }
}
