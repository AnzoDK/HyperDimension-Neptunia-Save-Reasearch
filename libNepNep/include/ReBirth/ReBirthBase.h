#pragma once
#include "../nepnepCommon.h"
#include "SaveFileBase.h"
#include "SaveSlotBase.h"
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
class ReBirthBase
{
    public:
            #ifdef _WIN32
                //Windows Just saves in documents, but linux saves in WINE prefixes...
                ReBirthBase(unicode_string overridePath="");
            #elif defined(__linux__)
                /*Usually "<PREFIX>/drive_c/users/steamuser/My Documents/My Games/Idea Factory International, Inc/Hyperdimension Neptunia Re;Birth1"*/
                ReBirthBase(unicode_string savePath);
            #endif     
            virtual ~ReBirthBase(){};
            virtual bool LoadSave(int slot);
            virtual bool LoadSave(const std::string& saveFileName);
            virtual void LoadSaveAndSlotIntoRAM();
            virtual std::vector<std::string> PopulatedSlots();
            virtual void CommitChanges();
            virtual SaveFileBase* GetSaveFile();
            virtual SaveSlotBase* GetSaveSlot();
        protected:
            /*To ensure Windows path compatibility we use a wstring for the path*/
            //void m_ValidatePath();
            unicode_string m_installPath = "";
            SaveFileBase* m_saveFile = nullptr;
            SaveSlotBase* m_saveSlot = nullptr;
};
