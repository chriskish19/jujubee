/***********************************************
* File: scroll.hpp
*
* Purpose: handle scrolling in a win32 window
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH


namespace juju {
	class scroll {
	public:
		scroll(SCROLLINFO si,HWND window_handle);



	protected:
		int m_scroll_position = 0;


	};
}