#include NAMES_INCLUDE
#include ERROR_INCLUDE_PATH



void juju::jujubee_error::vs_output_full_message() const
{
	string output_message = m_code.m_description + ROS("|") + m_location;
	
	OutputDebugString(output_message.c_str());
}

juju::string juju::jujubee_error::full_message() const
{
    return m_code.m_description + ROS("|") + m_location;
}

juju::string juju::get_location(std::source_location sl)
{
    std::string function_name = sl.function_name();
    std::string line = std::to_string(sl.line());
    std::string column = std::to_string(sl.column());
    std::string file_name = sl.file_name();

    std::string temp = std::format("File name: {} \n - column: {} \n - line: {} \n - function name: {} \n", file_name, column, line, function_name);
#if USING_STR
    return temp;
#endif

#if USING_WSTR
    juju_codes code;
    string wide_str = to_wide_string(temp, &code);
    output_code(code);
    return wide_str;
#endif
}

std::wstring juju::to_wide_string(const char* narrow, juju_codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*

    std::size_t mbsrtowcs( wchar_t* dst,
                       const char** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to wide character array where the results will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated multibyte string
    len 	- 	number of wide characters available in the array pointed to by dst
    ps 	- 	pointer to the conversion state object

    */

    // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    /*

    On success, returns the number of wide characters, excluding the terminating L'\0',
    written to the character array. If dst is a null pointer, returns the number of wide
    characters that would have been written given unlimited length.

    */
    std::size_t length = 1 + std::mbsrtowcs(nullptr, &narrow, 0, &state);


    wchar_t* buffer = nullptr;

    // stack buffer
    wchar_t stack_buffer[max_string_buffer];
    buffer = stack_buffer;
    boolean heap_alloc = false;

    // if length is greater than max_string_buffer, we allocate memory:
    if (length > max_string_buffer) {
        *code_p = juju_codes::string_length_too_long;

        buffer = new wchar_t[length];

        heap_alloc = true;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::mbsrtowcs(buffer, &narrow, length, &state);

    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = juju_codes::to_wide_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::wstring temp_buffer(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }

    *code_p = juju_codes::success;

    // return the wide string using the buffer
    return temp_buffer;
}

std::wstring juju::to_wide_string(const std::string& narrow, juju_codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*

    std::size_t mbsrtowcs( wchar_t* dst,
                       const char** src,
                       std::size_t len,
                       std::mbstate_t* ps );

    dst 	- 	pointer to wide character array where the results will be stored
    src 	- 	pointer to pointer to the first element of a null-terminated multibyte string
    len 	- 	number of wide characters available in the array pointed to by dst
    ps 	- 	pointer to the conversion state object

    */

    // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    const char* temp = narrow.c_str();

    /*

    On success, returns the number of wide characters, excluding the terminating L'\0',
    written to the character array. If dst is a null pointer, returns the number of wide
    characters that would have been written given unlimited length.

    */
    std::size_t length = 1 + std::mbsrtowcs(nullptr, &temp, 0, &state);


    wchar_t* buffer = nullptr;

    // stack buffer
    wchar_t stack_buffer[max_string_buffer];
    buffer = stack_buffer;
    bool heap_alloc = false;

    // if length is greater than max_string_buffer, allocate more memory.
    if (length > max_string_buffer) {
        *code_p = juju_codes::string_length_too_long;

        buffer = new wchar_t[length];

        heap_alloc = true;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::mbsrtowcs(buffer, &temp, length, &state);

    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = juju_codes::to_wide_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::wstring temp_buffer(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }

    *code_p = juju_codes::success;


    // return the wide string using the buffer
    return temp_buffer;
}

std::string juju::to_narrow_string(const wchar_t* wide, juju_codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*
   *
   Converts a sequence of wide characters from the array whose first element is pointed to by *src
   to its narrow multibyte representation that begins in the conversion state described by *ps.
   If dst is not null, converted characters are stored in the successive elements of the char array
   pointed to by dst. No more than len bytes are written to the destination array.


   std::size_t wcsrtombs( char* dst,
                      const wchar_t** src,
                      std::size_t len,
                      std::mbstate_t* ps );

   dst 	- 	pointer to narrow character array where the multibyte characters will be stored
   src 	- 	pointer to pointer to the first element of a null-terminated wide string
   len 	- 	number of bytes available in the array pointed to by dst
   ps 	    - 	pointer to the conversion state object

   */

   // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    // get the wide string length, does not include '\0'
    // returns the length in bytes
    std::size_t length = 1 + std::wcsrtombs(nullptr, &wide, 0, &state);

    char* buffer = nullptr;
    char temp_buffer[max_string_buffer];
    bool heap_alloc = false;


    // if length is greater than max_string_buffer, we have an error:
    // use new to allocate memory to compensate 
    if (length > max_string_buffer) {
        *code_p = juju_codes::string_length_too_long;

        buffer = new char[length];

        heap_alloc = true;
    }
    else {
        buffer = temp_buffer;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::wcsrtombs(buffer, &wide, length, &state);


    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = juju_codes::to_narrow_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::string temp_buffer_str(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }


    *code_p = juju_codes::success;

    // return the narrow string using the buffer
    return temp_buffer_str;
}

std::string juju::to_narrow_string(const std::wstring& wide, juju_codes* code_p)
{
    // return nothing if code is nullptr
    if (code_p == nullptr) {
        return {};
    }


    /*
   *
   Converts a sequence of wide characters from the array whose first element is pointed to by *src
   to its narrow multibyte representation that begins in the conversion state described by *ps.
   If dst is not null, converted characters are stored in the successive elements of the char array
   pointed to by dst. No more than len bytes are written to the destination array.


   std::size_t wcsrtombs( char* dst,
                      const wchar_t** src,
                      std::size_t len,
                      std::mbstate_t* ps );

   dst 	- 	pointer to narrow character array where the multibyte characters will be stored
   src 	- 	pointer to pointer to the first element of a null-terminated wide string
   len 	- 	number of bytes available in the array pointed to by dst
   ps 	    - 	pointer to the conversion state object

   */

   // Create a fresh conversion state per thread
    std::mbstate_t state = std::mbstate_t();

    const wchar_t* temp = wide.c_str();

    // get the wide string length, does not include '\0'
    // returns the length in bytes
    std::size_t length = 1 + std::wcsrtombs(nullptr, &temp, 0, &state);

    char* buffer = nullptr;
    char temp_buffer[max_string_buffer];
    bool heap_alloc = false;


    // if length is greater than max_string_buffer, we have an error:
    // use new to allocate memory to compensate 
    if (length > max_string_buffer) {
        *code_p = juju_codes::string_length_too_long;

        buffer = new char[length];

        heap_alloc = true;
    }
    else {
        buffer = temp_buffer;
    }


    // according to documentation:
    /*

    The following functions should not be called from multiple threads without synchronization with
    the std::mbstate_t* argument of a null pointer due to possible data races: std::mbrlen, std::mbrtowc,
    std::mbsrtowcs, std::mbtowc, std::wcrtomb, std::wcsrtombs, std::wctomb.

    */
    std::size_t error_code = std::wcsrtombs(buffer, &temp, length, &state);


    // On conversion error (if invalid wide character was encountered), 
    // returns static_cast<std::size_t>(-1), stores EILSEQ in errno, and leaves *ps in unspecified state. 
    if (error_code == std::size_t(-1)) {
        *code_p = juju_codes::to_narrow_string_failed;

        if (heap_alloc and buffer != nullptr) {
            delete[] buffer;
        }

        // returns an empty string
        return {};
    }

    std::string temp_buffer_str(buffer);

    if (heap_alloc and buffer != nullptr) {
        delete[] buffer;
    }


    *code_p = juju_codes::success;

    // return the narrow string using the buffer
    return temp_buffer_str;
}

void juju::output_code(juju_codes code)
{

    switch (code) {
        case juju_codes::success:
        {
            return;
        }

        case juju_codes::null_pointer:
        {
            output_window(null_pointer_description);
            break;
        }

        case juju_codes::window_problem:
        {
            output_window(window_problem_description);
            break;
        }

        case juju_codes::exception_thrown:
        {
            output_window(exception_thrown_description);
            break;
        }

        case juju_codes::empty_file:
        {
            output_window(empty_file_description);
            break;
        }

        case juju_codes::string_length_too_long:
        {
            output_window(string_length_too_long_description);
            break;
        }

        case juju_codes::to_wide_string_failed:
        {
            output_window(to_wide_string_failed_description);
            break;
        }


        case juju_codes::to_narrow_string_failed:
        {
            output_window(to_narrow_string_failed_description);
            break;
        }

        case juju_codes::class_already_registered:
        {
            output_window(class_already_registered_description);
            break;
        }

        case juju_codes::failed_to_register_class:
        {
            output_window(failed_to_register_class_description);
            break;
        }

        case juju_codes::hwnd_fail:
        {
            output_window(hwnd_fail_description);
            break;
        }

        case juju_codes::show_window_fail:
        {
            output_window(show_window_fail_description);
            break;
        }

        case juju_codes::menu_fail:
        {
            output_window(menu_fail_description);
            break;
        }

        case juju_codes::getclientrect_fail:
        {
            output_window(getclientrect_fail_description);
            break;
        }

        case juju_codes::lb_add_string_fail:
        {
            output_window(lb_add_string_fail_description);
            break;
        }

        case juju_codes::lb_get_selection_fail:
        {
            output_window(lb_get_selection_fail_description);
            break;
        }

        case juju_codes::file_open_fail:
        {
            output_window(file_open_fail_description);
            break;
        }

        case juju_codes::std_error_convert_unknown:
        {
            output_window(std_error_convert_unknown_description);
            break;
        }

        case juju_codes::permission_denied:
        {
            output_window(permission_denied_description);
            break;
        }

        case juju_codes::no_such_file_or_directory:
        {
            output_window(no_such_file_or_directory_description);
            break;
        }

        case juju_codes::file_exists:
        {
            output_window(file_exists_description);
            break;
        }

        case juju_codes::is_a_directory:
        {
            output_window(is_a_directory_description);
            break;
        }

        case juju_codes::not_a_directory:
        {
            output_window(not_a_directory_description);
            break;
        }

        case juju_codes::device_or_resource_busy:
        {
            output_window(device_or_resource_busy_description);
            break;
        }

        case juju_codes::invalid_argument:
        {
            output_window(invalid_argument_description);
            break;
        }

        case juju_codes::directory_not_empty:
        {
            output_window(directory_not_empty_description);
            break;
        }

        case juju_codes::file_too_large:
        {
            output_window(file_too_large_description);
            break;
        }

        case juju_codes::io_error:
        {
            output_window(io_error_description);
            break;
        }

        case juju_codes::no_space_on_device:
        {
            output_window(no_space_on_device_description);
            break;
        }

        case juju_codes::too_many_files_open:
        {
            output_window(too_many_files_open_description);
            break;
        }

        default:
            output_window(unknown_description);
    }
}



void juju::output_window(string message, string title)
{
    MessageBox(
        nullptr,                // No owner window
        message.c_str(),        // Error message
        title.c_str(),          // Title of the message box
        MB_OK | MB_ICONERROR    // OK button with an error icon
    );
}

