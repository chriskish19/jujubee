#include NAMES_INCLUDE
#include PCH_INCLUDE_PATH



namespace juju_global {
    juju::window_logger* wl_sys_logger = new juju::window_logger;

    std::thread* wl_thread_p = new std::thread;



    juju::juju_codes log_system_std_exception(const std::exception& e) {
#if WIDE
        juju::string what = juju_api::to_wide_string(e.what());
#elif NARROW
        juju::string what = e.what();
#endif
        what = ROS("standard exception thrown: ") + what;
        
        return wl_sys_logger->send_message(what);
    }



    juju::juju_codes log_system_std_file_exception(const std::filesystem::filesystem_error& e) {
        try {
#if WIDE
            juju::string what = juju_api::to_wide_string(e.what());
#elif NARROW
            juju::string what = e.what()
#endif
            juju::string p1 = e.path1().c_str();
            juju::string p2 = e.path2().c_str();

            auto message = std::format(ROS("filesystem error: {} '\n' path1: {} '\n' path2: {}"), what, p1, p2);
            return wl_sys_logger->send_message(message);
        }
        catch (const std::format_error& e) {
            std::cerr << "std::format error: " << e.what() << std::endl;
        }
        catch (const std::bad_alloc& e) {
            std::cerr << "memory allocation error: " << e.what() << std::endl;
        }
        catch (const juju::jujubee_error& e) {
            e.vs_output_full_message();
        }
        return juju::juju_codes::exception_thrown;
    }

    juju::juju_codes log_system_message(const char* message) {
#if WIDE
        try {
            juju::string wide_message = juju_api::to_wide_string(message);
            return wl_sys_logger->send_message(wide_message);
        }
        catch (const juju::jujubee_error& e) {
            e.vs_output_full_message();
        }
        return juju::juju_codes::exception_thrown;
#elif NARROW
        return wl_sys_logger->send_message(message);
#endif
    }

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
            wl_thread_p = nullptr;
        }

        if (wl_sys_logger != nullptr) {
            delete wl_sys_logger;
            wl_sys_logger = nullptr;
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
    {
        juju::juju_codes code = juju_global::log_system_message(ROS("juju system logger initialized..."));
        juju::output_code(code);
    }


    juju::window* main_window = new juju::window;
    {
        juju::juju_codes code = juju_global::log_system_message(ROS("main window created."));
        juju::output_code(code);
    }


    try {
        juju::juju_codes code = juju_global::log_system_message(ROS("main window go..."));
        juju::output_code(code);
        main_window->go();
    }
    catch (const juju::jujubee_error& e) {
        juju::juju_codes code = juju_global::log_system_message(e.full_message());
        juju::output_code(code);
        e.vs_output_full_message();
    }
    

    if (main_window != nullptr) {
        delete main_window;
        main_window = nullptr;
    }
    
    {
        juju::juju_codes code = juju_global::log_system_message(ROS("main window closed..."));
        juju::output_code(code);
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
