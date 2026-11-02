#include <Windows.h>

extern "C" __declspec(dllexport) int ModInit()
{
    MessageBoxA(
        nullptr,
        "MyNativeMod DLL loaded successfully!",
        "REPENTOGON Native Plugin Test",
        MB_OK | MB_ICONINFORMATION
    );

    return 0;
}
