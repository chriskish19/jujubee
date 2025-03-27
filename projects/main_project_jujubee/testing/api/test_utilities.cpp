#include "test_utilities.hpp"
#include NAMES_INCLUDE
#include TEST_UTILITIES_INCLUDE_PATH


juju::juju_codes juju::test_logging(std::size_t seconds)
{
    juju::log l(LOGGER_MESSAGE_LENGTH);
    l.set_time();
    std::size_t time_length = l.get_time_length();
    
    window_logger wl;
    std::jthread wl_thread(&juju::window_logger::go, &wl);
    wl.wait_until_init();

    random data(32, 126);

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    while (std::chrono::steady_clock::now() < end_time) {
        string message = data.random_data_string(LOGGER_MESSAGE_LENGTH-time_length);
        wl.send_message(message);
    }

    return juju_codes::success;
}
