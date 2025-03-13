/*

File: api.hpp
Purpose: General utilities/functions

*/

#pragma once

// dependencies
#include "main_project_jujubee\dependencies\include_dependencies.hpp"
#include "main_project_jujubee\classes\error\error.hpp"

namespace classes {
	// string conversions with error codes, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow, codes* code_p);
	std::wstring to_wide_string(const std::string& narrow, codes* code_p);
	std::string to_narrow_string(const wchar_t* wide, codes* code_p);
	std::string to_narrow_string(const std::wstring& wide, codes* code_p);


}