#pragma once
#ifdef _WIN32
#include <string>
#define WCHAR_OS_SEPARATOR L'\\'
#define WSTRING_OS_SEPARATOR L"\\"
#elif defined(__linux__)
#define WCHAR_OS_SEPARATOR L'/'
#define WSTRING_OS_SEPARATOR L"/"
#endif
typedef unsigned char byte;
