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
        //clear the database
        adb.clear();
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
                    (sumMapIt->second).insert(word);
                }
                else
                {
                    std::set < std::string > anagramList;
                    anagramList.insert(word);
                    lenMapIt->second[sum] = anagramList;
                }
            }
            else
            {
                //there has been no word with this length before
                char_sum_map newSumMap;
                std::set < std::string > anagramList;
                anagramList.insert(word);

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

std::set<std::string> AnagramDatabase::findAnagrams(const std::string& anagram)
{
    std::set<std::string> anagrams;
    //check for a wild-card
    size_t wildcard = anagram.find('?');
    if (wildcard != std::string::npos)
    {
        //if there is a wild-card symbol, split the word in two
        //and use find anagram on all possible combinations
        std::string first = anagram.substr(0, wildcard);
        std::string second = anagram.substr(wildcard + 1, anagram.length());
        //[33, 126] is the range of all printable ASCII characters
        for (int i = 97; i <= 122; i++)
        {
            char possibility = (char) i;
            std::string possibleWord = first + possibility + second;
            std::set<std::string> anagram_subset = findAnagrams(possibleWord); 
            //insert all anagrams found in the subset into the main set
            //insert makes sure it does not add duplicates.
            anagrams.insert(anagram_subset.begin(), anagram_subset.end());
        }
    }
    else
    {
        //if there are no wildcards
        anagram_db::const_iterator lenMapIt = adb.find(anagram.length());
        if (lenMapIt != adb.end())
        {
            int sum = getWordSum(anagram);
            char_sum_map::const_iterator sumMapIt = lenMapIt->second.find(sum);
            if (sumMapIt != lenMapIt->second.end())
                anagrams = adb[anagram.length()][sum];
        }
        //remove any words that are in the returned set that are not anagrams.
        filter(anagrams, anagram, &isAnagram);
    }

    return anagrams;
}

void AnagramDatabase::filter(std::set <std::string>& st, 
        const std::string& proposition,
        bool (*predicate)(const std::string& s1, const std::string& s2))
{
    typedef std::set < std::string > str_set;
    for (str_set::iterator elem = st.begin(); elem != st.end();)
    {
        if (!predicate(proposition, *elem)) 
            //erase returns an iterator that is incremented from the one
            //that was deleted (so deleting does not mess up pasing through the set).
            elem = st.erase(elem);
        else
            elem = ++elem;
    }
}

bool AnagramDatabase::isAnagram(const std::string& a1, const std::string& a2)
{
    typedef std::unordered_map<char, int> charMap;
    if (a1.length() != a2.length()) return false;
    //a map that will store the number of times a character has appeared
    //in a1 minus the number of times the same character has apeared in a2
    charMap charCount;
    charMap::iterator it1;
    charMap::iterator it2;

    for (int i = 0; i < a1.length(); ++i)
    {
        //increment the value for the character at position i for a1
        it1 = charCount.find(a1.at(i));
        if (it1 != charCount.end())
            charCount[a1.at(i)] += 1; 
        else
            charCount[a1.at(i)] = 1;

        //increment the value for the character at position i for a1
        it2 = charCount.find(a2.at(i));
        if (it2 != charCount.end())
            charCount[a2.at(i)] -= 1; 
        else
            charCount[a2.at(i)] = -1;
    }

    for (charMap::iterator pair = charCount.begin(); pair != charCount.end(); ++pair)
        if (pair->second != 0) return false; 

    return true;
}

int AnagramDatabase::getWordSum(const std::string& word)
{
    int sum = 0;
    for (int i = 0; i < word.length(); i++)
        sum += (int) word.at(i);
    return sum;
}
