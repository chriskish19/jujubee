/***********************************************
*
*
*
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include WINDOWLOGGER_INCLUDE_PATH
#include CODES_INCLUDE_PATH

namespace juju_global {
	extern juju::window_logger* wl_sys_logger;

	extern std::thread* wl_thread_p;

	juju::juju_codes log_system_message(const juju::string& message);

	juju::juju_codes start_logger();
	juju::juju_codes close_logger();
}