#pragma once
#include <iostream>
#ifdef _WIN32
#include <string>
#endif
namespace ReBirth1
{
class SaveFile
{
    public:
        SaveFile(std::wstring path);
        ~SaveFile(){};
    private:
        std::wstring m_savePath;
        void m_Validate();
};
}
