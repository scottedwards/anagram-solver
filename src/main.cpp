#include <iostream>
#include <string>
#include <set>

#include <stdio.h>  
#include <unistd.h> 

#include "AnagramDatabase.h"
#include "FileNotFoundException.h"

void printUsage();  


int main(int argc, char * argv[])
{
    AnagramDatabase ad;
    std::string anagram = "";
    std::string dictionary = "/usr/share/dict/words";

    // parse the options
    int opt;
    while((opt = getopt(argc, argv, ":d:h")) != -1)  
    {  
        switch(opt)  
        {  
            case 'd':  
                dictionary = optarg;
                break;  
            case 'h':  
                printUsage();
                return 0;  
            case ':':  
            default:  
                printUsage();
                return 1;
        }  
    } 

    // make sure they've put the options before the anagram
    if (optind < argc - 1) {
        printUsage();
        return 1;
    }

    if (argv[optind] == NULL) {
        printf("Anagram argument missing!\n\n");
        printUsage();
        return 1;
    }
    anagram = argv[optind];

    // set up the anagram database
    try
    {
        ad.setDictionary(dictionary);
    }
    catch (std::exception& e)
    {
        std::cout << "The default dictionary file at '" << dictionary << "' " 
            << "cannot be found!" << std::endl
            << "Please specify your own word list to use." << std::endl;
        return 1;
    }
    
    // find the anagrams
    std::cout << "Finding anagrams of '" << anagram << "'..." << std::endl;
    typedef std::set<std::string> str_set;
    str_set anagrams = ad.findAnagrams(anagram);

    // print them out
    if (anagrams.empty())
        std::cout << "No anagrams found!" << std::endl;
    else
        for (str_set::const_iterator a = anagrams.cbegin(); a != anagrams.cend(); ++a)
            std::cout << *a << std::endl;
    
    return 0;
}

void printUsage()
{
    std::cout << "solve_anagram, version 2.0" << std::endl << std::endl << 
        "usage: solve_anagram [-h] [-d dictionary] anagram ..." << std::endl << std::endl <<
        "  h : print this help message" << std::endl << // std::endl <<
        "  d dictionary : use an alternate word file located at this path" << std::endl;
}
