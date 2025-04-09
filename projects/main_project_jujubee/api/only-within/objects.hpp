/***********************************************
* File: objects.hpp
*
* Purpose: juju_api global objects
*
* Used: only within juju_api namespace
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include WINDOWLOGGER_INCLUDE_PATH


namespace juju_api {
	// juju file system drives
	extern std::unordered_set<jfs::character>* jfs_drive_letters;

	// system global logger window
	extern juju::window_logger* wl_sys_logger;

	// thread for running system global logger window
	extern std::thread* wl_thread_p;
}