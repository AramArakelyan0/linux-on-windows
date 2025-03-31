#include "functions.h"

using namespace std;

string getErrorMessage()
{
    DWORD errorId = GetLastError();
    char errorMessage[265];

    FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorId,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        errorMessage,
        sizeof(errorMessage),
        nullptr
    );

    return string(errorMessage);
}

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
        cout << "Failed to create file '" << fileName << "'. Error: " << getErrorMessage() << endl;
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

    return "Unknown";
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
        cout << "Failed to change directory. Error: " << getErrorMessage() << endl;
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
        cout << "Failed to create directory '" << newDir << "'. Error: " << getErrorMessage() << endl;
    }
}

void listDirectoryItems(const string&)
{
    string search_path = getCurrentDirectory() + "\\*";
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(search_path.c_str(), &fd);
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

    } while (FindNextFileA(hFind, &fd));

    FindClose(hFind);
}

void removeFile(const string& fileName)
{
    if (fileName.substr(0 ,2) == "-r")
    {
        removeDirectory(fileName.substr(3));
        return;
    }

    if (DeleteFileA(fileName.c_str()))
    {
        cout << "File '" << fileName << "' deleted successfully.";
    }
    else
    {
        cout << "Failed to delete file '" << fileName << "'. Error: " << getErrorMessage() << endl;
    }
}

void removeDirectory(const string& dirName)
{
    if (RemoveDirectoryA(dirName.c_str()))
    {
        cout << "Directory '" << dirName << "' deleted successfully.";
    }
    else
    {
        cout << "Failed to delete directory '" << dirName << "'. Error: " << getErrorMessage() << endl;
    }
}
