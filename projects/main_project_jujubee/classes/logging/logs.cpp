#include NAMES_INCLUDE
#include LOGS_INCLUDE_PATH

juju::log::log(std::size_t message_length)
    :m_message_length_reserved(message_length)
{
    m_message.reserve(message_length);
}

void juju::log::set_message(const string& message)
{
    std::unique_lock<std::mutex> local_lock(m_message_mtx);
    m_message = message;
}

juju::string juju::log::get_message_copy()
{
    std::unique_lock<std::mutex> local_lock(m_message_mtx);
    return m_message;
}

void juju::log::set_time()
{
    auto now = std::chrono::system_clock::now();
    m_stime = std::format(ROS("[{}]"), now);
    m_message = m_stime + m_message;
}

juju::base_logger::base_logger(std::size_t log_count, std::size_t message_length)
    :m_log_count(log_count),m_message_length(message_length)
{
    m_logs_vp->reserve(m_log_count);

    for (std::size_t i = 0; i < m_log_count; ++i) {
        log* lp = new log(m_message_length);
        m_logs_vp->push_back(lp);
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
    log* lp = m_logs_vp->at(index);
    lp->set_message(message);
    lp->set_time();
    
    return juju_codes::success;
}

juju::juju_codes juju::base_logger::add_message(const string& message)
{
    log* lp = m_logs_vp->at(m_log_pos);
    lp->set_message(message);
    lp->set_time();

    std::size_t max_index = m_log_count - 1;

    if (m_log_pos < max_index) {
        m_log_pos++;
    }
    else {
        m_log_pos = 0;
    }

    return juju_codes::success;
}
