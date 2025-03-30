/***********************************************
*
*
*
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include BUTTON_INCLUDE_PATH

namespace juju {
	class ui {
	public:
		ui() = default;
		ui(HWND window,HMENU menu,HINSTANCE hinst,LPVOID lp);
		

		button m_front_b;
		void front_button_action(button_state bs);
	protected:

/*

	struct button_description {
		string class_name = ROS("BUTTON");
		string window_name = ROS("#num");
		DWORD style_flags = 0;
		std::size_t xPos = 0;
		std::size_t yPos = 0;
		std::size_t width = 0;
		std::size_t height = 0;
		HWND window = nullptr;
		HMENU menu = nullptr;
		HINSTANCE hinst = GetModuleHandle(NULL);
		LPVOID lpParam = nullptr;
	};

*/
		juju::button_description m_front_bd{
			ROS("BUTTON"),
			ROS("#num1"),
			BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
			50,
			50,
			100,
			100,
			nullptr,
			nullptr,
			nullptr,
			nullptr
		};
	};
}