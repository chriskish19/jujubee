/***********************************************
* 
* File: utilities.hpp
* 
* Purpose: provide helper functions for jujubee
*
* Used: everywhere in jujubee project
* 
* Project: jujubee
* 
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include ERROR_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include OBJECTS_INCLUDE_PATH


namespace juju_api {


	UINT get_window_width(HWND window_handle);
	UINT get_window_height(HWND window_handle);

	UINT get_window_height(HWND window_handle, juju::juju_codes* code) noexcept;
	UINT get_window_width(HWND window_handle, juju::juju_codes* code) noexcept;

	// string conversions, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	// throws a jujubee exception on error...
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow);
	std::wstring to_wide_string(const std::string& narrow);
	std::string to_narrow_string(const wchar_t* wide);
	std::string to_narrow_string(const std::wstring& wide);

	// string conversions with error codes instead of exceptions, 
	// if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	std::wstring to_wide_string(const char* narrow, juju::juju_codes* code_p);
	std::wstring to_wide_string(const std::string& narrow, juju::juju_codes* code_p);
	std::string to_narrow_string(const wchar_t* wide, juju::juju_codes* code_p);
	std::string to_narrow_string(const std::wstring& wide, juju::juju_codes* code_p);


	// functions for logging messages to the system logger
	juju::juju_codes log_system_message(const juju::string& message);
	juju::juju_codes log_system_message(const char* message);
	juju::juju_codes log_system_std_file_exception(const std::filesystem::filesystem_error& e);
	juju::juju_codes log_system_std_exception(const std::exception& e);
}

