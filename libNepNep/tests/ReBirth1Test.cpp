#include <iostream>
#include <fstream>
#include "../include/libReBirth1.h"
#include "../include/nepnepCommon.h"
#ifdef _WIN32
#include <string>
#endif


int main()
{
    std::cout << "Running Re;Birth 1 Tests..." << std::endl;
#ifdef _WIN32
    unicode_string thisDir = L".";
#else
    unicode_string thisDir = ".";
#endif
    ReBirth1::ReBirth1Manager manager = ReBirth1::ReBirth1Manager(thisDir);
    std::cout << "Loading Example Save 0" << std::endl;
    manager.LoadSave(0);
    return 0;
}
