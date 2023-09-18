#pragma once
#include "../nepnepCommon.h"
class SaveFileBase
{
public:
    SaveFileBase(unicode_string path);
    virtual ~SaveFileBase(){m_Delete();};
    virtual void LoadAndValidate();
protected:
    unicode_string m_savePath = "";
    bool m_isLoaded = 0;
    byte* m_data = 0x0;
    size_t m_dataSize = 0;
    virtual void m_Validate();
    virtual void m_Load();
    virtual void m_DeleteAndLoad();
    virtual void m_Delete();
    
};
