#pragma once

namespace ViewPoint
{
    void ResetLogFile();
    void LogMessage(const char* message);
    void LogNumber(const char* label, unsigned long long value);
}
