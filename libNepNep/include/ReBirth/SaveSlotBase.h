#pragma once
#include "../nepnepCommon.h"
#include "ReBirthExtras.h"
class SaveSlotBase
{
public:
    SaveSlotBase(unicode_string path);
    virtual ~SaveSlotBase(){m_Delete();};
    virtual void LoadAndValidate();
    virtual DataRefStructure GetDataByKey(const std::string& key);
protected:
    byte* m_sanityHeader = 0x0;
    byte* m_data = 0x0;
    size_t m_dataSize = 0;
    unicode_string m_slotPath = "";
    bool m_isLoaded = 0;
    std::map<std::string, DataRefStructure> m_dataRefMap = std::map<std::string,DataRefStructure>();
    virtual void m_Validate();
    virtual void m_Load();
    virtual void m_DeleteAndLoad();
    virtual void m_Delete();
    virtual void m_RegisterOffsetMap();
};
