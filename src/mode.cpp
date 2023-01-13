# include "../includes/Class.MODE.hpp"

Mode::Mode()
{

}

Mode::~Mode()
{

}

void Mode::setType(char Type)
{
	this->__type = Type;
}

char Mode::getType()
{
    return this->__type;
}

void Mode::setChannelName(std::string  Name)
{
	this->__channel_name = Name;
}

std::string Mode::getChannelName()
{
	return this->__channel_name;
}

int Mode::parseMode(std::vector<std::string> __params,  std::vector<Channel> &__channels, int __sender, std::string __sender_name)
{
	int							__valid = 0, __is_op = 0;
	size_t						__index = 0;

	std::string					__temp;
	std::vector<std::string>    __temp_vec;
	std::stringstream 			__stream(__params[0]);
	std::string					__message = ":" + __sender_name + " MODE 403 * : No such channel\n";

	while (getline(__stream, __temp, ' '))
	{
		if (!__temp.empty())
			__temp_vec.push_back(__temp);
	}
	__params = __temp_vec;
	__temp_vec.clear();
	if (__params[0][0] != '#')
	{
		if (send(__sender, __message.c_str(), __message.size(), 0) == -1)
			return (-1);
		return (0);
	}
	for (; __index < __channels.size(); __index++)
	{
		if (__params[0].substr(1, __params[0].size()) == __channels[__index].getchannelname())
		{
			__valid = 1;
			break;
		}
	}
	if (__valid == 0)
	{
		if (send(__sender, __message.c_str(), __message.size(), 0) == -1)
			return (-1);
		return (0);
	}
	else
	{
		if ((__params[1][0]  != '-' && __params[1][0] != '+'))
		{
			__message = ":" + __sender_name + " 501 * Unknown MODE flag\n";
			if (send(__sender, __message.c_str(), __message.size(), 0) == -1)
				return (-1);
			return (0);
		}
		if (__params[1][1] != 'o' || __params[1].size() > 2 )
		{
			__message  = ":" + __sender_name + " 472 * is unknown mode char to me\n";
			if (send(__sender, __message.c_str(), __message.size(), 0) == -1)
				return (-1);
			return (0);
		}
		for (size_t i = 0; i < __channels[__index].get_operators().size(); i++)
		{
			if (__sender_name == __channels[__index].get_operators()[i].second)
				__is_op = 1;
		}
		if (__is_op == 1)
        {
			for (size_t i = 0; i < __channels[__index].get_clients().size(); i++)
			{
				if (__params[2] == __channels[__index].get_clients()[i].second)
					return (__channels[__index].add_operator(std::pair<int, std::string> (__channels[__index].get_clients()[i].first, __channels[__index].get_clients()[i].second)), 0);
			}
			__message  = ":" + __sender_name + " 401 * No such nick/channel\n";
			if (send(__sender, __message.c_str(), __message.size(), 0) == -1)
				return (-1);
		}
		else
		{
			__message  = ":" + __sender_name + " 482 * You're not channel operator\n";
			if (send(__sender, __message.c_str(), __message.size(), 0) == -1)
				return (-1);
		}
	}

	return (0);
}