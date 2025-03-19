#pragma once
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

void createFile(const std::string&);
void changeDirectory(const std::string&);
std::string getCurrentDirectory();
void listDirectoryItems(const std::string&);
void createDirectory(const std::string&);
void printDirectory(const std::string&);