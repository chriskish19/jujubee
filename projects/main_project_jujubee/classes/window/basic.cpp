#include "basic.hpp"

classes::starter::starter(const string& class_name)
{
    m_c_name = class_name;
}

LRESULT classes::starter::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // reroute to private window proc
    starter* p_window_rerouter = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        // Store the pointer to the window instance in the user data associated with the HWND.
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_window_rerouter = (starter*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_window_rerouter);
    }
    else
    {
        // Retrieve the pointer to the window instance from the user data associated with the HWND.
        p_window_rerouter = (starter*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (p_window_rerouter)
    {
        return p_window_rerouter->ThisWindowProc(hwnd, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT classes::starter::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

classes::codes classes::starter::window_settings()
{
    // the class might already be registered
    if (m_class_atm.load() > 0) {
        return codes::class_already_registered;
    }

    m_wc.lpfnWndProc = WindowProc;
    m_wc.hInstance = m_hinst;
    m_wc.lpszClassName = m_c_name.c_str();

    m_class_atm.store(RegisterClass(&m_wc));

    if (m_class_atm.load() == FALSE) {
        return codes::failed_to_register_class;
    }
    return codes::success;
}

classes::codes classes::starter::create_window()
{
    m_window_handle = CreateWindowEx(
        0,                                              // Optional window styles.
        m_c_name.c_str(),                               // Window class
        m_title.c_str(),                                // Window text
        WS_OVERLAPPEDWINDOW,                            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,                                           // Parent window    
        NULL,                                           // Load the menu here
        m_hinst,                                        // Instance handle
        this                                            // Additional application data
    );

    if (m_window_handle == nullptr) {
        return codes::hwnd_fail;
    }

    
    if (ShowWindow(m_window_handle, SW_SHOW) > 0) {
        return codes::show_window_fail;
    }
    
    return codes::success;
}

classes::codes classes::starter::message_pump()
{
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return codes::success;
}

classes::window::window()
{
    {
        codes code;
        code = window_settings();
        output_code(code);
    }

    {
        codes code;
        code = create_window();
        output_code(code);
    }

    {
        codes code;
        code = add_menu(m_window_handle);
        output_code(code);
    }

    {
        codes code;
        code = message_pump();
        output_code(code);
    }
}

LRESULT classes::window::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);  // Extract the menu item ID
            switch (wmId) {
                case static_cast<int>(window_ids::console):
                {
                    break;
                }
                default:
                    break;
            } // end of switch (wmId)
            break;
        }
    } // end of switch (uMsg)

    // no default switch needed
    return starter::ThisWindowProc(hwnd, uMsg, wParam, lParam);
}

classes::codes classes::window::add_menu(HWND window_handle)
{
    HMENU hMenu = CreateMenu();
    if (hMenu == nullptr) {
        return codes::menu_fail;
    }

    HMENU hFileMenu = CreatePopupMenu();
    if (hFileMenu == nullptr) {
        return codes::menu_fail;
    }

    HMENU hHelpMenu = CreatePopupMenu();
    if (hHelpMenu == nullptr) {
        return codes::menu_fail;
    }

    AppendMenu(hFileMenu, MF_STRING, static_cast<UINT_PTR>(window_ids::open), L"&Open");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(hFileMenu, MF_STRING, static_cast<UINT_PTR>(window_ids::exit), L"E&xit");

    AppendMenu(hHelpMenu, MF_STRING, static_cast<UINT_PTR>(window_ids::help), L"&About");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, L"&Help");

    SetMenu(window_handle, hMenu);
}
