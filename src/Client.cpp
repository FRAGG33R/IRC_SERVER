#include "../includes/main.hpp"

Client::Client(string username, string nickname, bool is_operator, bool authentication, int fd)
{
	this->__username = username;
    this->__nickname = nickname;
	this->__is_operator = is_operator;
    this->__authentication = authentication;
	this->__fd = fd;
}

Client::~Client(){}