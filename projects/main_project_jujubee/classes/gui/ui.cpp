#include "ui.hpp"
#include NAMES_INCLUDE
#include UI_INCLUDE_PATH

juju::ui::ui(HWND window, HMENU menu, HINSTANCE hinst, LPVOID lp)
{
	m_front_bd.window = window;
	m_front_bd.menu = menu;
	m_front_bd.hinst = hinst;
	m_front_bd.lpParam = lp;
	m_front_bd.button_caller = [this](button_state bs) {
		this->front_button_action(bs);
	};

	m_front_b = button(m_front_bd);

	m_front_b.create();
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
