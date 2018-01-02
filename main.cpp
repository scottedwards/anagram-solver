#include <iostream>
#include <string>
#include <set>

#include "AnagramDatabase.h"
#include "FileNotFoundException.h"

#define NT "\033[0m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[4;32m"
#define RED "\033[1;31m"
#define SEPBAR "--------------------------------------------------------------"

void commandHandler(const std::string& wholeCmd);

AnagramDatabase ad;

int main(int argc, char * argv[])
{
    //ask user for the word they want to solve
    std::cout << YELLOW << "Welcome to AnagramSolver v2.0" << NT << std::endl;
    std::cout << SEPBAR << std::endl 
        << "If you need a reminder on how this program works" << std::endl
        << "type in " << GREEN << ":help" << NT
        << ". If you have an alternate word file" << std::endl
        << "you want to use, use the " 
        << GREEN << ":dict <path_to_file> " << NT << "command" 
        << std::endl << SEPBAR << std::endl;

    std::string input;

    //set up the anagram database
    try
    {
        ad.setDictionary("words.txt");
    }
    catch (std::exception& e)
    {
        std::cout << RED << "The default 'words.txt' dictionary file" 
            << "cannot be found!" << NT << std::endl
            << "Please specify your own word list to use." << std::endl;
    }
    
    while (input != ":quit")
    {
        std::cout << "ASlv> ";
        std::getline(std::cin, input);
        try
        {
            //check if the input is a command or a word
            switch (input.at(0))
            {
                case ':':
                    commandHandler(input);
                    break;
                default:
                    std::cout << YELLOW <<  "Finding Anagrams..." << NT << std::endl;
                    typedef std::set<std::string> str_set;
                    str_set anagrams = ad.findAnagrams(input);
                    if (anagrams.empty())
                        std::cout << RED << "This is not a word!"
                            << NT << std::endl;
                    else
                        for (
                                str_set::const_iterator a = anagrams.cbegin();
                                a != anagrams.cend(); 
                                ++a
                            )
                            std::cout << " - " << *a << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cout << RED << "Error: " << NT << e.what() << std::endl;
        }

    }
    
    return 0;
}

void commandHandler(const std::string& wholeCmd)
{
    std::string cmd = "";
    int index = 1;
    //get the command name
    while (index < wholeCmd.length() && wholeCmd.at(index) != ' ') 
        cmd += wholeCmd.at(index++);

    if (cmd == "quit")
    {
        std::cout << YELLOW << "Bye" << NT << std::endl;
    }
    else if (cmd == "help")
    {
        std::cout << GREEN << "dict <path_to_file>" << NT << std::endl
            << " change the list of words the program uses to find anagrams"
            << std::endl;
    }
    else if (cmd == "dict")
    {
        std::string file = "";
        //move the index past the space
        index += 1;
        //get the next word after the command which will be file path
        while (index < wholeCmd.length() && wholeCmd.at(index) != ' ') 
            file += wholeCmd.at(index++);

        ad.setDictionary(file);
    }
    else
    {
        std::cout << RED << "Command not recognised." << NT << std::endl;
    }
}
