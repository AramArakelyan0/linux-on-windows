#include "functions.h"

using namespace std;

void createFile(const string& fileName)
{
    HANDLE fileHandle = CreateFileA(
        fileName.c_str(),
        GENERIC_WRITE,
        0,
        nullptr,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (fileHandle == INVALID_HANDLE_VALUE) {
        cout << "Failed to create file '" << fileName << "'. Error: " << GetLastError() << endl;
    }
    else
    {
        cout << "File '" << fileName << "' created successfully." << endl;
        CloseHandle(fileHandle);
    }
}

string getCurrentDirectory()
{
    char buffer[MAX_PATH];
    if (GetCurrentDirectoryA(MAX_PATH, buffer))
    {
        return string(buffer);
    }

    return "Unknown";  // If an error occurs
}

void printDirectory(const string&)
{
    cout << getCurrentDirectory() << endl;
}

void changeDirectory(const string& newPath)
{
    if (SetCurrentDirectoryA(newPath.c_str()))
    {
        cout << "Changed directory to: " << getCurrentDirectory() << endl;
    }
    else
    {
        cout << "Error: Failed to change directory. Error code: " << GetLastError() << endl;
    }
}

void createDirectory(const string& newDir)
{
    BOOL result = CreateDirectoryA(newDir.c_str(), nullptr);
    if (result)
    {
        cout << "Folder '" << newDir << "' created successfully." << endl;
    }
    else
    {
        DWORD errorCode = GetLastError();
        if (errorCode == ERROR_ALREADY_EXISTS)
        {
            cout << "Error: The directory '" << newDir << "' already exists." << endl;
        }
        else
        {
            cout << "Error: Failed to create directory '" << newDir << "'. Error code: " << errorCode << endl;
        }
    }
}

void listDirectoryItems(const string&)
{
    string search_path = getCurrentDirectory() + "\\*";
    WIN32_FIND_DATAA fd;
    HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Error: Could not open folder " << getCurrentDirectory() << "." << endl;
        return;
    }

    do {
        string name = fd.cFileName;
        if (name == "." || name == "..")
        {
            continue;
        }

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            cout << "[DIR] " << name << endl;
        }
        else
        {
            cout << "[FILE] " << name << endl;  
        }

    } while (::FindNextFileA(hFind, &fd));

    ::FindClose(hFind);
}
