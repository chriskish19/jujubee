/***********************************************
*
*
*
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH

#define LB_MAX_STRING 256

namespace juju {
    enum class listbox_commands {
        none = 0,

        // Adding & Removing Items
        add_string,         // Adds a string to the list box.
        insert_string,      // Inserts a string at a specific index.
        delete_string,      // Removes an item at a specified index.
        reset_content,      // Removes all items from the list box.

        // Selection Handling
        get_cursel,         // Gets the index of the currently selected item (single-selection list).
        set_cursel,         // Sets the selection to a specific index (single-selection list).
        get_sel,            // Gets selection state of an item (multi-selection list).
        set_sel,            // Selects/Deselects an item (multi-selection list).
        get_selcount,       // Gets the number of selected items (multi-selection list).
        get_selitems,       // Gets an array of selected items (multi-selection list).

        // Retrieving & Modifying Items
        get_text,           // Gets the text of an item.
        get_textlen,        // Gets the length of an item's text.
        set_itemdata,       // Sets application-defined data for an item.
        get_itemdata,       // Retrieves application-defined data for an item.
        find_string,        // Finds an item that starts with a specified string.
        find_stringexact,   // Finds an exact string match.

        // Size & Appearance
        set_horizontalextent, // Sets horizontal scroll width.
        get_horizontalextent, // Gets horizontal scroll width.
        set_columnwidth,      // Sets the width of columns in a multi-column list box.
        set_itemheight,       // Sets the height of an item (for owner-drawn list boxes).
        get_itemheight,       // Gets the height of an item.

        // Miscellaneous
        set_locale,         // Sets the locale for sorting.
        get_locale,         // Gets the locale for sorting.
        get_count,          // Gets the number of items in the list box.
        dir,                // Adds files matching a specified mask (e.g., *.txt).

        // Extended Features
        set_caretindex,     // Sets focus to a specific item.
        get_caretindex,     // Gets the index of the focused item.
        set_topindex,       // Scrolls the list so a specified item is at the top.
        get_topindex        // Gets the index of the topmost visible item.
    };

	struct listbox_description {
		string class_name = ROS("LISTBOX");
		string window_name = ROS("LB1");
		DWORD style_flags = 0;
		std::size_t xPos = 0;
		std::size_t yPos = 0;
		std::size_t width = 0;
		std::size_t height = 0;
		HWND window = nullptr;
		HMENU menu = nullptr;
		HINSTANCE hinst = GetModuleHandle(NULL);
		LPVOID lpParam = nullptr;
		std::function<void(listbox_commands)> listbox_caller = nullptr;
	};
	
	
	class listbox {
	public:
		listbox() = default;
        listbox(listbox_description lbd);

        juju_codes create();

        juju_codes add_string(const string& list_message);
        string get_selection(juju_codes* code);

        listbox_description get_lbd() { return m_lbd; }
        HWND get_listbox_handle() { return m_lb_handle; }
        listbox_commands get_command() { return m_command; }
	protected:
        listbox_description m_lbd = {};
        HWND m_lb_handle = nullptr;
        listbox_commands m_command = listbox_commands::none;
	};
}