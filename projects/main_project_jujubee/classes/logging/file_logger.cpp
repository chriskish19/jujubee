#include NAMES_INCLUDE
#include FILELOGGER_INCLUDE_PATH


juju::file_logger::file_logger(const string& file_name, const fs::path& p) 
{
    try {
        m_log_file_path = p / file_name;
    }
    catch (const std::filesystem::filesystem_error& e) {
#if USING_WSTR
        string error_message = juju_api::to_wide_string(e.what());
#elif USING_STR
        string error_message = e.what();
#endif
        juju_global::log_system_message(error_message);
    }
}

juju::juju_codes juju::file_logger::create() {
	

    return juju_codes::success;
}