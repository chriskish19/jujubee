#include NAMES_INCLUDE
#include CODES_INCLUDE_PATH

juju::code_description juju::match_code(juju_codes code)
{
    switch (code) {
        case juju_codes::success:
        {
            return success_code;
        }
        
        case juju_codes::unintialized:
        {
            return uninitialized_code;
        }

        case juju_codes::null_pointer:
        {
            return null_pointer_code;
        }

        case juju_codes::window_problem:
        {
            return window_problem_code;
        }
            
        case juju_codes::exception_thrown:
        {
            return exception_thrown_code;
        }
            
        case juju_codes::empty_file:
        {
            return empty_file_code;
        }

        case juju_codes::string_length_too_long:
        {
            return string_length_too_long_code;
        }

        case juju_codes::to_wide_string_failed:
        {
            return to_wide_string_failed_code;
        }

        case juju_codes::to_narrow_string_failed:
        {
            return to_narrow_string_failed_code;
        }

        case juju_codes::class_already_registered:
        {
            return class_already_registered_code;
        }

        case juju_codes::failed_to_register_class:
        {
            return failed_to_register_class_code;
        }

        case juju_codes::hwnd_fail:
        {
            return hwnd_fail_code;
        }
            
        case juju_codes::show_window_fail:
        {
            return show_window_fail_code;
        }
            
        case juju_codes::menu_fail:
        {
            return menu_fail_code;
        }
           
        case juju_codes::lb_add_string_fail:
        {
            return lb_add_string_fail_code;
        }

        case juju_codes::lb_get_selection_fail:
        {
            return lb_get_selection_fail_code;
        }

        case juju_codes::set_icon_fail:
        {
            return set_icon_fail_code;
        }

        // file errors
        case juju_codes::file_open_fail:
        {
            return file_open_fail_code;
        }

        case juju_codes::permission_denied:
        {
            return permission_denied_code;
        }

        case juju_codes::no_such_file_or_directory:
        {
            return no_such_file_or_directory_code;
        }

        case juju_codes::file_exists:
        {
            return file_exists_code;
        }

        case juju_codes::is_a_directory:
        {
            return is_a_directory_code;
        }

        case juju_codes::not_a_directory:
        {
            return not_a_directory_code;
        }

        case juju_codes::device_or_resource_busy:
        {
            return device_or_resource_code;
        }

        case juju_codes::invalid_argument:
        {
            return invalid_argument_code;
        }

        case juju_codes::directory_not_empty:
        {
            return directory_not_empty_code;
        }

        case juju_codes::file_too_large:
        {
            return file_too_large_code;
        }

        case juju_codes::io_error:
        {
            return io_error_code;
        }

        case juju_codes::no_space_on_device:
        {
            return no_space_on_device_code;
        }

        case juju_codes::too_many_files_open:
        {
            return too_many_files_open_code;
        }

        default:
            return unknown_code;
    }
}

juju::juju_codes juju::std_error_code_convert(std::error_code ec) {
    
    switch (static_cast<std::errc>(ec.value())) {
        case std::errc::permission_denied:
            return juju::juju_codes::permission_denied;
        case std::errc::no_such_file_or_directory:
            return juju::juju_codes::no_such_file_or_directory;
        case std::errc::file_exists:
            return juju::juju_codes::file_exists;
        case std::errc::is_a_directory:
            return juju::juju_codes::is_a_directory;
        case std::errc::not_a_directory:
            return juju::juju_codes::not_a_directory;
        case std::errc::device_or_resource_busy:
            return juju::juju_codes::device_or_resource_busy;
        case std::errc::invalid_argument:
            return juju::juju_codes::invalid_argument;
        case std::errc::directory_not_empty:
            return juju::juju_codes::directory_not_empty;
        case std::errc::file_too_large:
            return juju::juju_codes::file_too_large;
        case std::errc::io_error:
            return juju::juju_codes::io_error;
        case std::errc::no_space_on_device:
            return juju::juju_codes::no_space_on_device;
        case std::errc::too_many_files_open:
            return juju::juju_codes::too_many_files_open;
        default:
            return juju::juju_codes::std_error_convert_unknown;
    }
}