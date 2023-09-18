#include "../../include/ReBirth/ReBirthBase.h"
#include "../../include/ReBirth/SaveFileBase.h"
#include "../../include/ReBirth/SaveSlotBase.h"
#include "../../include/ReBirth/ReBirthExtras.h"

/*ReBirthBase*/

ReBirthBase::ReBirthBase(unicode_string savePath)
{
    m_installPath = savePath;
}


void ReBirthBase::LoadSave(int slot)
{
    
}

void ReBirthBase::LoadSave(const std::string& saveFileName)
{
    
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

/*SaveFileBase*/

SaveFileBase::SaveFileBase(unicode_string path)
{
    m_savePath = path;
}

void SaveFileBase::m_Delete()
{
    if(m_isLoaded)
    {
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


//DataRefStructure

DataRefStructure::DataRefStructure(size_t mDataOffset, byte* m_dataPtr, __ExpectedDataType dataType)
{
    m_dataOffset = m_dataOffset;
    _dataPtr = (byte*)m_dataPtr[mDataOffset];
    expectedDataType = dataType;
}
DataRefStructure::~DataRefStructure()
{
}


