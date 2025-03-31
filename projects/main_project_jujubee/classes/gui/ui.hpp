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
#include LISTBOX_INCLUDE_PATH

namespace juju {
	enum class window_ids {
		console = 0,
		file,
		open,
		exit,
		help,
		b_front,
		b_refresh,
		lb_box
	};

	
	class ui {
	public:
		ui() = default;
		ui(HWND window,HMENU menu,HINSTANCE hinst,LPVOID lp);
		

		button m_front_b;
		void front_button_action(button_state bs);

		button m_refresh_b;
		void refresh_button_action(button_state bs);

		listbox m_front_lb;
		void front_listbox_action(listbox_commands lc);
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
		std::function<void(button_state)> button_caller = nullptr;
	};

*/
		juju::button_description m_front_bd{
			ROS("BUTTON"),
			ROS("#num1"),
			BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
			500,
			50,
			100,
			100,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr
		};

		juju::button_description m_refresh_bd{
			ROS("BUTTON"),
			ROS("Refresh"),
			BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
			10,
			400,
			100,
			50,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr
		};



/*
		
		struct listbox_description {
		string class_name = ROS("LISTBOX");
		string window_name = ROS("LB1");
		DWORD style_flags = 0;
		std::size_t xPos = 0;
		std::size_t yPos = 0;
		std::size_t width = 0;
		std::size_t height = 0;
		HWND window = nullptr;
		HMENU menu = nullptr;
		HINSTANCE hinst = GetModuleHandle(NULL);
		LPVOID lpParam = nullptr;
		std::function<void(listbox_commands)> listbox_caller = nullptr;
	};
		
*/

		listbox_description m_front_lb_ld{
			ROS("LISTBOX"),
			ROS("LB_front"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_STANDARD,
			10,
			20,
			200,
			200,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr
		};

	};
}