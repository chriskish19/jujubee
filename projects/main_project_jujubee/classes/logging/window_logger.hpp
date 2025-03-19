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

namespace juju {
	class window_logger : starter{
	public:
		window_logger();

		juju_codes go();
	protected:
		LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	};
}
