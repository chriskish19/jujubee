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

/*

				HWND CreateWindowW(
				  [in, optional] LPCWSTR   lpClassName,
				  [in, optional] LPCWSTR   lpWindowName,
				  [in]           DWORD     dwStyle,
				  [in]           int       x,
				  [in]           int       y,
				  [in]           int       nWidth,
				  [in]           int       nHeight,
				  [in, optional] HWND      hWndParent,
				  [in, optional] HMENU     hMenu,
				  [in, optional] HINSTANCE hInstance,
				  [in, optional] LPVOID    lpParam
				);

*/



namespace juju {
	struct button_description {
		HWND window = nullptr; 
		std::size_t xPos = 0; 
		std::size_t yPos = 0; 
		std::size_t width = 0; 
		std::size_t height = 0;
	};
	
	
	class button {
	public:
		button(button_description bd);
	};
}