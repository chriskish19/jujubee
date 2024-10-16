#pragma once
#include "all_stl.hpp"
#include "juju_error_codes.hpp"

class juju_log {
	juju_log(std::initializer_list<codes> errors);
};