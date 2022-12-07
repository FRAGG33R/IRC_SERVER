#include "includes/main.hpp"

Client::Client()
{
	this->__name = "Client";
	this->__password = "*******";
	this->__neckname = "ClientNeckname";
	this->__id = 0;
	this->__is_operator =  false;
}

Client::Client(string name, string password, string neckname, int id, bool is_operator) : 
													__name(name), __password(password), 
													__neckname(neckname), __id(id), 
													__is_operator(is_operator)
{}

Client::Client(const Client& other) : 
				__name(other.__name), __password(other.__password),
				__neckname(other.__neckname), __id(other.__id),
				__is_operator(other.__is_operator)
{}

Client::~Client(){}
