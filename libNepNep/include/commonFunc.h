#include "nepnepCommon.h"
#pragma once
#if defined(_WIN32) || defined(_WIN64)
include <string>
#endif
class CommonFunc
{
public:
    static byte* ReadUnsignedFile(const std::string& filePath, size_t& fileSize);
};
