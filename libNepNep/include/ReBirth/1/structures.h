#pragma once
#include "../../nepnepCommon.h"
#include "../ReBirthBase.h"
#include "savefile.h"
#include "saveslot.h"
#include <iostream>
#include <vector>
namespace ReBirth1
{
    class ReBirth1Manager : public ReBirthBase
    {
        public:
            #ifdef _WIN32
                //Windows Just saves in documents, but linux saves in WINE prefixes...
                ReBirth1Manager(unicode_string overridePath="");
            #elif defined(__linux__)
                /*Usually "<PREFIX>/drive_c/users/steamuser/My Documents/My Games/Idea Factory International, Inc/Hyperdimension Neptunia Re;Birth1"*/
                ReBirth1Manager(unicode_string savePath);
            #endif     
            virtual ~ReBirth1Manager(){UnloadSaveFile(); UnloadSaveSlot();};
            void UnloadSaveSlot(){if(m_saveSlot != nullptr){delete m_saveSlot; m_saveSlot = 0x0;}};
            void UnloadSaveFile(){if(m_saveFile != nullptr){delete m_saveFile; m_saveFile = 0x0;}};
            virtual void LoadSave(int slot) override;
            virtual void LoadSave(const std::string& saveFileName) override;
            virtual void LoadSaveAndSlotIntoRAM() override;
        protected:
            SaveFile* m_saveFile = nullptr;
            SaveSlot* m_saveSlot = nullptr;
    };
        
};
