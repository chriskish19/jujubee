/***********************************************
* File:	error.hpp
* 
* Purpose: error handling for jujubee
* 
* Info:	this should only be dependant on codes.hpp and can be used throughout jujubee 
*		to handle errors
* 
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include STL_INCLUDE_PATH


namespace juju {
	string get_location(std::source_location sl = std::source_location::current());

	// string conversions with error codes, if max_string_buffer is exceeded
	// new is used to allocate a heap buffer to compensate
	const size_t max_string_buffer = MAX_STRING;
	std::wstring to_wide_string(const char* narrow, juju_codes* code_p);
	std::wstring to_wide_string(const std::string& narrow, juju_codes* code_p);
	std::string to_narrow_string(const wchar_t* wide, juju_codes* code_p);
	std::string to_narrow_string(const std::wstring& wide, juju_codes* code_p);

	void output_code(juju_codes code);
	void output_window(string message, string title = ROS("ERROR WINDOW"));

	class jujubee_error : std::exception {
	public:
		jujubee_error(code_description code, string location = get_location())
			:m_code(code),m_location(location){ }

		// send message to visual studio output window
		void vs_output_full_message();

		// returns full string message
		string full_message();
	protected:
		string m_location;
		code_description m_code;
	};
}