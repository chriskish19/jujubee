/***********************************************
* File: settings.hpp
*
* Purpose: Manage macro settings thorughout jujubee
*
*
*
************************************************/

#define MAX_STRING 512

#if defined(UNICODE) || defined(_UNICODE)
#define COUT std::wcout

// read only string, prepends L"string literal"
#define ROS(x) L##x

#define USING_WSTR 1


#else // ANSI

#define COUT std::cout
#define ROS(x) x
#define USING_STR 1
#endif

#ifdef TEST // compiler definition macro

#define ENTRY_TEST

#endif



