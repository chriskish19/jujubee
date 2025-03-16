#include "logs.hpp"
#include NAMES_INCLUDE
#include LOGS_INCLUDE_PATH

void classes::log::set_message(const string& message)
{
    m_message = message;
}

std::chrono::steady_clock::time_point classes::log::get_time()
{
    m_time = std::chrono::high_resolution_clock::now();
    return m_time;
}

void classes::log::set_time()
{
    m_time = std::chrono::high_resolution_clock::now();
}

classes::base_logger::base_logger(std::size_t log_count)
    :m_log_count(log_count)
{
    m_logs_v.reserve(m_log_count);

    for (std::size_t i = 0; i < m_log_count; ++i) {
        log* lp = new log;
        m_logs_v.push_back(lp);
    }
}
