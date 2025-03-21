#include NAMES_INCLUDE
#include SCROLL_INCLUDE_PATH

juju::scroll::scroll(SCROLLINFO si, HWND window_handle) {
    SetScrollInfo(window_handle, SB_VERT, &si, TRUE);
}