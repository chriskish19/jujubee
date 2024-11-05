#pragma once
#include "all_stl.hpp"

enum class codes {
	success = 0,
	init = 1,
	window_failure, // window creation failure for jujubee
	external_program_error, // this error code represents all possible external program errors, error handling per program is internal
	jujubee_win32_error, // a error in from the win32 api that relates to jujubee
	jujubee_logger_failed, // an error when logging within jujubee
	jujubee_gui_error, // an error within jujubee win32 gui framework






	// add more here
};

class jujubee_errors {
public:
	jujubee_errors() noexcept = default;

	jujubee_errors(const std::initializer_list<codes>& errors) noexcept{
		for (auto error : errors) {
			m_protected_jujubee_error_codes_vec.push_back(error);
		}
	}
protected:
	codes m_protected_main_error_code = codes::init;
	std::vector<codes> m_protected_jujubee_error_codes_vec = {};
};