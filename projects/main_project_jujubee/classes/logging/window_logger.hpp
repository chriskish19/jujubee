/***********************************************
* File: window_logger.hpp
*
* Purpose: provide a window for viewing system logs from jujubee
*
*
************************************************/
 
#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include BASIC_INCLUDE_PATH
#include LOGS_INCLUDE_PATH
#include ERROR_INCLUDE_PATH
#include SCROLL_INCLUDE_PATH


namespace juju {
	class window_logger : starter{
	public:
		window_logger();
		~window_logger();

		juju_codes go();

		juju_codes wait_until_init();
		juju_codes wait_until_closed();

		juju_codes send_message(const string& message);
		string get_latest_message() { return m_logger.get_latest_message(); }
	protected:
		std::atomic<bool> m_wait_b = false;
		std::condition_variable m_wait_cv;

		juju_codes create_window() override;
		juju_codes message_pump() override;
		juju_codes window_settings() override;

		LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		
		// 1000 messages and each message max length 512 characters
		base_logger m_logger = base_logger(LOGGER_LINES,LOGGER_MESSAGE_LENGTH);

		// create a font for window logger
		juju_codes setup_font(std::size_t font_size);

		// custom font
		HFONT m_wl_font = nullptr;
		const std::size_t m_font_size = LINE_HEIGHT;

		// keep track of screen resolution
		int m_sr_x = GetSystemMetrics(SM_CXSCREEN); // screen width
		int m_sr_y = GetSystemMetrics(SM_CYSCREEN); // screen height

		// this is used when screen resolution changes
		// and we need more or less single line rects
		juju_codes update_vector_of_rects(std::size_t new_size);

		juju_codes paint_window(HWND hwnd);
		
		scroll m_scrolling;

		// we allocate all the neccesary rects for the logger window
		// to print the messages into
		std::vector<RECT*>* m_single_lines_p = nullptr;

		// index for accessing a rect pointer from m_single_lines_p
		std::size_t m_slvp_index = 0;
		RECT* get_rect_p();

		juju_codes update_logger_window();
	};
}
