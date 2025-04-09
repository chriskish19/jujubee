#include NAMES_INCLUDE
#include PCH_INCLUDE_PATH


#ifndef ENTRY_TEST

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    juju_api::start_jfs();
    juju_api::start_logger();
    {
        juju::juju_codes code = juju_api::log_system_message(ROS("juju system logger initialized..."));
        juju::output_code(code);
    }


    juju::window* main_window = new juju::window;
    {
        juju::juju_codes code = juju_api::log_system_message(ROS("main window created."));
        juju::output_code(code);
    }


    try {
        juju::juju_codes code = juju_api::log_system_message(ROS("main window go..."));
        juju::output_code(code);
        main_window->go();
    }
    catch (const juju::jujubee_error& e) {
        juju::juju_codes code = juju_api::log_system_message(e.full_message());
        juju::output_code(code);
        e.vs_output_full_message();
    }
    

    if (main_window != nullptr) {
        delete main_window;
        main_window = nullptr;
    }
    
    {
        juju::juju_codes code = juju_api::log_system_message(ROS("main window closed..."));
        juju::output_code(code);
    }

    juju_api::close_logger();
    juju_api::close_jfs();

    return static_cast<int>(juju::juju_codes::success);

}



#else // USE TEST ENTRY POINT

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    jt::slow_test_logging(100,1);

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
