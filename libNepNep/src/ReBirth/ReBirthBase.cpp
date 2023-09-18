#include "../../include/ReBirth/ReBirthBase.h"

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
