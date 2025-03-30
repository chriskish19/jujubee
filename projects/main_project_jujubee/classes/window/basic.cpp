#include NAMES_INCLUDE
#include BASIC_INCLUDE_PATH

juju::starter::starter(const string& class_name)
{
    m_c_name = class_name;
}

LRESULT juju::starter::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT juju::starter::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

juju::juju_codes juju::starter::window_settings()
{
    // the class might already be registered
    if (m_class_atm.load() > 0) {
        return juju_codes::class_already_registered;
    }

    m_wc.lpfnWndProc = WindowProc;
    m_wc.hInstance = m_hinst;
    m_wc.lpszClassName = m_c_name.c_str();

    m_class_atm.store(RegisterClass(&m_wc));

    if (m_class_atm.load() == FALSE) {
        return juju_codes::failed_to_register_class;
    }
    return juju_codes::success;
}

juju::juju_codes juju::starter::create_window()
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
        return juju_codes::hwnd_fail;
    }

    
    if (ShowWindow(m_window_handle, SW_SHOW) > 0) {
        return juju_codes::show_window_fail;
    }
    
    return juju_codes::success;
}

juju::juju_codes juju::starter::message_pump()
{
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return juju_codes::success;
}

juju::window::window()
{
    
}

void juju::window::go()
{
    {
        juju_codes code;
        code = window_settings();
        if (code not_eq juju_codes::success) {
            code_description code_obj = match_code(code);
            throw jujubee_error(code_obj);
        }
    }

    {
        juju_codes code;
        code = create_window();
        if (code not_eq juju_codes::success) {
            code_description code_obj = match_code(code);
            throw jujubee_error(code_obj);
        }
    }

    m_main_ui = ui(m_window_handle, (HMENU)button_ids::front, m_hinst, nullptr);


    {
        juju_codes code;
        code = add_menu(m_window_handle);
        if (code not_eq juju_codes::success) {
            code_description code_obj = match_code(code);
            throw jujubee_error(code_obj);
        }
    }
    
    {
        juju_codes code;
        code = message_pump();
        if (code not_eq juju_codes::success) {
            code_description code_obj = match_code(code);
            throw jujubee_error(code_obj);
        }
    }
}

LRESULT juju::window::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

                case static_cast<int>(button_ids::front):
                {
                    m_main_ui.m_front_b.action(button_state::pressed);
                    break;
                }

                default:
                    break;
            } // end of switch (wmId)
            break;
        }

        case WM_SIZING:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // lParam holds a pointer to a RECT structure
            RECT* lw_rect_p = reinterpret_cast<RECT*>(lParam);

            FillRect(hdc, lw_rect_p, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);

            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);

            break;
        }
    } // end of switch (uMsg)

    // no default switch needed
    return starter::ThisWindowProc(hwnd, uMsg, wParam, lParam);
}

juju::juju_codes juju::window::add_menu(HWND window_handle)
{
    HMENU hMenu = CreateMenu();
    if (hMenu == nullptr) {
        return juju_codes::menu_fail;
    }

    HMENU hFileMenu = CreatePopupMenu();
    if (hFileMenu == nullptr) {
        return juju_codes::menu_fail;
    }

    HMENU hHelpMenu = CreatePopupMenu();
    if (hHelpMenu == nullptr) {
        return juju_codes::menu_fail;
    }

    if (!AppendMenu(hFileMenu, MF_STRING, static_cast<UINT_PTR>(window_ids::open), L"&Open")) {
        return juju_codes::menu_fail;
    }
    if (!AppendMenu(hFileMenu, MF_SEPARATOR, 0, nullptr)) {
        return juju_codes::menu_fail;
    }
    if (!AppendMenu(hFileMenu, MF_STRING, static_cast<UINT_PTR>(window_ids::exit), L"E&xit")) {
        return juju_codes::menu_fail;
    }

    if (!AppendMenu(hHelpMenu, MF_STRING, static_cast<UINT_PTR>(window_ids::help), L"&About")) {
        return juju_codes::menu_fail;
    }

    if (!AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File")) {
        return juju_codes::menu_fail;
    }
    if (!AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, L"&Help")) {
        return juju_codes::menu_fail;
    }

    if (!SetMenu(window_handle, hMenu)) {
        return juju_codes::menu_fail;
    }

    return juju_codes::success;
}
