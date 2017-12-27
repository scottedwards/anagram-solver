#ifndef ANAGRAMDATABASE_HEADER
#define ANAGRAMDATABASE_HEADER

#include <set>
#include <string>
#include <unordered_map>

//the type that the anagram database will have
typedef std::unordered_map < int, std::set < std::string > > char_sum_map;
typedef std::unordered_map < int, char_sum_map > anagram_db;

/** 
 * My Anagram Database Class.
 * A class that loads words from a text file into a data structure
 * and then can find anagrams of a given word.
 */
class AnagramDatabase
{
    public:
        /**
         * Default Contructor.
         * Just used to declare the class, the word file is not loaded yet.
         */
        AnagramDatabase();
        /**
         * Constructor that takes a path to a word file.
         * Loads all words from the text file into the hashmaps.
         */
        AnagramDatabase(const std::string& dict) throw (std::exception);
        /**
         * Copy constructor.
         * Copies over the hasmaps;
         */
        AnagramDatabase(const AnagramDatabase &ad);
        /**
         * Finds all possible anagrams of a word.
         * For this to work, the hashmaps must be populated.
         */
        std::set<std::string> findAnagrams(const std::string& anagram);
        /**
         * Uses the given word file for a dictionary.
         */
        void setDictionary(const std::string& dict) throw (std::exception); 
        /**
         * Returns if a word is an anagram of another word.
         * Does this by comparing the amount of times a character pops up in
         * each word (they must be equal for all characters)
         */
        static bool isAnagram(const std::string& a1, const std::string& a2);

    private:
        anagram_db adb;
        int getWordSum(const std::string& word);
        /**
         * Given a set, a proposition and a predicate, it removes all elements
         * that do not satisfy the predicate.
         */
        static void filter(std::set <std::string>& st, 
            const std::string& proposition,
            bool (*predicate)(const std::string& s1, const std::string& s2));
};

#endif
