#include "AnagramDatabase.h"

#include <vector>
#include <string>
#include <exception>

#include "FileNotFoundException.h"

AnagramDatabase::AnagramDatabase()
{
    anagram_db adb; 
}

AnagramDatabase::AnagramDatabase(const std::string& dict) 
    throw (std::exception)
{
    anagram_db adb; 
    setDictionary(dict); 
}

void AnagramDatabase::setDictionary(const std::string& dict) 
    throw (std::exception)
{
    if (FILE *file = fopen(dict.c_str(), "r")) {
        fclose(file);
    } else {
        throw FileNotFoundException(dict);
    }   
}

std::vector<std::string> AnagramDatabase::findAnagrams(const std::string& anagram)
{
    std::vector<std::string> anagrams;
    anagrams.push_back("not implemented yet");
    return anagrams;
}
