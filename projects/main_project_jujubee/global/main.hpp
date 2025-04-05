/***********************************************
* File: main.hpp
*
* Purpose: handle global objects and functions for 
		   the global objects.
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include WINDOWLOGGER_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include FILELOGGER_INCLUDE_PATH


namespace juju_global {
	// system global logger window
	extern juju::window_logger* wl_sys_logger;

	// thread for running system global logger window
	extern std::thread* wl_thread_p;

	// functions for logging messages to the system global logger
	juju::juju_codes log_system_message(const juju::string& message);
	juju::juju_codes log_system_message(const char* message);
	juju::juju_codes log_system_std_file_exception(const std::filesystem::filesystem_error& e);
	juju::juju_codes log_system_std_exception(const std::exception& e);

	// initialization: launches the thread
	juju::juju_codes start_logger();

	// cleans up resources
	juju::juju_codes close_logger();
}