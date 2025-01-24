#include "main_project_exe_jujubee/pch/pch.hpp"

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    // Placeholder logic for demonstration
    MessageBox(nullptr, L"Hello from wWinMain!", L"Message", MB_OK);

    // Return a Win32 API-specific return code (e.g., 0 for success)
    return 0;
}

int main() {
    // Prepare arguments for wWinMain
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    HINSTANCE hPrevInstance = nullptr;
    LPWSTR lpCmdLine = GetCommandLineW();
    int nShowCmd = SW_SHOW;

    // Call wWinMain
    return wWinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}
