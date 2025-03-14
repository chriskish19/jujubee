/*

File: basic.hpp
Purpose: basic window creation in win32

*/

#pragma once

// dependencies
#include "main_project_jujubee\dependencies\include_dependencies.hpp"
#include "main_project_jujubee\classes\error\error.hpp"
#include "main_project_jujubee\classes\utilities\api.hpp"

namespace classes {
	// abstract class
	class foundation {
	public:
		foundation() = default;
	protected:
		virtual LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual codes window_settings() = 0;
		virtual codes create_window() = 0;
		virtual codes message_pump() = 0;

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

		codes window_settings() override;
		codes create_window() override;
		codes message_pump() override;

		// return value from registering windows class
		inline static std::atomic<ATOM> m_class_atm = 0;
	};

	class window :starter{
	public:
		window();

	protected:
		LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		codes add_menu(HWND window_handle);

		enum class window_ids {
			console,
			file,
			open,
			exit,
			help
		};
	};
}