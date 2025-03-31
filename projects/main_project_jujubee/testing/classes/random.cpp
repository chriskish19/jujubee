#include NAMES_INCLUDE
#include RANDOM_INCLUDE_PATH


juju::random::random(std::size_t rlow, std::size_t rhigh)
{
    // init members
    m_gen = std::mt19937(m_rd());
    m_dist= std::uniform_int_distribution<int>(rlow, rhigh);
}

juju::string juju::random::random_data_string(std::size_t length)
{
    string message;
    for (std::size_t i = 0; i < length; ++i) {
        message += m_dist(m_gen);
    }

    return message;
}
