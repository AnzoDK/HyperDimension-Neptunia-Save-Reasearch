#pragma once
#pragma once
#include <iostream>
#ifdef _WIN32
#include <string>
#endif
namespace ReBirth1
{
class SaveSlot
{
    public:
        SaveSlot(std::wstring path);
        ~SaveSlot(){};
    private:
        byte data[8] = {0x53, 0x40, 0x56, 0x45, 0x30, 0x30, 0x30, 0x31};
        std::wstring m_slotPath;
        void m_Validate();
};
}
