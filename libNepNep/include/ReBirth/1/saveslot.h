#pragma once
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
        * @brief Unknown 27 bytes of data - seemingly always set to {92 ,B4 ,8E ,9F ,8E ,9F ,8C ,B3 ,83 ,51 ,83 ,43 ,83 ,80 ,20 ,83 ,6C ,83 ,76 ,83 ,65 ,83 ,85 ,81 ,5B ,83 ,6B}
        * 
        */
        byte unknownDataStartingAt0x2C[27] = {0x92 ,0xB4 ,0x8E ,0x9F ,0x8E ,0x9F ,0x8C ,0xB3 ,0x83 ,0x51 ,0x83 ,0x43 ,0x83 ,0x80 ,0x20 ,0x83 ,0x6C ,0x83 ,0x76 ,0x83 ,0x65 ,0x83 ,0x85 ,0x81 ,0x5B ,0x83 ,0x6B};
        
        /**
        * @brief The name of the game - this is possibly used to make sure that different games using the same engine doesn't use each others saves
        * 
        */
        byte gameName[9] = {'R', 'e', ';', 'B', 'i', 'r', 't', 'h', '1'}; //Re;Birth1;
        
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
    
class SaveSlot
{
    public:
        SaveSlot(unicode_string path);
        ~SaveSlot(){if(m_isLoaded){delete[] m_data;}};
    private:
        byte m_sanityHeader[8] = {0x53, 0x40, 0x56, 0x45, 0x30, 0x30, 0x30, 0x31};
        byte* m_data;
        size_t m_dataSize = 0;
        unicode_string m_slotPath;
        bool m_isLoaded;
        void m_Validate();
        void m_Load();
};
}
