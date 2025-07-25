/***********************************************
*
* File: init.hpp
*
* Purpose: initialize juju parts
*
* Project: jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include WINDOWLOGGER_INCLUDE_PATH
#include OBJECTS_INCLUDE_PATH




namespace juju_api {
	
	// initialization: launches the thread
	juju::juju_codes start_logger();

	// cleans up resources
	juju::juju_codes close_logger();



	// inits juju file system
	juju::juju_codes start_jfs();

	// shutsdown jfs
	juju::juju_codes close_jfs();
}