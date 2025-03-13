/*

File: error.hpp
Purpose: error handling for jujubee

*/

#pragma once

namespace classes {
	enum class codes {
		success = 0,
		null_pointer,
		window_problem,
		exception_thrown,
		empty_file,
		string_length_too_long,
		to_wide_string_failed,
		to_narrow_string_failed,
		class_already_registered,
		failed_to_register_class,
		hwnd_fail,
		show_window_fail


	};


}