#include NAMES_INCLUDE
#include LOGS_INCLUDE_PATH

juju::log::log(std::size_t message_length)
    :m_message_length_reserved(message_length)
{
    try {
        m_message.reserve(message_length);
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}

void juju::log::set_message(const string& message)
{
    std::unique_lock<std::mutex> local_lock(m_message_mtx);
    try {
        m_message = message;
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}

juju::string juju::log::get_message_copy()
{
    std::unique_lock<std::mutex> local_lock(m_message_mtx);
    return m_message;
}

void juju::log::set_time()
{
    try {
        auto now = std::chrono::system_clock::now();
        m_stime = std::format(ROS("[{}]"), now);
        m_message = m_stime + m_message;
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}

juju::base_logger::base_logger(std::size_t log_count, std::size_t message_length)
    :m_log_count(log_count),m_message_length(message_length)
{
    try {
        m_logs_vp->reserve(m_log_count);

        for (std::size_t i = 0; i < m_log_count; ++i) {
            log* lp = new log(m_message_length);
            m_logs_vp->push_back(lp);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}

juju::base_logger::~base_logger()
{
    for (auto lp : *m_logs_vp) {
        if (lp != nullptr) {
            delete lp;
            lp = nullptr;
        }
    }

    if (m_logs_vp != nullptr) {
        delete m_logs_vp;
        m_logs_vp = nullptr;
    }
}

juju::juju_codes juju::base_logger::add_message(const string& message, std::size_t index) 
{
    
    try {
        log* lp = m_logs_vp->at(index);
        lp->set_message(message);
        lp->set_time();
        return juju_codes::success;
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return juju_codes::exception_thrown;
}

juju::juju_codes juju::base_logger::add_message(const string& message)
{
    std::unique_lock<std::mutex> local_lock(m_logs_vp_mtx);
    try {
        log* lp = m_logs_vp->at(m_log_pos);
        lp->set_message(message);
        lp->set_time();
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;

        std::size_t max_index = m_log_count - 1;

        if (m_log_pos < max_index) {
            m_log_pos++;
        }
        else {
            m_log_pos = 0;
        }

        return juju_codes::exception_thrown;
    }


    std::size_t max_index = m_log_count - 1;

    if (m_log_pos < max_index) {
        m_log_pos++;
    }
    else {
        m_log_pos = 0;
    }

    return juju_codes::success;
}

juju::string juju::base_logger::get_latest_message() {
    std::unique_lock<std::mutex> local_lock(m_logs_vp_mtx);
    try {
        auto log_p = m_logs_vp->at(m_log_pos);
        return log_p->get_message_copy();
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    // return empty string if an exception is thrown
    return {};
}
