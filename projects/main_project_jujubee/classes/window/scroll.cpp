#include NAMES_INCLUDE
#include SCROLL_INCLUDE_PATH

juju::scroll::scroll(SCROLLINFO v_si,SCROLLINFO h_si, SCROLLINFO mouse_si , std::size_t line_height)
    :m_si_v(v_si),m_si_h(h_si),m_mouse_si(mouse_si), m_line_height(line_height) { }



juju::juju_codes juju::scroll::mouse_wheel(HWND hwnd, WPARAM wParam) {
    // Handle mouse wheel scrolling
    int scroll_lines = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA; // How many lines to scroll
    m_mouse_si.nPos = std::clamp(m_mouse_si.nPos - scroll_lines, m_mouse_si.nMin, m_mouse_si.nMax);

    SetScrollInfo(hwnd, SB_VERT, &m_mouse_si, TRUE);

    int delta = m_scroll_position_m - m_mouse_si.nPos;
    m_scroll_position_m = m_mouse_si.nPos;

    // Scroll the window contents
    ScrollWindowEx(hwnd, 0, delta * m_line_height, nullptr, nullptr, nullptr, nullptr, SW_INVALIDATE);

    return juju_codes::success;
}

juju::juju_codes juju::scroll::vertical_drag(HWND hwnd,WPARAM wParam)
{
    // Handle regular scroll events
    switch (LOWORD(wParam)) {
    case SB_LINEUP:
        m_si_v.nPos = std::max(m_si_v.nMin, m_si_v.nPos - 1);
        break;
    case SB_LINEDOWN:
        m_si_v.nPos = std::min(m_si_v.nMax, m_si_v.nPos + 1);
        break;
    case SB_PAGEUP:
        m_si_v.nPos = std::max(m_si_v.nMin, m_si_v.nPos - 25);
        break;
    case SB_PAGEDOWN:
        m_si_v.nPos = std::min(m_si_v.nMax, m_si_v.nPos + 25);
        break;
    case SB_THUMBTRACK:
        m_si_v.nPos = HIWORD(wParam);
        break;
    }

    SetScrollInfo(hwnd, SB_VERT, &m_si_v, TRUE);

    int delta = m_scroll_position_v - m_si_v.nPos;
    m_scroll_position_v = m_si_v.nPos;

    // Scroll the window contents
    ScrollWindowEx(hwnd, 0, delta * m_line_height, nullptr, nullptr, nullptr, nullptr, SW_INVALIDATE);

    return juju_codes::success;
}

juju::juju_codes juju::scroll::horizontal_drag(HWND hwnd,WPARAM wParam)  
{  
    // Handle regular scroll events
    switch (LOWORD(wParam)) {
    case SB_LINELEFT:
        m_si_h.nPos = std::max(m_si_h.nMin, m_si_h.nPos - 1);
        break;
    case SB_LINERIGHT:
        m_si_h.nPos = std::min(m_si_h.nMax, m_si_h.nPos + 1);
        break;
    case SB_PAGELEFT:
        m_si_h.nPos = std::max(m_si_h.nMin, m_si_h.nPos - 25);
        break;
    case SB_PAGERIGHT:
        m_si_h.nPos = std::min(m_si_h.nMax, m_si_h.nPos + 25);
        break;
    case SB_THUMBTRACK:
        m_si_h.nPos = HIWORD(wParam);
        break;
    }

    SetScrollInfo(hwnd, SB_HORZ, &m_si_h, TRUE);

    int delta = m_scroll_position_h - m_si_h.nPos;
    m_scroll_position_h = m_si_h.nPos;

    // Scroll the window contents  
    ScrollWindowEx(hwnd, delta, 0, nullptr, nullptr, nullptr, nullptr, SW_INVALIDATE);  

    return juju_codes::success;  
    
}
