#include "../../../include/libReBirth1.h"
#include "../../../include/nepnepCommon.h"
#include <fstream>
#include <filesystem> //C++ >= 17
namespace fs = std::filesystem;
using namespace ReBirth1;

/* ReBirth1Manager */
#ifdef _WIN32
#include <windows.h>
#include <shobjidl_core.h>
ReBirth1Manager::ReBirth1Manager(std::wstring overridePath)
{
    if(overridePath != L"")
    {
        m_installPath = overridePath;
    }
    else
    {
        wchar_t* path = nullptr;
        HRESULT res = SHGetKnownFolderPath(FOLDERID_Documents,0x0,NULL,path);
        if(res != S_OK)
        {
            std::cout << "Failed to retreive user folder... Please report this bug" << std::endl;
            exit(1);
        }  
        m_installPath = std::wstring(path);
        m_installPath += "\\My Games\\Idea Factory International, Inc\\Hyperdimension Neptunia Re;Birth1"
        CoTaskMemFree(path);
    }
    m_ValidatePath();
}
#elif defined(__linux__)
ReBirth1Manager::ReBirth1Manager(std::wstring instPath)
{
    m_installPath = instPath;
    
}
#endif

void ReBirth1::ReBirth1Manager::m_ValidatePath()
{
    if(!fs::exists(m_installPath) || !fs::exists(m_installPath+WCHAR_OS_SEPARATOR+L"Neptune.ini"))
    {
        std::wcout << "Could not find the Re;Birth1 save folder... (Searched for folder: " << m_installPath << ") [The game may have to be booted up at least once...]" << std::endl;
        exit(1);
    }
}


void ReBirth1::ReBirth1Manager::LoadSave(int slot)
{
    std::wstring slotStr = std::to_wstring(slot);
    if(slotStr.size() > 4)
    {
        std::cout << "Slot: " << slot << " is too large to be a valid slot" << std::endl;
        exit(1);
    }
    int leadingZeros = 4-slotStr.size();
    std::wstring slotPath = m_installPath+WCHAR_OS_SEPARATOR+L"data";
    for(int i = 0; i < leadingZeros; i++)
    {
        slotPath+=L'0';
    }
    slotPath+=slotStr;
    std::wcout << "Attempting to access " << slotPath << std::endl;
    m_saveFile = new SaveFile(slotPath+L".sav");
    m_saveSlot = new SaveSlot(slotPath+L".savslot");
    
    
}

/* SaveFile */

SaveFile::SaveFile(std::wstring path)
{
    m_savePath = path;
    m_Validate();
}

void SaveFile::m_Validate()
{
    if(!fs::exists(m_savePath))
    {
        std::wcout << "Save File: " << m_savePath << " Failed to validate... (File Not Found)" << std::endl;
        exit(1);
    }
}

/* SaveSlot */
SaveSlot::SaveSlot(std::wstring path)
{
    m_slotPath = path;
    m_Validate();
}

void SaveSlot::m_Validate()
{
    if(!fs::exists(m_slotPath))
    {
        std::wcout << "SaveSlot File: " << m_slotPath << " Failed to validate... (File Not Found)" << std::endl;
        exit(1);
    }
}

