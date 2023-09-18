#pragma once
#include "../nepnepCommon.h"
#include <iostream>
class DataRefStructure
{
public:
    DataRefStructure(size_t mDataOffset, byte* m_dataPtr);
    byte* _dataPtr = 0x0;
    size_t m_dataOffset = 0x0;
};

