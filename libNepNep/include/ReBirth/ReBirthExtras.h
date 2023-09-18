#pragma once
#include "../nepnepCommon.h"
#include <iostream>
enum __ExpectedDataType{UNKNOWN,INT8,INT16,INT32,INT64,UINT8,UINT16,UINT32,UINT64,CSTRING};
class DataRefStructure
{
public:
    DataRefStructure(size_t mDataOffset, byte* m_dataPtr, __ExpectedDataType dataType=UNKNOWN);
    ~DataRefStructure();
    byte* _dataPtr = 0x0;
    size_t m_dataOffset = 0x0;
    __ExpectedDataType expectedDataType = UNKNOWN;
};

