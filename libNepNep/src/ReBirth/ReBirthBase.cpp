#include "../../include/ReBirth/ReBirthBase.h"
#include "../../include/ReBirth/SaveFileBase.h"
#include "../../include/ReBirth/SaveSlotBase.h"
#include "../../include/ReBirth/ReBirthExtras.h"
#include <string.h>
#include <fstream>
#include <openssl/md5.h>

/*ReBirthBase*/

ReBirthBase::ReBirthBase(unicode_string savePath)
{
    m_installPath = savePath;
}


bool ReBirthBase::LoadSave(int slot)
{
    return false;
}

bool ReBirthBase::LoadSave(const std::string& saveFileName)
{
    return false;
}

void ReBirthBase::LoadSaveAndSlotIntoRAM()
{
    
}



std::vector<std::string> ReBirthBase::PopulatedSlots()
{
    if(m_installPath == "")
    {
        std::cout << "SaveDataDir is empty..." << std::endl;
        return std::vector<std::string>();
    }
    std::vector<std::string> slotVec = std::vector<std::string>();
    
    for (const fs::directory_entry& entry : fs::directory_iterator(m_installPath))
    {
        if(entry.path().string().substr(entry.path().string().length()-4) == ".sav")
        {
            slotVec.push_back(entry.path().string().substr(entry.path().string().find_last_of("/")+1));
        }
    }
    return slotVec;
}

void ReBirthBase::CommitChanges()
{
    
}


SaveFileBase* ReBirthBase::GetSaveFile()
{
    return m_saveFile;
}

SaveSlotBase* ReBirthBase::GetSaveSlot()
{
    return m_saveSlot;
}

/*SaveSlotBase*/

SaveSlotBase::SaveSlotBase(unicode_string path)
{
    m_slotPath = path;
}


void SaveSlotBase::LoadAndValidate()
{
    
}

void SaveSlotBase::m_Delete()
{
    if(m_isLoaded)
    {
        std::vector<std::string> keys = std::vector<std::string>();
        for(std::map<std::string,DataRefStructure*>::iterator it = m_dataRefMap.begin(); it != m_dataRefMap.end(); ++it)
        {
            keys.push_back(it->first);
        }
        for(size_t i = 0; i < keys.size(); i++)
        {
            delete m_dataRefMap.at(keys.at(i));
        }
        m_dataRefMap.clear();
        delete[] m_data;
        m_data = 0x0;
        m_isLoaded = false;
    }
}

void SaveSlotBase::m_DeleteAndLoad()
{
    m_Delete();
    m_Load();
}

void SaveSlotBase::m_Validate()
{
    
}
void SaveSlotBase::m_Load()
{
    
}

DataRefStructure SaveSlotBase::GetDataByKey(const std::string& key)
{
    //STUB
}

void SaveSlotBase::m_RegisterOffsetMap()
{
    
}

bool SaveSlotBase::IsLoaded()
{
    return m_isLoaded;
}

std::pair<std::string, DataRefStructure> SaveSlotBase::GetDataPairByKey(const std::string& key)
{
    return std::pair<std::string, DataRefStructure>(key,m_dataRefMap.at(key));
}

unicode_string SaveSlotBase::GetFullSavePath()
{
    return unicode_string(m_slotPath);
}

void SaveSlotBase::CommitToDisk()
{
    if(!m_isLoaded)
    {
        std::cout << "SaveFile: \"" << m_slotPath << "\" is not loaded, can't commit to disk" << std::endl;
        return;
    }
    std::ofstream saveStream = std::ofstream(m_slotPath, std::ios::out | std::ios::binary);
    saveStream.write((char*)m_data, m_dataSize); //Overwrite file
    
    if(saveStream.fail())
    {
        std::cout << "Failed to write savefile" << std::endl;
    }
    saveStream.close();
}


/*SaveFileBase*/

SaveFileBase::SaveFileBase(unicode_string path)
{
    m_savePath = path;
}

void SaveFileBase::m_Delete()
{
    if(m_isLoaded)
    {
        std::vector<std::string> keys = std::vector<std::string>();
        for(std::map<std::string,DataRefStructure*>::iterator it = m_dataRefMap.begin(); it != m_dataRefMap.end(); ++it)
        {
            keys.push_back(it->first);
        }
        for(size_t i = 0; i < keys.size(); i++)
        {
            delete m_dataRefMap.at(keys.at(i));
        }
        m_dataRefMap.clear();
        delete[] m_data;
        m_data = 0x0;
        m_isLoaded = false;
    }
}

void SaveFileBase::LoadAndValidate()
{
    
}

void SaveFileBase::m_Validate()
{
    
}

void SaveFileBase::m_Load()
{
    
}

void SaveFileBase::m_DeleteAndLoad()
{
    m_Delete();
    m_Load();
}

DataRefStructure SaveFileBase::GetDataByKey(const std::string& key)
{
    //STUB
}

void SaveFileBase::m_RegisterOffsetMap()
{
    
}

bool SaveFileBase::IsLoaded()
{
    return m_isLoaded;
}

std::pair<std::string, DataRefStructure*> SaveFileBase::GetDataPairByKey(const std::string& key)
{
    return std::pair<std::string, DataRefStructure*>(key,m_dataRefMap.at(key));
}


unicode_string SaveFileBase::GetFullSavePath()
{
    return unicode_string(m_savePath);
}

void SaveFileBase::CommitToDisk()
{
    if(!m_isLoaded)
    {
        std::cout << "SaveFile: \"" << m_savePath << "\" is not loaded, can't commit to disk" << std::endl;
        return;
    }
    std::ofstream saveStream = std::ofstream(m_savePath, std::ios::out | std::ios::binary);
    saveStream.write((char*)m_data, m_dataSize); //Overwrite file
    if(saveStream.fail())
    {
        std::cout << "Failed to write savefile" << std::endl;
    }
    saveStream.close();
}

byte* SaveFileBase::GetBufferMD5Hash()
{
    if(!m_isLoaded)
    {
        std::cout << "File is load loaded, can't generate hash" << std::endl;
        return 0x0;
    }
    unsigned char* md_buffer = new byte[MD5_DIGEST_LENGTH];
    return MD5(m_data, m_dataSize, md_buffer); //This is depricated, but we need MD5 for this - the MD5.h should prob be used instead
}


//DataRefStructure

DataRefStructure::DataRefStructure(size_t mDataOffset, byte* m_dataPtr, __ExpectedDataType dataType, size_t dataSize)
{
    m_dataOffset = mDataOffset;
    _dataPtr = m_dataPtr+mDataOffset;
    expectedDataType = dataType;
    switch(expectedDataType)
    {
    case UNKNOWN:
    case CUSTOM:
        m_exptectedTypeSize = dataSize;
        break;
    case UINT8:
        m_exptectedTypeSize = 1;
        break;
    case UINT16:
        m_exptectedTypeSize = 2;
        break;
    case UINT32:
        m_exptectedTypeSize = 4;
        break;
    case UINT64:
        m_exptectedTypeSize = 8;
        break;
    case INT8:
        m_exptectedTypeSize = 1;
        break;
    case INT16:
        m_exptectedTypeSize = 2;
        break;
    case INT32:
        m_exptectedTypeSize = 4;
        break;
    case INT64:
        m_exptectedTypeSize = 8;
        break;
    case FLOAT:
        m_exptectedTypeSize = 4;
        break;
    case CSTRING:
        m_exptectedTypeSize = strlen((char*)m_dataPtr);
        break;
    default:
        std::cout << "expectedDataType was not set" << std::endl;
    }
}
DataRefStructure::~DataRefStructure()
{
}


