/***********************************************
* File: basic.hpp
*
* Purpose: basic win32 window creation
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include ERROR_INCLUDE_PATH
#include UI_INCLUDE_PATH



namespace juju {
	// abstract class
	class foundation {
	public:
		foundation() = default;
	protected:
		virtual LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual juju_codes window_settings() = 0;
		virtual juju_codes create_window() = 0;
		virtual juju_codes message_pump() = 0;

		HWND m_window_handle = nullptr;
		HINSTANCE m_hinst = GetModuleHandle(NULL);
		string m_c_name = L"foundation";
		string m_title = L"plain window";
		WNDCLASS m_wc = {};
	};


	class starter :public foundation {
	public:
		starter() = default;
		starter(const string& class_name);
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		juju_codes window_settings() override;
		juju_codes create_window() override;
		juju_codes message_pump() override;
	};

	class window :starter{
	public:
		window();

		void go();

	protected:
		LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		juju_codes add_menu(HWND window_handle);

		ui m_main_ui;
	};
}