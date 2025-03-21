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
    for (std::size_t i = 0; i < max_single_lines; ++i) {
        m_single_lines.push_back(new RECT{});
    }
}

juju::window_logger::~window_logger() {
    // clean up the vector of rect pointers
    for (auto rect : m_single_lines) {
        if (rect != nullptr) {
            delete rect;
            rect = nullptr;
        }
    }

    // delete created font
    DeleteObject(m_wl_font);
}

juju::juju_codes juju::window_logger::update_vector_of_rects(std::size_t new_size) {
    std::size_t current_size = m_single_lines.size();
    
    if ( current_size > new_size) {
        // shrink 
        std::size_t size_diff = current_size - new_size;

        // delete memory
        for (std::size_t i = 0; i < size_diff; ++i) {
            auto rp = m_single_lines.at(i);
            if (rp != nullptr) {
                delete rp;
                rp = nullptr;
            }
        }

        // then remove entries in vector
        m_single_lines.erase(m_single_lines.begin(), m_single_lines.end() - new_size);
    }
    else {
        // expand
        m_single_lines.resize(new_size, new RECT{});
    }

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

LRESULT juju::window_logger::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        
        case WM_DISPLAYCHANGE:
        {
            // update our variables
            m_sr_x = GetSystemMetrics(SM_CXSCREEN);
            m_sr_y = GetSystemMetrics(SM_CYSCREEN);
            std::size_t new_vector_size = (std::size_t)m_sr_y / m_font_size;
            update_vector_of_rects(new_vector_size);
            break;
        }

        case VK_SCROLL:
        {
            
            break;
        }

        case WM_SIZE:
        {
            InvalidateRect(hwnd, nullptr, TRUE);  // Force redraw on resize
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

            // use custom font object
            SelectObject(hdc, m_wl_font);


            RECT lw_rect;
            if (!GetClientRect(hwnd, &lw_rect)) {
                EndPaint(hwnd, &ps);
                break;
            }

            FillRect(hdc, &lw_rect, (HBRUSH)(COLOR_WINDOW + 1));
            

            UINT window_width = lw_rect.right - lw_rect.left;
            UINT window_height = lw_rect.bottom - lw_rect.top;
            UINT number_of_lines = window_height / m_font_size;

            auto log_vec_p = m_logger.get_logs_vec_pointer();


            LONG top = lw_rect.top;
            LONG bottom = window_width + lw_rect.bottom - m_font_size;

            for (std::size_t i = 0; i < number_of_lines;++i) {
                // log pointer object
                auto log_p = log_vec_p->at(i);

                // message pointer
                string* message_p = log_p->get_message_p();

                // get a rect pointer
                auto wl_rp = m_single_lines.at(i);

                // set the rect memory
                *wl_rp = RECT{ lw_rect.left,top,lw_rect.right,bottom };

                int text_size = DrawText(hdc, message_p->c_str(), -1, wl_rp, DT_LEFT);

                // 
                top += text_size;

                //
                bottom -= text_size;
            }

            

            EndPaint(hwnd, &ps);
         
            break;
        }


    } // end of switch (uMsg)

    // no default switch needed
    return starter::ThisWindowProc(hwnd, uMsg, wParam, lParam);
}
