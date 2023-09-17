#include "../../include/commonFunc.h"
#include <iostream>
#include <fstream>

byte* CommonFunc::ReadUnsignedFile(const std::string& filePath, size_t& fileSize)
{
    std::ifstream in = std::ifstream(filePath, std::ios::in | std::ios::binary);
    in.seekg(0, in.end);
    fileSize = in.tellg();
    in.seekg(0, in.beg);
    byte* buffer = new byte[fileSize];
    in.read(reinterpret_cast<char*>(buffer), fileSize);
    return buffer;
}
