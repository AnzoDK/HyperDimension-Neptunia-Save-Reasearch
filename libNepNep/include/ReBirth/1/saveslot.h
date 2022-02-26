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
        SaveSlot(unicode_string path);
        ~SaveSlot(){if(m_isLoaded){delete[] m_data;}};
    private:
        byte m_sanityHeader[8] = {0x53, 0x40, 0x56, 0x45, 0x30, 0x30, 0x30, 0x31};
        byte* m_data;
        size_t m_dataSize = 0;
        unicode_string m_slotPath;
        bool m_isLoaded;
        void m_Validate();
        void m_Load();
};
}
