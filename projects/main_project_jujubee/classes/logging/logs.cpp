#include NAMES_INCLUDE
#include LOGS_INCLUDE_PATH

classes::log::log(std::size_t message_length)
    :m_message_length_reserved(message_length)
{
    m_message.reserve(message_length);
}

void classes::log::set_message(const string& message)
{
    m_message = message;
}

void classes::log::set_time()
{
    m_time = std::chrono::high_resolution_clock::now();
    m_stime = std::format(ROS("[{}]"), m_time);
    m_message = m_stime + m_message;
}

classes::base_logger::base_logger(std::size_t log_count, std::size_t message_length)
    :m_log_count(log_count),m_message_length(message_length)
{
    m_logs_vp->reserve(m_log_count);

    for (std::size_t i = 0; i < m_log_count; ++i) {
        log* lp = new log(m_message_length);
        m_logs_vp->push_back(lp);
    }
}

classes::base_logger::~base_logger()
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

classes::juju_codes classes::base_logger::add_message(const string& message, std::size_t index) 
{
    log* lp = m_logs_vp->at(index);
    lp->set_message(message);
    lp->set_time();
    
    return juju_codes::success;
}

classes::juju_codes classes::base_logger::add_message(const string& message)
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
