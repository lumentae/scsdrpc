#pragma once
#include <atomic>
#include <thread>

#include "core.h"

class DiscordRichPresence
{
public:
    DiscordRichPresence();
    ~DiscordRichPresence();
    void Initialize();
    void Update() const;
    void StartThread();
    void StopThread();

    static DiscordRichPresence& GetInstance()
    {
        static DiscordRichPresence instance{};
        return instance;
    }

    discord::Activity m_activity{};

private:
    discord::Core* m_discordCore;

    std::atomic<bool> m_running{false};
    std::thread m_thread;
};
