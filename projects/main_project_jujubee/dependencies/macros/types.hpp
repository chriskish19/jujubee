#include NAMES_INCLUDE
 
/*

Purpose: Manage types throughout jujubee.

*/

// names
#include NAMES_INCLUDE

// stl
#include STL_INCLUDE

// windows
#include WINDOWS_INCLUDE



#if defined(UNICODE) || defined(_UNICODE)

namespace classes {
	using string = std::wstring;
	using ostringstream = std::wostringstream;
	using character = wchar_t;
	using w32_str_p = LPWSTR;			// wchar_t*
	using w32_str_cp = LPCWSTR;			// const wchar_t* (read only)
	namespace fs = std::filesystem;		// for less typing
}

#else

namespace classes {
	using string = std::string;
	using ostringstream = std::ostringstream;
	using character = char;
	using w32_str_p = LPSTR;			// wchar_t*
	using w32_str_cp = LPCSTR;			// const wchar_t* (read only)
	namespace fs = std::filesystem;		// for less typing
}


#endif