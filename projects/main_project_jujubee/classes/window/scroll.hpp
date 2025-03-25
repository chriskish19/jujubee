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
		scroll(SCROLLINFO si, std::size_t line_height);


		juju_codes mouse_wheel(HWND hwnd, WPARAM wParam);
		juju_codes vertical_drag(HWND hwnd,WPARAM wParam);
		juju_codes horizontal_drag(HWND hwnd,WPARAM wParam);

		int get_v_position() { return m_vscroll_position; }
		int get_h_position() { return m_hscroll_position; }
	protected:
		int m_vscroll_position = 0;
		int m_hscroll_position = 0;
		SCROLLINFO m_si = {};
		const std::size_t m_line_height = 0;
	};
}