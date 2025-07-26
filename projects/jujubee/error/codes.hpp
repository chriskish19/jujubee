/***********************************************
* 
* File: codes.hpp
* 
* Purpose: defines all codes (error codes and messages)
* 
* Project: jujubee
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
		getclientrect_fail,
		lb_add_string_fail,
		lb_get_selection_fail,
		file_open_fail,
		std_error_convert_unknown,
		set_icon_fail,

		// file errors (<system_error>)
		permission_denied,					// No permission to access the file / directory
		no_such_file_or_directory,			// File or directory does not exist
		file_exists,						// File already exists when trying to create one
		is_a_directory,						// Expected a file but found a directory
		not_a_directory,					// Expected a directory but found a file
		device_or_resource_busy,			// File is locked by another process
		invalid_argument,					// Invalid path or argument provided
		directory_not_empty,				// Cannot delete a non - empty directory
		file_too_large,						// File exceeds the system's size limit
		io_error,							// Generic I / O error(e.g., disk failure)
		no_space_on_device,					// Disk is full
		too_many_files_open 				// Process has too many open files
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
	inline const character* lb_add_string_fail_description =		ROS("Failed to add string to list box.");
	inline const character* lb_get_selection_fail_description =		ROS("Failed to get selected string inside listbox.");
	inline const character* file_open_fail_description =			ROS("F stream failed to open file.");
	inline const character* std_error_convert_unknown_description = ROS("the function std_error_code_convert() encountered an unknown code");
	inline const character* set_icon_fail_description =				ROS("failed to set icon.");



	// file errors from header:<system_error>
	inline const character* permission_denied_description =			ROS("No permission to access the file / directory");
	inline const character* no_such_file_or_directory_description = ROS("File or directory does not exist");
	inline const character*	file_exists_description	=				ROS("File already exists when trying to create one");
	inline const character*	is_a_directory_description =			ROS("Expected a file but found a directory");
	inline const character* not_a_directory_description =			ROS("Expected a directory but found a file");
	inline const character* device_or_resource_busy_description =	ROS("File is locked by another process");
	inline const character* invalid_argument_description =			ROS("Invalid path or argument provided");
	inline const character* directory_not_empty_description =		ROS("Cannot delete a non - empty directory");
	inline const character* file_too_large_description =			ROS("File exceeds the system's size limit");
	inline const character* io_error_description =					ROS("Generic I / O error(e.g., disk failure)");
	inline const character* no_space_on_device_description =		ROS("Disk is full");
	inline const character* too_many_files_open_description =		ROS("Process has too many open files");


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
	inline const code_description lb_add_string_fail_code			(juju_codes::lb_add_string_fail, lb_add_string_fail_description);
	inline const code_description lb_get_selection_fail_code		(juju_codes::lb_get_selection_fail, lb_get_selection_fail_description);
	inline const code_description file_open_fail_code				(juju_codes::file_open_fail, file_open_fail_description);
	inline const code_description std_error_convert_unknown_code	(juju_codes::std_error_convert_unknown, std_error_convert_unknown_description);
	inline const code_description set_icon_fail_code				(juju_codes::set_icon_fail, set_icon_fail_description);


	// file errors
	inline const code_description permission_denied_code			(juju_codes::permission_denied, permission_denied_description);
	inline const code_description no_such_file_or_directory_code	(juju_codes::no_such_file_or_directory, no_such_file_or_directory_description);
	inline const code_description file_exists_code					(juju_codes::file_exists, file_exists_description);
	inline const code_description is_a_directory_code				(juju_codes::is_a_directory, is_a_directory_description);
	inline const code_description not_a_directory_code				(juju_codes::not_a_directory, not_a_directory_description);
	inline const code_description device_or_resource_code			(juju_codes::device_or_resource_busy, device_or_resource_busy_description);
	inline const code_description invalid_argument_code				(juju_codes::invalid_argument, invalid_argument_description);
	inline const code_description directory_not_empty_code			(juju_codes::directory_not_empty, directory_not_empty_description);
	inline const code_description file_too_large_code				(juju_codes::file_too_large, file_too_large_description);
	inline const code_description io_error_code						(juju_codes::io_error, io_error_description);
	inline const code_description no_space_on_device_code			(juju_codes::no_space_on_device, no_space_on_device_description);
	inline const code_description too_many_files_open_code			(juju_codes::too_many_files_open, too_many_files_open_description);




	// matches the juju_code to a code_description object
	code_description match_code(juju_codes code);

	// convert from std::error_code to juju code
	juju_codes std_error_code_convert(std::error_code ec);
}