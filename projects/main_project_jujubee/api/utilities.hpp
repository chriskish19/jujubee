/***********************************************
* File: utilities.hpp
* 
* Purpose: provide helper functions for jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include ERROR_INCLUDE_PATH

namespace juju_api {
	UINT get_window_width(HWND window_handle);
	UINT get_window_height(HWND window_handle);

	UINT get_window_height(HWND window_handle, juju::juju_codes* code) noexcept;
	UINT get_window_width(HWND window_handle, juju::juju_codes* code) noexcept;


}

