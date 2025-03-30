#include "main_project_jujubee/dependencies/pch/pch.hpp"

#ifndef ENTRY_TEST

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    juju::window* main_window = new juju::window;
    main_window->go();

    if (main_window != nullptr) {
        delete main_window;
    }
    

    return static_cast<int>(juju::juju_codes::success);
}



#else // USE TEST ENTRY POINT

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    juju::slow_test_logging(100,1);

    return static_cast<int>(juju::juju_codes::success);
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

#endif
