#include "../includes/Class.PRIVMSG.hpp"

Privmsg::Privmsg()
{
}


std::vector<int> Privmsg::getReceivers() const
{
	return this->__receivers;
}

std::string Privmsg::getMessage() const
{
    return this->__message;
}

int Privmsg::getSender() const
{
    return this->__sender;
}

std::string Privmsg::getType() const
{
	return this->__type;
}

void Privmsg::setReceivers(std::vector<int> &receivers)
{
    this->__receivers = receivers;
}

void Privmsg::setMessage(std::string &message)
{
	this->__message = message;
}

void Privmsg::setSender(int sender)
{
	this->__sender = sender;
}

void Privmsg::setType(std::string &type)
{
	this->__type = type;
}
