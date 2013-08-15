#include "Exceptions.h"


ErrorException::ErrorException(const char* message)
    : mMessage(message)
{}

const char * ErrorException::what() const throw()
{
    return mMessage;
}
