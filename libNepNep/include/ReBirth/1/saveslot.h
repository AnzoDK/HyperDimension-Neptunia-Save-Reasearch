#pragma once
#include "../SaveSlotBase.h"
#include <iostream>
#ifdef _WIN32
#include <string>
#endif
namespace ReBirth1
{

    struct SaveSlotHeader
    {
        /**
         * @brief A static header always equal to this array {Which is just the C-string: "SAVE0001"}
         * 
         */
        byte header[8] = {0x53, 0x40, 0x56, 0x45, 0x30, 0x30, 0x30, 0x31};
        /**
        * @brief Unknown 16 bytes between the MD5 hash and header ... //Needs to be researched - Range [8-23]
        * 
        */
        byte unknownDataStartingAt0x8[16];
        
        /**
        * @brief The MD5 Hash of the .sav file, kept here to make sure they aren't being edited independant of each other.
        * 
        */
        byte savefileMD5Hash[16];
        
        /**
        * @brief A 4 byte int, usually set to zero, I have never seen it set, but theoretically it is possible.
        * 
        */
        byte nullByteSeperatorAt0x28[4] = {0,0,0,0};
        
        /**
        * @brief The name of the game as a SHIFT-JIS encoded string - this is possibly used to make sure that different games using the same engine doesn't use each others saves - For HDN Re;Birth 1 it's equal to: "超次元ゲイム ネプテューヌRe;Birth1"
        * 
        */
        byte gameName[36] = { 0x92, 0xb4, 0x8e, 0x9f, 0x8e, 0x9f, 0x8c, 0xb3, 0x83, 0x51, 0x83, 0x43, 0x83, 0x80, 0x20, 0x83, 0x6c, 0x83, 0x76, 0x83, 0x65, 0x83, 0x85, 0x81, 0x5b, 0x83, 0x6b, 0x52, 0x65, 0x3b, 0x42, 0x69, 0x72, 0x74, 0x68, 0x31 };
        
        /**
        * @brief 28 Bytes of nulls - acting as a sepetator between the "header" and saveslot content
        * 
        */
        byte nullSeperatorAt0x50[28] = {};
    };
    
    /**
     * @brief The SaveSlot File structure as found on disk.
     * 
     */
    struct SaveSlotFile
    {
        SaveSlotHeader header;
        /**
        * @brief The name of the current chapter in ASCII, starting at offset 0x6C - With a possible buffer size of 128 bytes // Range [0x6C - 0xEB]
        * 
        */
        byte* chapterTitle = 0x0;
        
        /**
         * @brief The text to be displayed on the "LoadSave" menu - starting at offset 0xEC - has a potential buffer of 512 bytes // Range [0xEC - 0x2EB]
         * 
         */
        byte* saveFileText = 0x0;
        
        /**
         * @brief A static path to app0:/data/icon.png (Always equal to this path)
         */
        byte iconPath[19] =
        {
            0x61, 0x70, 0x70, 0x30,
            0x3a, 0x2f, 0x64, 0x61,
            0x74, 0x61, 0x2f, 0x69,
            0x63, 0x6f, 0x6e, 0x2e,
            0x70, 0x6e, 0x67
        };

    
};
    
class SaveSlot : public SaveSlotBase
{
    public:
        SaveSlot(unicode_string path);
        ~SaveSlot(){m_Delete();};
        virtual void LoadAndValidate() override;
    protected:
        byte m_sanityHeader[8] = {0x53, 0x40, 0x56, 0x45, 0x30, 0x30, 0x30, 0x31};
        virtual void m_Validate() override;
        virtual void m_Load() override;
        virtual void m_RegisterOffsetMap() override;
};
}
