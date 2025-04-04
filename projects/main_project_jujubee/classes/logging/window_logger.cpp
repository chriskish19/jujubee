#include NAMES_INCLUDE
#include WINDOWLOGGER_INCLUDE_PATH

juju::window_logger::window_logger()
{
    m_c_name = ROS("SYSTEM_LOGGER");
    m_title = ROS("System Log Window");

    juju_codes code = setup_font(m_font_size);
    output_code(code);

    // number of single line rects to allocate and reuse
    UINT max_single_lines = static_cast<UINT>(m_sr_y) / m_font_size;

    // allocate vector
    m_single_lines_p = new std::vector<RECT*>;

    // allocate rects
    for (std::size_t i = 0; i < max_single_lines; ++i) {
        m_single_lines_p->push_back(new RECT{});
    }
}

juju::window_logger::~window_logger() {
    // clean up the vector of rect pointers
    for (auto rect : *m_single_lines_p) {
        if (rect != nullptr) {
            delete rect;
            rect = nullptr;
        }
    }

    if (m_single_lines_p != nullptr) {
        delete m_single_lines_p;
        m_single_lines_p = nullptr;
    }

    // delete created font
    DeleteObject(m_wl_font);
}

juju::juju_codes juju::window_logger::window_settings() {
    m_wc.lpfnWndProc = WindowProc;
    m_wc.hInstance = m_hinst;
    m_wc.lpszClassName = m_c_name.c_str();

    // my computer icon
    m_wc.hIcon = ExtractIcon(m_hinst, ROS("shell32.dll"), 15);

    if (RegisterClass(&m_wc) == FALSE) {
        return juju_codes::failed_to_register_class;
    }
    return juju_codes::success;
}

