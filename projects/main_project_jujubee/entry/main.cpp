#include "main_project_jujubee/dependencies/pch/pch.hpp"

namespace juju_global {
    juju::window_logger* wl_sys_logger = new juju::window_logger;

    std::thread* wl_thread_p = new std::thread;


    juju::juju_codes log_system_message(const juju::string& message) {
       return wl_sys_logger->send_message(message);
    }

    juju::juju_codes start_logger() {
        *wl_thread_p = std::thread(&juju::window_logger::go, wl_sys_logger);

        wl_sys_logger->wait_until_init();

        return juju::juju_codes::success;
    }

    juju::juju_codes close_logger() {
        if (wl_thread_p->joinable()) {
            wl_thread_p->join();
        }

        // clean up
        if (wl_thread_p != nullptr) {
            delete wl_thread_p;
        }

        if (wl_sys_logger != nullptr) {
            delete wl_sys_logger;
        }

        return juju::juju_codes::success;
    }
}




#ifndef ENTRY_TEST

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    juju_global::start_logger();


    juju::window* main_window = new juju::window;
    main_window->go();

    if (main_window != nullptr) {
        delete main_window;
    }
    

    juju_global::close_logger();

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
