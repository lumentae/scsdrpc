#include "DebugConsole.hpp"

#if _DEBUG && defined(_WIN32)
#include <cstdio>
#include <windows.h>

DebugConsole::DebugConsole() :
        m_Redirected(false)
{
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("Debug Console");

    StartRedirecting();
}

DebugConsole::~DebugConsole()
{
    StopRedirecting();
    FreeConsole();
}

void DebugConsole::StartRedirecting()
{
    if (m_Redirected)
        StopRedirecting();

    m_Redirected = true;

    m_OriginalStdin = _dup(0);
    m_OriginalStdout = _dup(1);
    m_OriginalStderr = _dup(2);

    FILE *s_Con;
    freopen_s(&s_Con, "CONIN$", "r", stdin);
    freopen_s(&s_Con, "CONOUT$", "w", stderr);
    freopen_s(&s_Con, "CONOUT$", "w", stdout);

    SetConsoleOutputCP(CP_UTF8);
}

void DebugConsole::StopRedirecting()
{
    if (!m_Redirected)
        return;

    m_Redirected = false;

    _dup2(m_OriginalStdin, 0);
    _dup2(m_OriginalStdout, 1);
    _dup2(m_OriginalStderr, 2);
}
#endif