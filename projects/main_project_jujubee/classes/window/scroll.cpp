#include NAMES_INCLUDE
#include SCROLL_INCLUDE_PATH

juju::scroll::scroll(HWND window_handle, std::size_t max_lines, std::size_t max_line_length)
:m_window_handle(window_handle),m_max_lines(max_lines){
    SCROLLINFO si = {};

    // Set the vertical scrolling range and page size
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE;
    si.nMin = 0;
    si.nMax = 99;
    si.nPage = m_max_lines;
    SetScrollInfo(m_window_handle, SB_VERT, &si, TRUE);

    // Set the horizontal scrolling range and page size. 
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE;
    si.nMin = 0;
    si.nMax = 99;
    si.nPage = max_line_length;
    SetScrollInfo(m_window_handle, SB_HORZ, &si, TRUE);
}

juju::juju_codes juju::scroll::mouse_wheel() {
    int wheel_delta = WHEEL_DELTA;


}