juju::juju_codes juju::window_logger::create_window() {
    m_window_handle = CreateWindowEx(
        0,                                              // Optional window styles.
        m_c_name.c_str(),                               // Window class
        m_title.c_str(),                                // Window text
        WS_OVERLAPPEDWINDOW |                           // Window style
        WS_HSCROLL | WS_VSCROLL,                        // scroll bars

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

juju::juju_codes juju::window_logger::message_pump()
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

juju::juju_codes juju::window_logger::update_vector_of_rects(std::size_t new_size) {
    std::size_t current_size = m_single_lines_p->size();
    
    if ( current_size > new_size) {
        // shrink 
        std::size_t size_diff = current_size - new_size;

        // delete memory
        for (std::size_t i = 0; i < size_diff; ++i) {
            auto rp = m_single_lines_p->at(i);
            if (rp != nullptr) {
                delete rp;
                rp = nullptr;
            }
        }

        // then remove entries in vector
        m_single_lines_p->erase(m_single_lines_p->begin(), m_single_lines_p->end() - new_size);
    }
    else {
        // expand
        m_single_lines_p->resize(new_size, new RECT{});
    }

    return juju_codes::success;
}

juju::juju_codes juju::window_logger::paint_window(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // get a si object
    SCROLLINFO si = {};

    // Get vertical scroll bar position.
    si.cbSize = sizeof(si);
    si.fMask = SIF_POS;
    GetScrollInfo(hwnd, SB_VERT, &si);
    m_scrolling.set_v_position(si.nPos);

    // Get horizontal scroll bar position.
    GetScrollInfo(hwnd, SB_HORZ, &si);
    m_scrolling.set_h_position(si.nPos);

    // get positions
    int xPos = m_scrolling.get_h_position();
    int yChar = m_scrolling.get_vertical_unit();
    int yPos = m_scrolling.get_v_position();

    RECT lw_rect;
    if (!GetClientRect(hwnd, &lw_rect)) {
        EndPaint(hwnd, &ps);
        return juju_codes::getclientrect_fail;
    }

    FillRect(hdc, &lw_rect, (HBRUSH)(COLOR_WINDOW + 1));

    auto log_vec_p = m_logger.get_logs_vec_pointer();

    LONG window_width = lw_rect.right - lw_rect.left;
    LONG top = lw_rect.top;
    LONG bottom = window_width + lw_rect.bottom;

    // how many lines to print
    std::size_t lines_number = window_width / yChar;


    std::size_t FirstLine = static_cast<std::size_t>(std::abs(yPos));
    std::size_t LastLine = std::clamp(FirstLine + lines_number,(std::size_t)0,(std::size_t)LOGGER_LINES);

    LONG left = lw_rect.left - xPos;
    LONG right = lw_rect.right + xPos;

    for (std::size_t i = FirstLine; i < LastLine and i < log_vec_p->size(); ++i) {

        // log pointer object
        auto log_p = log_vec_p->at(i);

        // make a copy
        string message_p = log_p->get_message_copy();

        // get a rect pointer
        auto wl_rp = get_rect_p();

        // set the rect memory
        *wl_rp = RECT{ left,top,right,bottom };

        // display the message
        int text_size = DrawText(hdc, message_p.c_str(), -1, wl_rp, DT_LEFT);

        // 
        top += text_size;

        //
        bottom -= text_size;
    }

    EndPaint(hwnd, &ps);

    return juju_codes::success;
}

RECT* juju::window_logger::get_rect_p()
{
    if (m_slvp_index < m_single_lines_p->size() - 1) {
        // increment
        m_slvp_index++;
    }
    else {
        // reset
        m_slvp_index = 0;
    }

    return m_single_lines_p->at(m_slvp_index);
}

juju::juju_codes juju::window_logger::update_logger_window()
{
    InvalidateRect(m_window_handle, get_rect_p(), TRUE);
    return juju_codes::success;
}

juju::juju_codes juju::window_logger::setup_font(std::size_t font_size) {
    
    // Create and select a custom font
    m_wl_font = CreateFont(
        font_size,                 // Height
        0,                         // Width (0 for default)
        0,                         // Escapement
        0,                         // Orientation
        FW_BOLD,                   // Weight (FW_NORMAL, FW_BOLD, etc.)
        FALSE,                     // Italic
        FALSE,                     // Underline
        FALSE,                     // Strikeout
        DEFAULT_CHARSET,           // Character set
        OUT_DEFAULT_PRECIS,        // Output precision
        CLIP_DEFAULT_PRECIS,       // Clipping precision
        ANTIALIASED_QUALITY,       // Quality
        DEFAULT_PITCH | FF_SWISS,  // Pitch and family
        ROS("Arial")               // Font face name
    );

    if (m_wl_font == nullptr) {
        return juju_codes::null_pointer;
    }
    
    return juju_codes::success;
}

juju::juju_codes juju::window_logger::go() 
{
    {
        juju_codes code = window_settings();
        output_code(code);
    }

    {
        juju_codes code = create_window();
        output_code(code);
    }

    {
        juju_codes code = message_pump();
        output_code(code);
    }

    return juju_codes::success;
}

juju::juju_codes juju::window_logger::wait_until_init()
{
    // wait here
    std::mutex local_mtx;
    std::unique_lock<std::mutex> local_lock(local_mtx);
    m_wait_cv.wait(local_lock, [this]
        {
            return m_wait_b.load();
        });
    
    return juju_codes::success;
}

juju::juju_codes juju::window_logger::wait_until_closed()
{
    return juju_codes::success;
}

juju::juju_codes juju::window_logger::send_message(const string& message)
{
    m_logger.add_message(message);
    update_logger_window();
    return juju_codes::success;
}

LRESULT juju::window_logger::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        
        case WM_CREATE:
        {
            m_scrolling.pre_window_setup(hwnd, m_wl_font);
            break;
        }

        case WM_SHOWWINDOW:
        {
            // main window logger window was successfully created
            if (hwnd == m_window_handle) {

                // tell waiting thread its safe to procceed...
                m_wait_b.store(true);
                m_wait_cv.notify_all();
            }
            break;
        }

        case WM_DISPLAYCHANGE:
        {
            // update our variables
            m_sr_x = GetSystemMetrics(SM_CXSCREEN);
            m_sr_y = GetSystemMetrics(SM_CYSCREEN);
            std::size_t new_vector_size = (std::size_t)m_sr_y / m_font_size;
            update_vector_of_rects(new_vector_size);
            break;
        }

        case WM_HSCROLL:
        {
            m_scrolling.horizontal_drag(hwnd, wParam);
            break;
        }

        case WM_VSCROLL:
        {
            m_scrolling.vertical_drag(hwnd,wParam);
            break;
        }

        case WM_SIZE:
        {
            m_scrolling.window_size_change(hwnd, lParam);
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
            paint_window(hwnd);
            break;
        }


    } // end of switch (uMsg)

    // no default switch needed
    return starter::ThisWindowProc(hwnd, uMsg, wParam, lParam);
}
