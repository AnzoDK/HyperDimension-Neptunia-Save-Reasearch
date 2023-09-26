#pragma once
#include "../nepnepCommon.h"
#include <iostream>
#include <map>
#include "ReBirthExtras.h"
class SaveFileBase
{
public:
    SaveFileBase(unicode_string path);
    virtual ~SaveFileBase(){m_Delete();};
    virtual void LoadAndValidate();
    virtual DataRefStructure GetDataByKey(const std::string& key);
    virtual std::pair<std::string, DataRefStructure> GetDataPairByKey(const std::string& key);
    virtual bool IsLoaded();
    virtual unicode_string GetFullSavePath();
    virtual void CommitToDisk();
    virtual byte* GetBufferMD5Hash();//This is kinda stoopid...
protected:
    unicode_string m_savePath = "";
    bool m_isLoaded = 0;
    byte* m_data = 0x0;
    size_t m_dataSize = 0;
    std::map<std::string, DataRefStructure> m_dataRefMap = std::map<std::string,DataRefStructure>();
    virtual void m_Validate();
    virtual void m_Load();
    virtual void m_DeleteAndLoad();
    virtual void m_Delete();
    virtual void m_RegisterOffsetMap();
    
    
};
