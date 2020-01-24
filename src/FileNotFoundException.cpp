#include "FileNotFoundException.h"

#include <string>

FileNotFoundException::FileNotFoundException(const std::string& fileName) 
    : fileName(fileName) {}

FileNotFoundException::~FileNotFoundException() throw () {}

const char* FileNotFoundException::what() const throw() 
{
    std::string message = "File " + fileName + " was not found!";
    return message.c_str();
}
