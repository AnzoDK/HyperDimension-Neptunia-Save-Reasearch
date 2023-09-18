#pragma once
#include "../SaveFileBase.h"
#include <iostream>
#ifdef _WIN32
#include <string>
#endif
namespace ReBirth1
{
struct _FileStructure
{
    /**
     * @brief Uknown data at the start of the save file... usually just set to {0x0,0x0}
     * 
     */
    byte uknownDataStartingAt0x0[2] = {0,0};
    /**
     * @brief The saveslotID used to display the savefile in the game - indexed from 1 instead of zero. Located at offset 0x02
     * 
     */
    int saveSlotId = 0x0; //4 bytes
    /**
     * @brief Located at 0x0C and saves the amount of times the savefile has been overwritten as a single 32bit signed integer
     * 
     */
    int saveCounter[4]; //byte[4]
    
    /**
     * @brief Unknown data at 0x010 usually just set to {0,0,0,0}
     * 
     */
    byte unknownDataStartingAt0x010[4] = {0,0,0,0};
    /**
     * @brief The playtime hours (not total playtime *in* hours) Starting at 0x0e1c and holds 4 bytes for hour, 4 bytes for minutes and 4 bytes for seconds
     * 
     */
    int* playTimeHours;
    int playTimeMinutes;
    int playTimeSeconds;
    
};
class SaveFile : public SaveFileBase
{
    public:
        SaveFile(unicode_string path);
        virtual ~SaveFile(){m_Delete();};
        virtual void LoadAndValidate() override;
        
    protected:
        virtual void m_Validate() override;
        virtual void m_Load() override;
        virtual void m_RegisterOffsetMap() override;
};
}
