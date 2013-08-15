#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class ErrorException : public std::exception
{
public:
    ErrorException(const char*);
    ~ErrorException() throw() {}

    const char *what() const throw();

private:

    const char* mMessage;

};


#endif // EXCEPTIONS_H
