#pragma once
#include <scssdk_telemetry.h>
#include <string>

class EventHandler
{
public:
    struct Telemetry
    {
        bool doingJob = false;
        float speed{};
        int navigationDistance{};
        std::string destinationCityName{};
        std::string sourceCityName{};
        std::string truckBrand{};
        std::string truckName{};
        scs_u32_t plannedDistanceKm;
    };

    static void Initialize(const scs_telemetry_init_params_v100_t* initParams);

    static Telemetry& GetTelemetry()
    {
        return m_telemetry;
    }

    static scs_telemetry_init_params_v100_t* GetInitParams()
    {
        return &m_initParams;
    }

private:
    static void TelemetryConfiguration(scs_event_t event, const void* event_info, scs_context_t context);

    static scs_telemetry_init_params_v100_t m_initParams;
    static Telemetry m_telemetry;
};
