#include "../../../include/libReBirth1.h"
#include "../../../include/nepnepCommon.h"
#include "../../../include/commonFunc.h"
#include <fstream>
#include <filesystem> //C++ >= 17
#include <iostream>
#include <format>
#include <chrono>
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


bool ReBirth1::ReBirth1Manager::LoadSave(int slot)
{
    unicode_string slotStr = to_unicode_string(slot);
    if(slotStr.size() > 4)
    {
        std::cout << "Slot: " << slot << " is too large to be a valid slot" << std::endl;
        return false;
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
    UnloadSaveSlot();
    UnloadSaveFile();
    m_saveFile = new SaveFile(slotPath+".sav");
    m_saveSlot = new SaveSlot(slotPath+".savslot");
#endif
    return true;
    
}

bool ReBirth1::ReBirth1Manager::LoadSave(const std::string& saveFileName)
{
    if(saveFileName.substr(saveFileName.length()-4) != ".sav")
    {
        std::cout << "SaveFile: \"" << saveFileName << "\" is not a valid savefile (checked against: \"" << saveFileName.substr(saveFileName.length()-4) << "\")" << std::endl;
        return false;
    }
    unicode_string savPath = m_installPath + UNICODE_CHAR_OS_SEPARATOR + saveFileName;
    unicode_string savSlotPath = savPath+"slot";
    if(!fs::exists(savPath) || !fs::exists(savSlotPath))
    {
        std::cout << "SaveFile missing - Can't access: \"" << saveFileName << "\" or its associated .savslot (" << std::string(saveFileName + "slot") << ")" << std::endl;
        return false;
    }

    UnloadSaveFile();
    m_saveFile = new SaveFile(savPath);
    UnloadSaveSlot();
    m_saveSlot = new SaveSlot(savSlotPath);
    
    return true; 
}

void ReBirth1::ReBirth1Manager::LoadSaveAndSlotIntoRAM()
{
    if(m_saveFile == 0x0 || m_saveSlot == 0x0)
    {
        std::cout << "SaveFile or SaveSlot is not initilized - Load a save first..." << std::endl;
        return;
    }
    m_saveFile->LoadAndValidate();
    m_saveSlot->LoadAndValidate();
}


void ReBirth1Manager::CommitChanges()
{
    //Start with updating the .sav file - This must be done first, as the .savslot file requires an MD5 hash of the .sav file
    const auto now = std::chrono::system_clock::now();
    time_t backupTime = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&backupTime);
    std::string timeString = "-" + std::to_string(local_tm.tm_mday) + std::string("_") + std::to_string(local_tm.tm_mon) + std::string("_") + std::to_string(local_tm.tm_year) + std::string("_") + std::to_string(local_tm.tm_hour) + std::to_string(local_tm.tm_min) + std::to_string(local_tm.tm_sec);
    
    //Create backup of save file + savslot file
    std::string savePath = m_saveFile->GetFullSavePath();
    fs::copy_file(savePath, savePath.substr(0,savePath.length()-4) + timeString + ".sav");
    
    std::string saveSlotPath = m_saveSlot->GetFullSavePath();
    fs::copy_file(saveSlotPath, savePath.substr(0,saveSlotPath.length()-9) + timeString + ".savslot");
    
    fs::remove(savePath);
    m_saveFile->CommitToDisk();
    //Reload the file
    m_saveFile->LoadAndValidate(); //no need as we have saved a copy of the buffer, BUT it's a good idea, as it checks for errors in the file
    //LibCrypto + LibOpenSSL
    byte* hash = m_saveFile->GetBufferMD5Hash();
    
    //Update the saveSlots internal MD5 hash
    auto data = m_saveSlot->GetDataPairByKey("savFileMD5Hash");
    for(int i = 0; i < 16; i++)
    {
        data.second._dataPtr[i] = hash[i];
    }
    
    fs::remove(saveSlotPath);
    m_saveSlot->CommitToDisk();
    delete[] hash;
}

/* SaveFile */

SaveFile::SaveFile(unicode_string path) : SaveFileBase(path)
{
    m_Validate();
}

void SaveFile::m_Validate()
{
    if(!fs::exists(m_savePath))
    {
        UNICODE_OUT << "Save File: " << m_savePath << " Failed to validate... (File Not Found)" << std::endl;
        //exit(1);
        return;
    }
    m_Delete();
    m_Load();
    m_RegisterOffsetMap();
    
}
void SaveFile::m_Load()
{
    m_data = CommonFunc::ReadUnsignedFile(m_savePath,m_dataSize);
    m_isLoaded = 1;
}

void SaveFile::LoadAndValidate()
{      
    m_Validate();
}

void SaveFile::m_RegisterOffsetMap()
{
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("playTimeHours", DataRefStructure(0xe1c,m_data,UINT32)));
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("playTimeMinutes",DataRefStructure(0xe20,m_data,UINT32)));
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("playTimeSeconds", DataRefStructure(0xe24,m_data,UINT32)));
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("saveCount", DataRefStructure(12,m_data,UINT32)));
    
}

/* SaveSlot */
SaveSlot::SaveSlot(unicode_string path) : SaveSlotBase(path)
{
    m_Validate();
}

void SaveSlot::m_Validate()
{
    if(!fs::exists(m_slotPath))
    {
        UNICODE_OUT << "SaveSlot File: " << m_slotPath << " Failed to validate... (File Not Found)" << std::endl;
        //exit(1);
        return;
    }
    m_Load();
    m_Delete();
    m_Load();
    m_RegisterOffsetMap();
}

void SaveSlot::m_Load()
{
    m_data = CommonFunc::ReadUnsignedFile(m_slotPath,m_dataSize);
    m_isLoaded = 1;
    
}

void SaveSlot::LoadAndValidate()
{
    m_Validate();
}
void SaveSlot::m_RegisterOffsetMap()
{
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("savslotHeader", DataRefStructure(0,m_data,CUSTOM,8)));
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("savFileMD5Hash", DataRefStructure(0x18,m_data,CUSTOM,16)));
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("savTimeStampHour", DataRefStructure(0x334,m_data,UINT16)));
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("savTimeStampMin",DataRefStructure(0x336,m_data,UINT16)));
    m_dataRefMap.insert(std::pair<std::string, DataRefStructure>("SavTimeStampSec", DataRefStructure(0x338,m_data,UINT16)));
    
    
}

