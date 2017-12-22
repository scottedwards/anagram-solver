#ifndef FILENOTFOUNDEXCEPTION_HEADER
#define FILENOTFOUNDEXCEPTION_HEADER

#include <exception>
#include <string>

class FileNotFoundException: public std::exception 
{
    public:
        explicit FileNotFoundException(const std::string& fileName);
        ~FileNotFoundException() throw ();
        virtual const char* what() const throw(); 

    private:
        std::string fileName;
};

#endif


