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

int		Privmsg::parsPrivmsg(std::vector<std::string> __params, std::vector<std::pair<std::string, int> > __clients, std::vector<Channel> __channels)
{
	std::vector<std::string>	__given_clients;
	std::vector<int>			__clients_fds;
	std::stringstream 			stream(__params[0]);
	std::string					temp;
	size_t						__flag = 0;

	if (__params[0][0] == ':')
		return 411;
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
					for (size_t l = 0; l < __channels[k].get_clients().size(); l++)
						__clients_fds.push_back(__channels[k].get_clients()[l]);
					__flag++;
					break;
				}
			}
		}
		else
		{
			for (size_t j = 0; j < __clients.size(); j++)
			{
				if (__given_clients[i] == __clients[j].first) {
					__clients_fds.push_back(__clients[j].second);
					__flag++;
				}
			}
		}
	}
	if (__flag != __given_clients.size())
	    return 401;
	Privmsg	__repair;
	if (__params[1][0] == ':')
		__repair.setMessage(__params[1].substr(1, __params[1].size()));
	__repair.setReceivers(__clients_fds);
	//debug
	// std::cout << "The receivers" << std::endl;
	// for (size_t i = 0; i < __repair.getReceivers().size(); i++)
	// {
	// 	std::cout << __repair.getReceivers()[i] << std::endl;
	// }
	// std::cout << "The message" << std::endl;
	// std::cout << __repair.getMessage() << std::endl;
	
	return (0);
}