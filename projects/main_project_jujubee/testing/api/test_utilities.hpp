/***********************************************
* File: test_utilities.hpp
*
* Purpose: test jujubee's code base
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include ERROR_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include RANDOM_INCLUDE_PATH
#include WINDOWLOGGER_INCLUDE_PATH

namespace juju {
	juju_codes test_logging(std::size_t seconds);
}