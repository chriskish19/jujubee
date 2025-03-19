#include NAMES_INCLUDE
#include UTILITIES_INCLUDE_PATH

UINT juju_api::get_window_width(HWND window_handle)
{
    RECT rc = {};
    if (GetClientRect(window_handle, &rc) == FALSE) {
        throw juju::jujubee_error(juju::getclientrect_fail_code);
    }

    return rc.right - rc.left;
}

UINT juju_api::get_window_height(HWND window_handle) {
    RECT rc = {};
    if (GetClientRect(window_handle, &rc) == FALSE) {
        throw juju::jujubee_error(juju::getclientrect_fail_code);
    }

    return rc.bottom - rc.top;
}

UINT juju_api::get_window_width(HWND window_handle,juju::juju_codes* code) noexcept
{
    RECT rc = {};
    if (GetClientRect(window_handle, &rc) == FALSE) {
        *code = juju::juju_codes::getclientrect_fail;
        return 0;
    }

    return rc.right - rc.left;
}

UINT juju_api::get_window_height(HWND window_handle, juju::juju_codes* code) noexcept
{
    RECT rc = {};
    if (GetClientRect(window_handle, &rc) == FALSE) {
        *code = juju::juju_codes::getclientrect_fail;
        return 0;
    }

    return rc.bottom - rc.top;
}
