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
		scroll(HWND window_handle, std::size_t max_lines, std::size_t max_line_length);


		juju_codes mouse_wheel();
		juju_codes vertical_drag();
		juju_codes horizontal_drag();
	protected:
		int m_scroll_position = 0;
		HWND m_window_handle;
		std::size_t m_max_lines;

	};
}