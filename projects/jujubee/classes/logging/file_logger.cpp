/***********************************************
*
* File: file_logger.cpp
*
* Purpose: file_logger.hpp definitions
*
* Project: jujubee
*
************************************************/


#include NAMES_INCLUDE
#include FILELOGGER_INCLUDE_PATH


juju::file_logger::file_logger(const string& file_name, const fs::path& p) 
{
    try {
        m_log_file_path = p / file_name;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "file system error: " << e.what() << "\n";
        std::cerr << "path1: " << e.path1() << "\n";
        std::cerr << "path2: " << e.path2() << "\n";
        
        // if that fails just use the file_name as the starting path
        m_log_file_path = file_name;
    }

    juju_codes code = create(p);
    juju::output_code(code);
}

juju::juju_codes juju::file_logger::create(const fs::path& p) {
    try {
        fs::create_directories(p);
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "file system error: " << e.what() << "\n";
        std::cerr << "path1: " << e.path1() << "\n";
        std::cerr << "path2: " << e.path2();
    }
    
    m_log_file = juju::ofstream(m_log_file_path);

    if (m_log_file.fail()) {
        return juju_codes::file_open_fail;
    }

    return juju_codes::success;
}

juju::juju_codes juju::file_logger::add_line(const string& new_line_message) {
    std::unique_lock<std::mutex> local_lock(m_log_file_mtx);
    try {
        m_log_file << new_line_message << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "standard error: " << e.what() << "\n";
        return juju_codes::exception_thrown;
    }
    return juju_codes::success;
}