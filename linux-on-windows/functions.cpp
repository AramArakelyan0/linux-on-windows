#include "functions.h"

using namespace std;

void createFile(const string fileName) {
    HANDLE fileHandle = CreateFileA(
        fileName.c_str(),
        GENERIC_WRITE,
        0,
        nullptr,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
}