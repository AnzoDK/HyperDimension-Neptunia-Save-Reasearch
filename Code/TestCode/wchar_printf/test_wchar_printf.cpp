#include <iostream>
#include <wchar.h>
//#include <stdarg.h>
#include <string.h>
#include <stdio.h>
void wchar_printf(wchar_t* buffer, const wchar_t* printf_format)
{
   
    __builtin_va_list* selfFramePtr = 0x0;
    __asm__ volatile
    (
        "push %%rax\n"
        "lea 0x18(%%rbp), %%rax\n"
        "mov %%rax, %0\n"
        "popq %%rax"
        : "=m"(selfFramePtr)
        :
    );
    vswprintf(buffer,0x104,printf_format,*selfFramePtr);
}


int main()
{
    wchar_t* some = L"SomeString";
    wchar_t someString[260];
    memset(someString, 0x0, 260);
    for(int i = 0; i < 10; i++)
    {
        someString[i] = some[i];
    }
    wchar_t* someFormat = L"\0";
    wchar_printf(someFormat, someString);
}


