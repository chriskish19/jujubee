#include NAMES_INCLUDE
#include UI_INCLUDE_PATH

juju::ui::ui(HWND window, HMENU menu, HINSTANCE hinst, LPVOID lp)
{

    // front button setup
    m_front_bd.window = window;
    m_front_bd.menu = (HMENU)window_ids::b_front;
    m_front_bd.hinst = hinst;
    m_front_bd.lpParam = lp;
    m_front_bd.button_caller = [this](button_state bs) {
        this->front_button_action(bs);
        };

    m_front_b = button(m_front_bd);
    m_front_b.create();

    // refresh button setup
    m_refresh_bd.window = window;
    m_refresh_bd.menu = (HMENU)window_ids::b_refresh;
    m_refresh_bd.hinst = hinst;
    m_refresh_bd.lpParam = lp;
    m_refresh_bd.button_caller = [this](button_state bs) {
        this->refresh_button_action(bs);
        };

    m_refresh_b = button(m_refresh_bd);
    m_refresh_b.create();

    // front listbox setup
    m_front_lb_ld.window = window;
    m_front_lb_ld.menu = (HMENU)window_ids::lb_box;
    m_front_lb_ld.hinst = hinst;
    m_front_lb_ld.lpParam = lp;
    m_front_lb_ld.listbox_caller = [this](listbox_commands lc) {
        this->front_listbox_action(lc);
        };

    m_front_lb = listbox(m_front_lb_ld);
    m_front_lb.create();

}
void juju::ui::front_button_action(button_state bs)
{
	switch (bs) {
		case button_state::rest:
		{
			return;
		}

		case button_state::pressed:
		{
			MessageBox(nullptr, L"Button Clicked!", L"Notification", MB_OK | MB_ICONINFORMATION);
			break;
		}

		case button_state::released:
		{
			break;
		}

		case button_state::holding:
		{
			break;
		}

	default:
		break;
	}
}

void juju::ui::refresh_button_action(button_state bs)
{
	switch (bs) {
	    case button_state::rest:
	    {
		    return;
	    }

	    case button_state::pressed:
	    {
		    MessageBox(nullptr, L"Refresh Button Clicked!", L"Notification", MB_OK | MB_ICONINFORMATION);
		    break;
	    }

	    case button_state::released:
	    {
		    break;
	    }

	    case button_state::holding:
	    {
		    break;
	    }

	default:
		break;
	}
}

void juju::ui::front_listbox_action(listbox_commands lc) {
    switch (lc) {
        case listbox_commands::none:
            // Handle none
            break;
        case listbox_commands::add_string:
            // Handle add_string
            break;
        case listbox_commands::insert_string:
            // Handle insert_string
            break;
        case listbox_commands::delete_string:
            // Handle delete_string
            break;
        case listbox_commands::reset_content:
            // Handle reset_content
            break;
        case listbox_commands::get_cursel:
            // Handle get_cursel
            break;
        case listbox_commands::set_cursel:
            // Handle set_cursel
            break;
        case listbox_commands::get_sel:
            // Handle get_sel
            break;
        case listbox_commands::set_sel:
            // Handle set_sel
            break;
        case listbox_commands::get_selcount:
            // Handle get_selcount
            break;
        case listbox_commands::get_selitems:
            // Handle get_selitems
            break;
        case listbox_commands::get_text:
            // Handle get_text
            break;
        case listbox_commands::get_textlen:
            // Handle get_textlen
            break;
        case listbox_commands::set_itemdata:
            // Handle set_itemdata
            break;
        case listbox_commands::get_itemdata:
            // Handle get_itemdata
            break;
        case listbox_commands::find_string:
            // Handle find_string
            break;
        case listbox_commands::find_stringexact:
            // Handle find_stringexact
            break;
        case listbox_commands::set_horizontalextent:
            // Handle set_horizontalextent
            break;
        case listbox_commands::get_horizontalextent:
            // Handle get_horizontalextent
            break;
        case listbox_commands::set_columnwidth:
            // Handle set_columnwidth
            break;
        case listbox_commands::set_itemheight:
            // Handle set_itemheight
            break;
        case listbox_commands::get_itemheight:
            // Handle get_itemheight
            break;
        case listbox_commands::set_locale:
            // Handle set_locale
            break;
        case listbox_commands::get_locale:
            // Handle get_locale
            break;
        case listbox_commands::get_count:
            // Handle get_count
            break;
        case listbox_commands::dir:
            // Handle dir
            break;
        case listbox_commands::set_caretindex:
            // Handle set_caretindex
            break;
        case listbox_commands::get_caretindex:
            // Handle get_caretindex
            break;
        case listbox_commands::set_topindex:
            // Handle set_topindex
            break;
        case listbox_commands::get_topindex:
            // Handle get_topindex
            break;
    default:
        // Handle unknown command
        break;
    }
}