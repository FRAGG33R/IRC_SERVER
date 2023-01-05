#include "../includes/main.hpp"

Registration::Registration()
{
	this->pass = false;
	this->nick = false;
	this->user = false;
}

bool Registration::get_pass() const
{
	return (this->pass);
}

bool Registration::get_nick() const
{
	return (this->nick);
}

bool Registration::get_user() const
{
	return (this->user);
}

void Registration::set_pass(bool __bool)
{
	this->pass = __bool;
}

void Registration::set_nick(bool __bool)
{
	this->nick = __bool;
}

void Registration::set_user(bool __bool)
{
	this->user = __bool;
}
