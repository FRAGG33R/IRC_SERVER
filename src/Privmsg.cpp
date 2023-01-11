#include "../includes/Class.PRIVMSG.hpp"

Privmsg::Privmsg()
{
}

Privmsg::~Privmsg()
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

int		Privmsg::parsPrivmsg(std::vector<std::string> __params, std::vector<std::string> __clients, std::vector<Channel> __channels)
{
	std::vector<std::string> substrings;
	std::stringstream stream(__params[0]);
	std::string temp;
	while (getline(stream, temp, ',')) {
		if (!temp.empty())
			substrings.push_back(temp);
	}
	for (size_t i = 0; i < substrings.size(); i++)
	{
		
	}

	return (0);
}