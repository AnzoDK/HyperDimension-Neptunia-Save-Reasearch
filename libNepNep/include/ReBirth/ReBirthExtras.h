#pragma once
#include "../nepnepCommon.h"
#include <iostream>
#include <cstdint>
enum __ExpectedDataType{UNKNOWN,INT8,INT16,INT32,INT64,UINT8,UINT16,UINT32,UINT64,FLOAT,CSTRING};
class DataRefStructure
{
public:
    DataRefStructure(size_t mDataOffset, byte* m_dataPtr, __ExpectedDataType dataType=UNKNOWN);
    ~DataRefStructure();
    
    /*Throws Signed*/
    int8_t* ThrowToInt8() { return (int8_t*)_dataPtr; };
    int16_t* ThrowToInt16() { return (int16_t*)_dataPtr; };
    int32_t* ThrowToInt32() { return (int32_t*)_dataPtr; };
    int64_t* ThrowToInt64() { return (int64_t*)_dataPtr; };
    
    /*Throws Unsigned*/
    uint8_t* ThrowToUint8() { return (uint8_t*)_dataPtr; };
    uint16_t* ThrowToUint16() { return (uint16_t*)_dataPtr; };
    uint32_t* ThrowToUint32() { return (uint32_t*)_dataPtr; };
    uint64_t* ThrowToUint64() { return (uint64_t*)_dataPtr; };
    
    /*Throw Floating*/
    float* ThrowToFloat() { return (float*)_dataPtr;};
    
    
    /*Throw Other*/
    const char* ThrowToCString(){ return (char*)_dataPtr; };
    
    byte* _dataPtr = 0x0;
    size_t m_dataOffset = 0x0;
    __ExpectedDataType expectedDataType = UNKNOWN;
    
};


