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

        default:
            return unknown_code;
    }
}
