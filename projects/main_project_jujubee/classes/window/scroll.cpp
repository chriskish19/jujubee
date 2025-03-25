#include NAMES_INCLUDE
#include SCROLL_INCLUDE_PATH

juju::scroll::scroll(SCROLLINFO si, std::size_t line_height)
    :m_si(si), m_line_height(line_height) { }



juju::juju_codes juju::scroll::mouse_wheel(HWND hwnd, WPARAM wParam) {
    // Handle mouse wheel scrolling
    int scroll_lines = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA; // How many lines to scroll
    m_si.nPos = std::clamp(m_si.nPos - scroll_lines, m_si.nMin, m_si.nMax);

    SetScrollInfo(hwnd, SB_VERT, &m_si, TRUE);

    int delta = m_vscroll_position - m_si.nPos;
    m_vscroll_position = m_si.nPos;

    // Scroll the window contents
    ScrollWindowEx(hwnd, 0, delta * m_line_height, nullptr, nullptr, nullptr, nullptr, SW_INVALIDATE);

    return juju_codes::success;
}

juju::juju_codes juju::scroll::vertical_drag(HWND hwnd,WPARAM wParam)
{
    // Handle regular scroll events
    switch (LOWORD(wParam)) {
    case SB_LINEUP:
        m_si.nPos = std::max(m_si.nMin, m_si.nPos - 1);
        break;
    case SB_LINEDOWN:
        m_si.nPos = std::min(m_si.nMax, m_si.nPos + 1);
        break;
    case SB_PAGEUP:
        m_si.nPos = std::max(m_si.nMin, m_si.nPos - PAGE_LINES);
        break;
    case SB_PAGEDOWN:
        m_si.nPos = std::min(m_si.nMax, m_si.nPos + PAGE_LINES);
        break;
    case SB_THUMBTRACK:
        m_si.nPos = HIWORD(wParam);
        break;
    }

    SetScrollInfo(hwnd, SB_VERT, &m_si, TRUE);

    int delta = m_vscroll_position - m_si.nPos;
    m_vscroll_position = m_si.nPos;

    // Scroll the window contents
    ScrollWindowEx(hwnd, 0, delta * m_line_height, nullptr, nullptr, nullptr, nullptr, SW_INVALIDATE);

    return juju_codes::success;
}

juju::juju_codes juju::scroll::horizontal_drag(HWND hwnd,WPARAM wParam)
{  
    // Handle regular scroll events
    switch (LOWORD(wParam)) {
    case SB_LINELEFT:
        m_si.nPos = std::max(m_si.nMin, m_si.nPos - 1);
        break;
    case SB_LINERIGHT:
        m_si.nPos = std::min(m_si.nMax, m_si.nPos + 1);
        break;
    case SB_PAGELEFT:
        m_si.nPos = std::max(m_si.nMin, m_si.nPos - PAGE_LINES);
        break;
    case SB_PAGERIGHT:
        m_si.nPos = std::min(m_si.nMax, m_si.nPos + PAGE_LINES);
        break;
    case SB_THUMBTRACK:
        m_si.nPos = HIWORD(wParam);
        break;
    }

    SetScrollInfo(hwnd, SB_HORZ, &m_si, TRUE);

    int delta = m_hscroll_position - m_si.nPos;
    m_hscroll_position = m_si.nPos;
        
    // Scroll the window contents  
    ScrollWindowEx(hwnd, delta, 0, nullptr, nullptr, nullptr, nullptr, SW_INVALIDATE);
    

    return juju_codes::success;
}
