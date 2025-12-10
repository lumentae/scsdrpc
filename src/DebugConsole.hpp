#pragma once

#if _DEBUG && defined(_WIN32)
#include <io.h>

class DebugConsole
{
public:
    DebugConsole();
    ~DebugConsole();

    void StartRedirecting();

private:
    void StopRedirecting();

    int m_OriginalStdin;
    int m_OriginalStdout;
    int m_OriginalStderr;

    bool m_Redirected;
};
#endif
