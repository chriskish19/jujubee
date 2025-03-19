#include NAMES_INCLUDE
#include WINDOWLOGGER_INCLUDE_PATH

juju::window_logger::window_logger()
{
	
}

juju::juju_codes juju::window_logger::go() 
{
	window_settings();
	create_window();
	return message_pump();
}

LRESULT juju::window_logger::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    


    } // end of switch (uMsg)

    // no default switch needed
    return starter::ThisWindowProc(hwnd, uMsg, wParam, lParam);
}
