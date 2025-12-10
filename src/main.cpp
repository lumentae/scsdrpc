#include "EventHandler.h"
#include "scssdk.h"
#include "scssdk_telemetry.h"
#include <memory>

#include "DebugConsole.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/callback_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

extern "C" {
    // ReSharper disable once CppInconsistentNaming
    SCSSDK_EXPORT SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t *const params)
    {
        if (version != SCS_TELEMETRY_VERSION_1_01)
        {
            return SCS_RESULT_unsupported;
        }

#ifdef _WIN32
        auto console = std::make_shared<DebugConsole>();
#endif

        const auto initParams = (scs_telemetry_init_params_v100_t*)(params);

        // Setup logging
        auto callbackSink = std::make_shared<spdlog::sinks::callback_sink_mt>([initParams](const spdlog::details::log_msg &msg)
            {
                // Convert the log level to the game's log level
                int logLevel = SCS_LOG_TYPE_message;
                if (msg.level == spdlog::level::warn)
                    logLevel = SCS_LOG_TYPE_warning;
                else if (msg.level == spdlog::level::err)
                    logLevel = SCS_LOG_TYPE_error;

                auto message = std::string(msg.payload.data(), msg.payload.size());

                // Send the log message to the game
                EventHandler::GetInitParams()->common.log(logLevel, ("[scsdrpc] " + message).c_str());
            });
        // @formatter:on

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        //auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("scsdrpc.log", true);
        spdlog::logger logger("scsdrpc", {consoleSink, callbackSink});
        spdlog::register_logger(std::make_shared<spdlog::logger>(logger));
        spdlog::set_default_logger(std::make_shared<spdlog::logger>(logger));

        EventHandler::Initialize(initParams);

        spdlog::info("Initialized successfully!");
        return SCS_RESULT_ok;
    }

    // ReSharper disable once CppInconsistentNaming
    SCSSDK_EXPORT SCSAPI_VOID scs_telemetry_shutdown()
    {
    }
}

#ifdef _WIN32
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return TRUE;
}
#elif defined(__linux__)
__attribute__((constructor)) static void init()
{
}
#endif