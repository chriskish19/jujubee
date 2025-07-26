/***********************************************
* File: random.hpp
*
* Purpose: generate random data, mostly for testing
*
* Project: jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH

namespace juju_test {
	class random {
	public:
		random(std::size_t rlow, std::size_t rhigh);

		string random_data_string(std::size_t length);
	protected:
		std::random_device m_rd;
		std::mt19937 m_gen;
		std::uniform_int_distribution<int> m_dist;
	};
}