/***********************************************
* 
* File: types.hpp
*
* Purpose: Manage types throughout jujubee.
*
* Project: jujubee
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include STL_INCLUDE_PATH
#include WINDOWS_INCLUDE_PATH


#if defined(UNICODE) || defined(_UNICODE)


namespace juju {
	using string = std::wstring;
	using ostringstream = std::wostringstream;
	using character = wchar_t;
	using w32_str_p = LPWSTR;			// wchar_t*
	using w32_str_cp = LPCWSTR;			// const wchar_t* (read only)
	namespace fs = std::filesystem;		// for less typing
	using ofstream = std::wofstream;
}

namespace juju_api {
	using string = std::wstring;
	using ostringstream = std::wostringstream;
	using character = wchar_t;
	using w32_str_p = LPWSTR;			// wchar_t*
	using w32_str_cp = LPCWSTR;			// const wchar_t* (read only)
	namespace fs = std::filesystem;		// for less typing
	using ofstream = std::wofstream;
}

namespace juju_file_system {
	using string = std::string;
	using ostringstream = std::wostringstream;
	using character = char;
	namespace fs = std::filesystem;		// for less typing
	using fstream = std::fstream;
}

namespace jfs = juju_file_system;


namespace juju_test {
	using string = std::wstring;
	using ostringstream = std::wostringstream;
	using character = wchar_t;
	using w32_str_p = LPWSTR;			// wchar_t*
	using w32_str_cp = LPCWSTR;			// const wchar_t* (read only)
	namespace fs = std::filesystem;		// for less typing
	using ofstream = std::wofstream;
}

namespace jt = juju_test;

#else



namespace juju {
	using string = std::string;
	using ostringstream = std::ostringstream;
	using character = char;
	using w32_str_p = LPSTR;			// char*
	using w32_str_cp = LPCSTR;			// const char* (read only)
	namespace fs = std::filesystem;		// for less typing
	using ofstream = std::ofstream;
}

namespace juju_api {
	using string = std::string;
	using ostringstream = std::ostringstream;
	using character = char;
	using w32_str_p = LPSTR;			// char*
	using w32_str_cp = LPCSTR;			// const char* (read only)
	namespace fs = std::filesystem;		// for less typing
	using ofstream = std::ofstream;
}

namespace juju_file_system {
	using string = std::string;
	using ostringstream = std::ostringstream;
	using character = char;
	namespace fs = std::filesystem;		// for less typing
	using ofstream = std::ofstream;
}

namespace jfs = juju_file_system;

namespace juju_test {
	using string = std::string;
	using ostringstream = std::ostringstream;
	using character = char;
	using w32_str_p = LPSTR;			// char*
	using w32_str_cp = LPCSTR;			// const char* (read only)
	namespace fs = std::filesystem;		// for less typing
	using ofstream = std::ofstream;
}

namespace jt = juju_test;



#endif