#include "AnagramDatabase.h"

#include <vector>
#include <string>
#include <exception>
#include <fstream>

#include <iostream>

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
    //open the file and make sure it's open
    std::ifstream infile(dict);
    if (infile.is_open()) {
        std::string word;
        //read the file line by line
        while (infile >> word)
        {

            //get the sum of all the ASCII values of the word
            int sum = getWordSum(word);

            //find the map that holds all the words of the same length.
            anagram_db::iterator lenMapIt = adb.find(word.length());
            if (lenMapIt != adb.end()) 
            {
                //there has been words added before of the same length
                //now, find that vector that contains all the words that have the
                //same sum of ASCII character values.
                char_sum_map::iterator sumMapIt = lenMapIt->second.find(sum);
                if (sumMapIt != lenMapIt->second.end())
                {
                    //just add the word to the located vector
                    (sumMapIt->second).push_back(word);
                }
                else
                {
                    std::vector < std::string > anagramList;
                    anagramList.push_back(word);
                    lenMapIt->second[sum] = anagramList;
                }
            }
            else
            {
                //there has been no word with this length before
                char_sum_map newSumMap;
                std::vector < std::string > anagramList;
                anagramList.push_back(word);

                //add the vector to the map, and add that map the database
                newSumMap[sum] = anagramList;
                adb[word.length()] = newSumMap; 
            }
        }
        infile.close(); 
    } else {
        throw FileNotFoundException(dict);
    }   
}

std::vector<std::string> AnagramDatabase::findAnagrams(const std::string& anagram)
{
    std::vector<std::string> anagrams;
    anagram_db::const_iterator lenMapIt = adb.find(anagram.length());
    if (lenMapIt != adb.end())
    {
        int sum = getWordSum(anagram);
        char_sum_map::const_iterator sumMapIt = lenMapIt->second.find(sum);
        if (sumMapIt != lenMapIt->second.end())
            anagrams = adb[anagram.length()][sum];
    }
    return anagrams;
}

int AnagramDatabase::getWordSum(const std::string& word)
{
    int sum = 0;
    for (int i = 0; i < word.length(); i++)
        sum += (int) word.at(i);
    return sum;
}
