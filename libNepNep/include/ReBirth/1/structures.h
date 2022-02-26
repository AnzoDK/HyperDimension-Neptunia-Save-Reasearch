#pragma once
#include "../../nepnepCommon.h"
#include "savefile.h"
#include "saveslot.h"
#include <iostream>
namespace ReBirth1
{
    class ReBirth1Manager
    {
        public:
            #ifdef _WIN32
                //Windows Just saves in documents, but linux saves in WINE prefixes...
                ReBirth1Manager(unicode_string overridePath="");
            #elif defined(__linux__)
                /*Usually "<PREFIX>/drive_c/users/steamuser/My Documents/My Games/Idea Factory International, Inc/Hyperdimension Neptunia Re;Birth1"*/
                ReBirth1Manager(unicode_string savePath);
            #endif     
            ~ReBirth1Manager(){if(m_saveFile != nullptr){delete m_saveFile;}if(m_saveSlot != nullptr){delete m_saveSlot;}};
            void LoadSave(int slot);
        private:
            /*To ensure Windows path compatibility we use a wstring for the path*/
            void m_ValidatePath();
            unicode_string m_installPath;
            SaveFile* m_saveFile = nullptr;
            SaveSlot* m_saveSlot = nullptr;
    };
        
};
