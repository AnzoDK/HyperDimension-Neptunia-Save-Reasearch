#pragma once
#include <iostream>
#ifdef _WIN32
#include <string>
#define WCHAR_OS_SEPARATOR L'\\'
#define WSTRING_OS_SEPARATOR L"\\"
#define UNICODE_CHAR_OS_SEPARATOR L'\\'
#define UNICODE_STRING_OS_SEPARATOR L"\\"
#define UNICODE_OUT std::wcout

#define to_unicode_string(x) std::to_wstring(x)

typedef std::wstring unicode_string;
#elif defined(__linux__)
#define WCHAR_OS_SEPARATOR L'/'
#define WSTRING_OS_SEPARATOR L"/"
#define UNICODE_STRING_OS_SEPARATOR "/"
#define UNICODE_CHAR_OS_SEPARATOR "/"
#define UNICODE_OUT std::cout

#define to_unicode_string(x) std::to_string(x)

typedef std::string unicode_string;
#endif
typedef unsigned char byte;
