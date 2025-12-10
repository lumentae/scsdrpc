#include "EventHandler.h"

#include <cassert>
#include <cstring>
#include <common/scssdk_telemetry_common_configs.h>

#include "spdlog/spdlog.h"

void EventHandler::Initialize(scs_telemetry_init_params_v100_t* initParams)
{
    m_initParams = *initParams;

    spdlog::info("Registering telemetry channels");
    m_initParams.register_for_event(SCS_TELEMETRY_EVENT_configuration, TelemetryConfiguration, nullptr);
}

void EventHandler::TelemetryConfiguration(const scs_event_t, const void* const event_info, const scs_context_t)
{
    spdlog::info("Telemetry configuration called");
    const auto* const info = static_cast<const scs_telemetry_configuration_t *>(event_info);
    spdlog::info("Telemetry configuration: {}", info->id);
    if (strcmp(info->id, SCS_TELEMETRY_CONFIG_job) == 0)
    {
        spdlog::info("Job configuration found");
        for (auto attr = info->attributes; attr->name; ++attr) {
            spdlog::info("Attribute: {}", attr->name);
            switch (attr->value.type) {
                case SCS_VALUE_TYPE_bool: {
                    spdlog::info("Bool value: {}", attr->value.value_bool.value ? "true" : "false");
                    break;
                }
                case SCS_VALUE_TYPE_u32: {
                    spdlog::info("U32 value: {}", attr->value.value_u32.value);
                    break;
                }
                case SCS_VALUE_TYPE_s32: {
                    spdlog::info("S32 value: {}", attr->value.value_s32.value);
                    break;
                }
                case SCS_VALUE_TYPE_u64: {
                    spdlog::info("U64 value: {}", attr->value.value_u64.value);
                    break;
                }
                case SCS_VALUE_TYPE_float: {
                    spdlog::info("Float value: {}", attr->value.value_float.value);
                    break;
                }
                case SCS_VALUE_TYPE_double: {
                    spdlog::info("Double value: {}", attr->value.value_double.value);
                    break;
                }
                case SCS_VALUE_TYPE_fvector: {
                    spdlog::info("FVector value: ({},{},{})", attr->value.value_fvector.x, attr->value.value_fvector.y, attr->value.value_fvector.z);
                    break;
                }
                case SCS_VALUE_TYPE_dvector: {
                    spdlog::info("DVector value: ({},{},{})", attr->value.value_dvector.x, attr->value.value_dvector.y, attr->value.value_dvector.z);
                    break;
                }
                case SCS_VALUE_TYPE_euler: {
                    spdlog::info("Euler value: ({},{},{})", attr->value.value_euler.heading, attr->value.value_euler.pitch, attr->value.value_euler.roll);
                    break;
                }
                case SCS_VALUE_TYPE_fplacement: {
                    spdlog::info("FPlacement value: ({},{},{})", attr->value.value_fplacement.position.x, attr->value.value_fplacement.position.y, attr->value.value_fplacement.position.z);
                    break;
                }
                case SCS_VALUE_TYPE_dplacement: {
                    spdlog::info("DPlacement value: ({},{},{})", attr->value.value_dplacement.position.x, attr->value.value_dplacement.position.y, attr->value.value_dplacement.position.z);
                    break;
                }
                case SCS_VALUE_TYPE_string: {
                    spdlog::info("String value: {}", attr->value.value_string.value);
                    break;
                }
                case SCS_VALUE_TYPE_s64: {
                    spdlog::info("S64 value: {}", attr->value.value_s64.value);
                    break;
                }
                default:
                    spdlog::warn("Unhandled attribute type: {}", attr->value.type);
                    break;
            }
        }
    }
}

scs_telemetry_init_params_v100_t EventHandler::m_initParams{};
EventHandler::Telemetry EventHandler::m_telemetry{};