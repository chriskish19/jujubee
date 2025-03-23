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
		scroll(SCROLLINFO v_si, SCROLLINFO h_si, SCROLLINFO mouse_si, std::size_t line_height);


		juju_codes mouse_wheel(HWND hwnd, WPARAM wParam);
		juju_codes vertical_drag(HWND hwnd,WPARAM wParam);
		juju_codes horizontal_drag(HWND hwnd,WPARAM wParam);
	protected:
		int m_scroll_position_v = 0;
		int m_scroll_position_h = 0;
		int m_scroll_position_m = 0;
		SCROLLINFO m_si_h;
		SCROLLINFO m_si_v;
		SCROLLINFO m_mouse_si;
		const std::size_t m_line_height;
	};
}