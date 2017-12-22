#include <iostream>
#include <string>

#include "AnagramDatabase.h"
#include "FileNotFoundException.h"

#define NT "\033[0m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[4;32m"
#define RED "\033[1;31m"
#define SEPBAR "--------------------------------------------------------------"

void commandHandler(const std::string& cmd);

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
        ad.setDictionary("fakewords.txt");
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
                    std::cout << "Finding Anagrams..." << std::endl;
                    std::vector<std::string> anagrams = ad.findAnagrams(input);
                    for (int i = 0; i < anagrams.size(); i++)
                        std::cout << " - " << anagrams[i] << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }

    }
    
    return 0;
}

void commandHandler(const std::string& cmd)
{

}
