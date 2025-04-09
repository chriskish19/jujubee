#include NAMES_INCLUDE
#include INIT_INCLUDE_PATH



juju::juju_codes juju_api::start_jfs() {
    jfs_drive_letters = new std::unordered_set<jfs::character>;
    return juju::juju_codes::success;
}


juju::juju_codes juju_api::close_jfs() {
    if (jfs_drive_letters != nullptr) {
        delete jfs_drive_letters;
        jfs_drive_letters = nullptr;
    }

    return juju::juju_codes::success;
}

juju::juju_codes juju_api::start_logger() {
    wl_sys_logger = new juju::window_logger;

    wl_thread_p = new std::thread(&juju::window_logger::go, wl_sys_logger);

    wl_sys_logger->wait_until_init();

    return juju::juju_codes::success;
}

juju::juju_codes juju_api::close_logger() {
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