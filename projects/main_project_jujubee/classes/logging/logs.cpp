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
}

classes::base_logger::base_logger(std::size_t log_count, std::size_t message_length)
    :m_log_count(log_count),m_message_length(message_length)
{
    m_logs_v.reserve(m_log_count);

    for (std::size_t i = 0; i < m_log_count; ++i) {
        log* lp = new log(m_message_length);
        m_logs_v.push_back(lp);
    }
}

classes::base_logger::~base_logger()
{
    for (auto lp : m_logs_v) {
        if (lp != nullptr) {
            delete lp;
        }
    }
}
