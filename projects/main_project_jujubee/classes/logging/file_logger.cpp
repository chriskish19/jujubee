#include NAMES_INCLUDE
#include FILELOGGER_INCLUDE_PATH


juju::file_logger::file_logger(const string& file_name, const fs::path& p) 
{
    try {
        m_log_file_path = p / file_name;
    }
    catch (const std::filesystem::filesystem_error& e) {
        
    }
    catch (const std::bad_alloc& e) {
        
    }
    catch (const std::exception& e) {
        
    }
	


}

juju::juju_codes juju::file_logger::create() {
	

    return juju_codes::success;
}