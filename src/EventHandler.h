#pragma once
#include <scssdk_telemetry.h>

class EventHandler
{
public:
    struct Telemetry
    {
        scs_string_t sourceCityName;
        scs_string_t destinationCityName;
    };

    static void Initialize(scs_telemetry_init_params_v100_t* initParams);

    static Telemetry GetTelemetry()
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