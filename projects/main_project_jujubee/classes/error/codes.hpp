/***********************************************
* File: codes.hpp
* 
* Purpose: defines all codes (error codes and messages)
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include TYPES_INCLUDE_PATH
#include SETTINGS_INCLUDE_PATH
#include STL_INCLUDE_PATH

namespace juju {
	enum class juju_codes {
		success = 0,
		unintialized,
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
		show_window_fail,
		menu_fail,
		unknown,
		getclientrect_fail
	};

	inline const character* success_description =					ROS("Operation completed successfully.");
	inline const character* uninitialized_description =				ROS("enum class codes defaults to int 1 if not set explicitly");
    inline const character* null_pointer_description =				ROS("Encountered a null pointer.");
    inline const character* window_problem_description =			ROS("There was a problem with the window.");
    inline const character* exception_thrown_description =			ROS("An exception was thrown.");
    inline const character* empty_file_description =				ROS("The file is empty.");
    inline const character* string_length_too_long_description =	ROS("The string length is too long.");
    inline const character* to_wide_string_failed_description =		ROS("Failed to convert to wide string.");
    inline const character* to_narrow_string_failed_description =	ROS("Failed to convert to narrow string.");
    inline const character* class_already_registered_description =	ROS("The class is already registered.");
    inline const character* failed_to_register_class_description =	ROS("Failed to register the class.");
    inline const character* hwnd_fail_description =					ROS("Failed to obtain window handle.");
    inline const character* show_window_fail_description =			ROS("Failed to show the window.");
    inline const character* menu_fail_description =					ROS("Failed to create or display the menu.");
	inline const character* unknown_description =					ROS("Unknown code");
	inline const character* getclientrect_fail_description =		ROS("Failed to obtain client rect.");

	class code_description : std::exception{
	public:
		code_description(juju_codes code, string description)
			:m_code(code),m_description(description) { }

		const juju_codes m_code;
		const string m_description;
	};

	inline const code_description success_code						(juju_codes::success, success_description);
	inline const code_description uninitialized_code				(juju_codes::unintialized, uninitialized_description);
	inline const code_description null_pointer_code					(juju_codes::null_pointer, null_pointer_description);
	inline const code_description window_problem_code				(juju_codes::window_problem, window_problem_description);
	inline const code_description exception_thrown_code				(juju_codes::exception_thrown, exception_thrown_description);
	inline const code_description empty_file_code					(juju_codes::empty_file, empty_file_description);
	inline const code_description string_length_too_long_code		(juju_codes::string_length_too_long, string_length_too_long_description);
	inline const code_description to_wide_string_failed_code		(juju_codes::to_wide_string_failed, to_wide_string_failed_description);
	inline const code_description to_narrow_string_failed_code		(juju_codes::to_narrow_string_failed, to_narrow_string_failed_description);
	inline const code_description class_already_registered_code		(juju_codes::class_already_registered, class_already_registered_description);
	inline const code_description failed_to_register_class_code		(juju_codes::failed_to_register_class, failed_to_register_class_description);
	inline const code_description hwnd_fail_code					(juju_codes::hwnd_fail, hwnd_fail_description);
	inline const code_description show_window_fail_code				(juju_codes::show_window_fail, show_window_fail_description);
	inline const code_description menu_fail_code					(juju_codes::menu_fail, menu_fail_description);
	inline const code_description unknown_code						(juju_codes::unknown, unknown_description);
	inline const code_description getclientrect_fail_code			(juju_codes::getclientrect_fail, getclientrect_fail_description);


	// matches the juju_code to a code_description object
	code_description match_code(juju_codes code);
}