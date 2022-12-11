#include "../includes/main.hpp"

Error::Error()
{
	this->__message = string(RED) + "an error has been occurred" + string(RESET);
}

Error::Error(const std::string& message)
{
	this->__message = string(RED) + message + string(RESET);
}

const char *Error::what() const throw()
{
	return(this->__message.c_str());
}
