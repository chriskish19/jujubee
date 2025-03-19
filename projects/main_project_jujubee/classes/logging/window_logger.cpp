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

    // allocate rects
    for ( )
}

juju::juju_codes juju::window_logger::update_vector_of_rects() {

}

juju::juju_codes juju::window_logger::setup_font(std::size_t font_size) {
    
    // Create and select a custom font
    m_wl_font = CreateFont(font_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, ROS("Arial"));
    
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

LRESULT juju::window_logger::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_DISPLAYCHANGE:
        {
            // update our variables
            m_sr_x = GetSystemMetrics(SM_CXSCREEN);
            m_sr_y = GetSystemMetrics(SM_CYSCREEN);
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT lw_rect;
            if (!GetClientRect(hwnd, &lw_rect)) {
                EndPaint(hwnd, &ps);
                break;
            }

            TEXTMETRIC tm;
            if (!GetTextMetrics(hdc, &tm)) {
                EndPaint(hwnd, &ps);
                break;
            }

            UINT font_height = tm.tmHeight;
            UINT window_width = lw_rect.right - lw_rect.left;
            UINT window_height = lw_rect.bottom - lw_rect.top;
            UINT number_of_lines = window_height / font_height;

            auto log_vec_p = m_logger.get_logs_vec_pointer();
            for (std::size_t i = 0; i < number_of_lines;++i) {
                auto log_p = log_vec_p->at(i);
                string* message_p = log_p->get_message_p();

                // left , top , right , bottom
                RECT single_line = RECT{lw_rect.}

                DrawText(hdc, message_p->c_str(), -1, &lw_rect, DT_LEFT);
            }

            

            EndPaint(hwnd, &ps);
         
            break;
        }


    } // end of switch (uMsg)

    // no default switch needed
    return starter::ThisWindowProc(hwnd, uMsg, wParam, lParam);
}
