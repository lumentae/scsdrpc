#include "DiscordRichPresence.h"

#include <cmath>

#include "EventHandler.h"
#include "spdlog/spdlog.h"

static constexpr discord::ClientId APPLICATION_ID = 1402418075726254102;

DiscordRichPresence::DiscordRichPresence() : m_discordCore(nullptr) {}
DiscordRichPresence::~DiscordRichPresence() {
    delete m_discordCore;
}

void DiscordRichPresence::Initialize()
{
    const auto discordCreateResult = discord::Core::Create(
        APPLICATION_ID, DiscordCreateFlags_NoRequireDiscord, &m_discordCore
    );

    if (discordCreateResult != discord::Result::Ok) {
        spdlog::error("Discord init failed with result: {}", static_cast<int>(discordCreateResult));
        m_discordCore = nullptr;
        return;
    }

    m_activity.SetType(discord::ActivityType::Playing);
    m_activity.SetName(EventHandler::GetInitParams()->common.game_name);
    m_activity.SetState("In menu");
    m_activity.SetDetails("No active job...");
    m_activity.GetTimestamps().SetStart(std::time(nullptr));
    m_activity.GetAssets().SetLargeImage("https://cdn.discordapp.com/app-icons/1402418075726254102/46bfdfc58e4eacbfde29b2461e118e78.png");

    StartThread();
    spdlog::info("Discord initialized successfully!");
}

void DiscordRichPresence::Update()
{
    if (!m_discordCore)
        return;

    auto& telemetry = EventHandler::GetTelemetry();
    if (telemetry.doingJob)
    {
        m_activity.SetDetails(std::format("{} -> {} | {} {}", telemetry.sourceCityName, telemetry.destinationCityName, telemetry.truckBrand, telemetry.truckName).c_str());
        m_activity.SetState(std::format("{} km/h - {} km total distance", std::round(telemetry.speed * 3.6), telemetry.plannedDistanceKm).c_str());
    }
    else
    {
        m_activity.SetDetails("In menu");
        m_activity.SetState("No active job...");
    }

    m_discordCore->RunCallbacks();
    m_discordCore->ActivityManager().UpdateActivity(
        m_activity, [](discord::Result result) {
            if (result != discord::Result::Ok)
                spdlog::info("Activity Manager push completed with result: {}", static_cast<int>(result));
        }
    );
}

void DiscordRichPresence::StartThread() {
    m_running = true;
    m_thread = std::thread([this] {
        while (m_running) {
            GetInstance().Update();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}

void DiscordRichPresence::StopThread() {
    spdlog::info("Stopping thread...");
    m_running = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}
