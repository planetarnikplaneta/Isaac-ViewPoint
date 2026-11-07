#include "Logger.h"

#include <Windows.h>
#include <cstdio>

namespace
{
    constexpr const char* LOG_FILE = "C:\\IsaacViewPoint.log";
}

namespace ViewPoint
{
    void ResetLogFile()
    {
        FILE* file = nullptr;

        fopen_s(&file, LOG_FILE, "w");

        if (file)
        {
            fclose(file);
        }
    }

    void LogMessage(const char* message)
    {
        FILE* file = nullptr;

        fopen_s(&file, LOG_FILE, "a");

        if (file)
        {
            fprintf(file, "%s\n", message ? message : "");
            fclose(file);
        }

        OutputDebugStringA(message ? message : "");
        OutputDebugStringA("\n");
    }

    void LogNumber(const char* label, unsigned long long value)
    {
        char buffer[256];

        sprintf_s(
            buffer,
            "%s: %llu",
            label ? label : "",
            value
        );

        LogMessage(buffer);
    }
}
