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
        SaveFile(unicode_string path);
        ~SaveFile(){if(m_isLoaded){delete[] m_data;}};
    private:
        unicode_string m_savePath;
        bool m_isLoaded;
        byte* m_data;
        size_t m_dataSize = 0;
        void m_Validate();
        void m_Load();
};
}
