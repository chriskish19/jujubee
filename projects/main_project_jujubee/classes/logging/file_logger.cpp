#include NAMES_INCLUDE
#include FILELOGGER_INCLUDE_PATH


juju::file_logger::file_logger(const string& file_name, const fs::path& p) 
{
    try {
        m_log_file_path = p / file_name;
    }
    catch (const std::filesystem::filesystem_error& e) {
        juju_global::log_system_std_file_exception(e);
        
        // if that fails just use the file_name as the starting path
        m_log_file_path = file_name;
    }
}

juju::juju_codes juju::file_logger::create() {
	

    return juju_codes::success;
}