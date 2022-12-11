#include "../includes/Class.error.hpp"

Error::Error()
{
	this->__message = "an error has been occurred";
}

Error::Error(const std::string& message)
{
	this->__message = message;
}

const char *Error::what() const throw()
{
	return(this->__message.c_str());
}
