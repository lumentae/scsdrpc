#include "EventHandler.h"
#include "scssdk.h"
#include "scssdk_telemetry.h"
#include "windows.h"

extern "C" {
    // ReSharper disable once CppInconsistentNaming
    __declspec(dllexport) SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t *const params)
    {
        if (version != SCS_TELEMETRY_VERSION_1_01)
        {
            return SCS_RESULT_unsupported;
        }

        const auto initParams = (scs_telemetry_init_params_v100_t*)(params);
        EventHandler::Initialize(initParams);
        return SCS_RESULT_ok;
    }

    // ReSharper disable once CppInconsistentNaming
    __declspec(dllexport) SCSAPI_VOID scs_telemetry_shutdown()
    {
    }
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return TRUE;
}