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

int		Privmsg::parsPrivmsg(std::vector<std::string> __params, std::vector<std::pair<std::string, int> > __clients, std::vector<Channel> &__channels, int __sender, std::string __sender_nickname, bool __command)
{

// 	:Angel PRIVMSG Wiz :Hello are you receiving this message ?
//                                 ; Message from Angel to Wiz.
	std::vector<std::string>	__given_clients;
	__params[0].erase(__params[0].find_last_not_of(" ") + 1);
	std::stringstream 			stream(__params[0]);
	std::string					temp;
	std::string                 __message;

	__message  = __params[1];
	// if (__params[0][0] == ':' || __params[1][0] != ':')
	// 	return 412;
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
				if (__given_clients[i] == __channels[k].getchannelname())
				{
					for (size_t l = 0; l < __channels[k].get_clients().size(); l++)
					{
						if (__command)
							this->setMessage(":" + __sender_nickname + " PRIVMSG " + __channels[k].get_clients()[l].second + " " +  __message  + "\n");
						else
							this->setMessage(":" + __sender_nickname + " NOTICE " + __channels[k].get_clients()[l].second + " " +  __message  + "\n");
						if (send(__channels[k].get_clients()[l].first, this->getMessage().c_str(), this->getMessage().size(), 0) == -1)
							return (-1);
					}
				}
				else
				{
					if (__command)
					{
						std::string msg(std::string(RED) + ":" + __sender_nickname + " 401 " + __given_clients[i] + " No such nick/channel\n" + std::string(RESET));
						if (send(__sender, msg.c_str(), msg.size(), 0) == -1)
							return (-1);
					}
				}
			}
		}
		else
		{
			int	__index = client_exist(__clients, __given_clients[i]);
			if (__index != -1)
			{
				if (__command)
					this->setMessage(":" + __sender_nickname + " PRIVMSG " + __clients[__index].first + " " +  __message  + "\n");
				else
					this->setMessage(":" + __sender_nickname + " NOTICE " + __clients[__index].first + " " +  __message  + "\n");
				if (send(__clients[__index].second, this->getMessage().c_str(), this->getMessage().size(), 0) == -1)
					return (-1);
			}
			else
			{
				if (__command)
				{
					std::string msg(std::string(RED) + ":" + __sender_nickname + " 401 " + __given_clients[i] + " No such nick/channel\n" + std::string(RESET));
					if (send(__sender, msg.c_str(), msg.size(), 0) == -1)
						return (-1);
				}
			}
		}
	}
	return (-2);
}

int	Privmsg::client_exist(std::vector<std::pair<std::string, int> > __client_list, std::string __client)
{
	for (size_t j = 0; j < __client_list.size(); j++)
	{
		if (__client == __client_list[j].first)
			return (j);
	}
	return (-1);
}