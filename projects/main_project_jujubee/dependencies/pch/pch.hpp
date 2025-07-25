/***********************************************
*
* File: pch.hpp
*
* Purpose: pre-compiled-header
*
* Project: jujubee
*
************************************************/

#ifndef PCH_HPP_GUARD
#define PCH_HPP_GUARD

// name changes
#include NAMES_INCLUDE

// dependencies
#include STL_INCLUDE_PATH
#include SETTINGS_INCLUDE_PATH		
#include TYPES_INCLUDE_PATH			
#include WINDOWS_INCLUDE_PATH

// juju (namespace)
#include CODES_INCLUDE_PATH		
#include ERROR_INCLUDE_PATH	
#include FILELOGGER_INCLUDE_PATH		
#include LOGS_INCLUDE_PATH			
#include WINDOWLOGGER_INCLUDE_PATH	
#include BASIC_INCLUDE_PATH	
#include EXCEPT_INCLUDE_PATH
#include UI_INCLUDE_PATH

// juju_global (namespace)
#include MAIN_INCLUDE_PATH

// juju_file_system (namespace)
#include JFS_UTILITIES_INCLUDE_PATH	
#include DRIVE_INCLUDE_PATH			
#include PATH_INCLUDE_PATH			
#include FILE_INCLUDE_PATH			
#include JUJU128_INCLUDE_PATH		
#include FOLDER_INCLUDE_PATH			

// juju_api (namespace)
#include UTILITIES_INCLUDE_PATH
#include INIT_INCLUDE_PATH

// juju_test (namespace)
#include TEST_UTILITIES_INCLUDE_PATH
#include RANDOM_INCLUDE_PATH


#endif

