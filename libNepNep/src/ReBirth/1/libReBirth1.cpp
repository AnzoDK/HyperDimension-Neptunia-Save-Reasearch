#include "../../../include/libReBirth1.h"
#include "../../../include/nepnepCommon.h"
#include "../../../include/commonFunc.h"
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
        m_installPath += L"\\My Games\\Idea Factory International, Inc\\Hyperdimension Neptunia Re;Birth1"
        CoTaskMemFree(path);
    }
    m_ValidatePath();
}
#elif defined(__linux__)
ReBirth1Manager::ReBirth1Manager(unicode_string instPath) : ReBirthBase(instPath)
{ }
#endif

/*void ReBirth1::ReBirth1Manager::m_ValidatePath()
{
#ifdef _WIN32
    unicode_string neptuneFile = L"Neptune.ini";
#else
    unicode_string neptuneFile = "Neptune.ini";
#endif
    if(!fs::exists(m_installPath) || !fs::exists(m_installPath+UNICODE_CHAR_OS_SEPARATOR+neptuneFile))
    {
        UNICODE_OUT << "Could not find the Re;Birth1 save folder... (Searched for folder: " << m_installPath << ") [The game may have to be booted up at least once...]" << std::endl;
        exit(1);
    }
}*/


void ReBirth1::ReBirth1Manager::LoadSave(int slot)
{
    unicode_string slotStr = to_unicode_string(slot);
    if(slotStr.size() > 4)
    {
        std::cout << "Slot: " << slot << " is too large to be a valid slot" << std::endl;
        exit(1);
    }
    int leadingZeros = 4-slotStr.size();
#ifdef _WIN32
    unicode_string slotPath = m_installPath+UNICODE_CHAR_OS_SEPARATOR+L"data";
#else
    unicode_string slotPath = m_installPath+UNICODE_CHAR_OS_SEPARATOR+"data";
#endif
    for(int i = 0; i < leadingZeros; i++)
    {
#ifdef _WIN32
        slotPath+=L'0';
#else
        slotPath+='0';
#endif
    }
    slotPath+=slotStr;
    UNICODE_OUT << "Attempting to access " << slotPath << std::endl;
#ifdef _WIN32
    m_saveFile = new SaveFile(slotPath+L".sav");
    m_saveSlot = new SaveSlot(slotPath+L".savslot");
#else
    m_saveFile = new SaveFile(slotPath+".sav");
    m_saveSlot = new SaveSlot(slotPath+".savslot");
#endif
    
    
}

void ReBirth1::ReBirth1Manager::LoadSave(const std::string& saveFileName)
{
    if(saveFileName.substr(saveFileName.length()-4) != ".sav")
    {
        std::cout << "SaveFile: \"" << saveFileName << "\" is not a valid savefile (checked against: \"" << saveFileName.substr(saveFileName.length()-4) << "\")" << std::endl;
        return;
    }
    unicode_string savPath = m_installPath + UNICODE_CHAR_OS_SEPARATOR + saveFileName;
    unicode_string savSlotPath = savPath+"slot";
    if(!fs::exists(savPath) || !fs::exists(savSlotPath))
    {
        std::cout << "SaveFile missing - Can't access: \"" << saveFileName << "\" or its associated .savslot (" << std::string(saveFileName + "slot") << ")" << std::endl;
        return;
    }

    UnloadSaveFile();
    m_saveFile = new SaveFile(savPath);
    UnloadSaveSlot();
    m_saveSlot = new SaveSlot(savSlotPath);
    
}


/* SaveFile */

SaveFile::SaveFile(unicode_string path)
{
    m_savePath = path;
    m_Validate();
}

void SaveFile::m_Validate()
{
    if(!fs::exists(m_savePath))
    {
        UNICODE_OUT << "Save File: " << m_savePath << " Failed to validate... (File Not Found)" << std::endl;
        exit(1);
    }
    m_Load();
    
}
void SaveFile::m_Load()
{
    m_data = CommonFunc::ReadUnsignedFile(m_savePath,m_dataSize);
}

/* SaveSlot */
SaveSlot::SaveSlot(unicode_string path)
{
    m_slotPath = path;
    m_Validate();
}

void SaveSlot::m_Validate()
{
    if(!fs::exists(m_slotPath))
    {
        UNICODE_OUT << "SaveSlot File: " << m_slotPath << " Failed to validate... (File Not Found)" << std::endl;
        exit(1);
    }
    m_Load();
}

void SaveSlot::m_Load()
{
    m_data = CommonFunc::ReadUnsignedFile(m_slotPath,m_dataSize);
}

