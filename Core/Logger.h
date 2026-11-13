#pragma once

namespace ViewPoint
{
    void ResetLogFile();
    void LogMessage(const char* message);

    void LogNumber(const char* label, long long value);
    void LogNumber(const char* label, unsigned long long value);
    void LogNumber(const char* label, double value);
    void LogNumber(const char* label, float value);
}
