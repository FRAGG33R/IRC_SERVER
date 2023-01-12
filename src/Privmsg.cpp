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


std::string Privmsg::getType() const
{
	return this->__type;
}

void Privmsg::setReceivers(std::vector<int> &receivers)
{
    this->__receivers = receivers;
}

void Privmsg::setMessage(std::string message)
{
	this->__message = message;
}

void Privmsg::setType(std::string &type)
{
	this->__type = type;
}

int		Privmsg::parsPrivmsg(std::vector<std::string> __params, std::vector<std::pair<std::string, int> > __clients, std::vector<Channel> __channels, int __sender, std::string __sender_nickname)
{
	std::vector<std::string>	__given_clients;
	__params[0].erase(__params[0].find_last_not_of(" ") + 1);
	std::stringstream 			stream(__params[0]);
	std::string					temp;
	std::string                 __message;

	__message  = __params[1];
	if (__params[0][0] == ':' || __params[1][0] != ':')
		return 412;
	while (getline(stream, temp, ','))
	{
		if (!temp.empty())
			__given_clients.push_back(temp);
	}
	for (size_t i = 0; i < __given_clients.size(); i++)
	{
		if (__given_clients[i][0] == '#')
		{
			for (size_t k = 0; k < __channels.size(); k++)
			{
				if (__given_clients[i].substr(1, __given_clients[i].size()) == __channels[k].getchannelname())
				{
					for (size_t l = 0; l < __channels[k].get_clients().size(); l++) {
						this->setMessage(":" + __sender_nickname + " PRIVMSG * " + __message  + "\n");
						std::cout << "The full message is " << this->getMessage();
						if (send(__channels[k].get_clients()[l].first, this->getMessage().c_str(), this->getMessage().size(), 0) == -1)
							return (-1);
					}
					break;
				}
				else
				{
					std::string msg(":" + __sender_nickname + " 401 * No such nick/channel\n");
					if (send(__sender, msg.c_str(), msg.size(), 0) == -1)
						return (-1);
				}
			}
		}
		else
		{
			for (size_t j = 0; j < __clients.size(); j++)
			{
				if (__clients[j].second != __sender) {
					if (__given_clients[i] == __clients[j].first) {
						this->setMessage(":" + __sender_nickname + " PRIVMSG * " + __message  + "\n");
						if (send(__clients[j].second, this->getMessage().c_str(), this->getMessage().size(), 0) == -1)
							return (-1);
					}
					else
					{
						std::string msg(":" + __sender_nickname + " 401 * No such nick/channel\n");
						if (send(__sender, msg.c_str(), msg.size(), 0) == -1)
							return (-1);
					}
				}
			}
		}
	}
	return (0);
}