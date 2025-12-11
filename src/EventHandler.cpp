#include "EventHandler.h"

#include <cassert>
#include <cstring>
#include <common/scssdk_telemetry_common_configs.h>
#include <common/scssdk_telemetry_truck_common_channels.h>

#include "DiscordRichPresence.h"
#include "spdlog/spdlog.h"

void storeSpeed(const scs_string_t, const scs_u32_t, const scs_value_t *const value, const scs_context_t context)
{
    assert(context);
    *static_cast<float *>(context) = value->value_float.value;
}

void EventHandler::Initialize(const scs_telemetry_init_params_v100_t* initParams)
{
    m_initParams = *initParams;

    spdlog::info("Registering telemetry channels");
    m_initParams.register_for_event(SCS_TELEMETRY_EVENT_configuration, TelemetryConfiguration, nullptr);
    m_initParams.register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_speed, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, storeSpeed, &m_telemetry.speed);
    m_initParams.register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_navigation_distance, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, storeSpeed, &m_telemetry.navigationDistance);
}

void EventHandler::TelemetryConfiguration(const scs_event_t, const void* const event_info, const scs_context_t)
{
    const auto* const info = static_cast<const scs_telemetry_configuration_t *>(event_info);
    if (strcmp(info->id, SCS_TELEMETRY_CONFIG_job) == 0)
    {
        for (auto attr = info->attributes; attr->name; ++attr) {
            m_telemetry.doingJob = true;
            if (strcmp(attr->name, SCS_TELEMETRY_CONFIG_ATTRIBUTE_source_city) == 0)
                m_telemetry.sourceCityName = std::string(attr->value.value_string.value);
            else if (strcmp(attr->name, SCS_TELEMETRY_CONFIG_ATTRIBUTE_destination_city) == 0)
                m_telemetry.destinationCityName = std::string(attr->value.value_string.value);
            else if (strcmp(attr->name, SCS_TELEMETRY_CONFIG_ATTRIBUTE_planned_distance_km) == 0)
                m_telemetry.plannedDistanceKm = attr->value.value_u32.value;
        }
    }
    else if (strcmp(info->id, SCS_TELEMETRY_CONFIG_truck) == 0)
    {
        for (auto attr = info->attributes; attr->name; ++attr) {
            if (strcmp(attr->name, SCS_TELEMETRY_CONFIG_ATTRIBUTE_brand) == 0)
                m_telemetry.truckBrand = std::string(attr->value.value_string.value);
            if (strcmp(attr->name, SCS_TELEMETRY_CONFIG_ATTRIBUTE_name) == 0)
                m_telemetry.truckName = std::string(attr->value.value_string.value);
        }
    }
}

scs_telemetry_init_params_v100_t EventHandler::m_initParams{};
EventHandler::Telemetry EventHandler::m_telemetry{};