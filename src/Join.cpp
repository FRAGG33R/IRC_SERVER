#include "../includes/Class.JOIN.hpp"

Join::Join()
{

}

void	Join::parse_join_args(std::vector<std::string> &__params)
{
	std::string		__keys;
	std::string		__names;

	if (__params[0].find(" ") != std::string::npos)
	{
		__keys = __params[0].substr(__params[0].find(" ") + 1, std::string::npos);
		__names = __params[0].substr(0, __params[0].find(" "));
	}
	else
		__names = __params[0];
	while (__names.find(",") != std::string::npos && __keys.find(",") != std::string::npos)
	{
		this->__channels[__names.substr(0, __names.find(","))] = __keys.substr(0, __keys.find(","));
		__names = __names.substr(__names.find(",") + 1, std::string::npos);
		__keys = __keys.substr(__keys.find(",") + 1, std::string::npos);
	}
	while (__names.find(",") != std::string::npos)
	{
		if (!__keys.empty())
			this->__channels[__names.substr(0, __names.find(","))] = __keys.substr(0, std::string::npos);
		else
			this->__channels[__names.substr(0, __names.find(","))] =  std::string("");
		__keys.erase();
		__names = __names.substr(__names.find(",") + 1, std::string::npos);
	}
	if (!__keys.empty())
		this->__channels[__names.substr(0, std::string::npos)] = __keys.substr(0, std::string::npos);
	else
		this->__channels[__names.substr(0, std::string::npos)] = std::string("");
	__names.erase();
}

void Join::erase_channels( void )
{
	__channels.clear();
}

int	Join::set_channels_keys(std::vector<std::string> &__params , int __new_client, std::string __sender_nickname, std::vector<Channel> &ref_channels)
{
	size_t			__begin;
	size_t			__end;
	std::string		__message;

	this->parse_join_args(__params);
	bool	client_exist(false);
	bool	channel_exist(false);
	for (std::map<std::string, std::string>::iterator it = this->__channels.begin(); it != this->__channels.end(); it++)
	{
		channel_exist =  false;
		client_exist = false;
		for (size_t i = 0; i < ref_channels.size(); i++)
		{
			if (ref_channels[i].getchannelname() == it->first)
			{
				channel_exist = true;
				client_exist = false;
				for (size_t j = 0; j < ref_channels[i].get_clients().size(); j++)
				{
					if (ref_channels[i].get_clients()[j].second == __sender_nickname)
					{
						client_exist = true;
						__message = ":" + __sender_nickname + " 443 * is already on channel\n";
						if (send(__new_client, __message.c_str(), __message.size(), 0) == -1)
							return (-1);
						break ;
					}
				}
				if (!client_exist)
				{
					if (ref_channels[i].get_password().empty() || ref_channels[i].get_password() == it->second)
					{
						ref_channels[i].add_client(std::pair<int, std::string>(__new_client, __sender_nickname));
						__message = ":" + __sender_nickname + "JOIN * Welcome To " + it->first + " channel\n";
						if (send(__new_client, __message.c_str(), __message.size(), 0) == -1)
								return (-1);
					}
					else
					{
						__message = ":" + it->first + " 475 * Cannot join channel\n";
						if (send(__new_client, __message.c_str(), __message.size(), 0) == -1)
							return (-1);
					}
				}
			}
		}
		if (!channel_exist)
		{
			Channel	__new(it->first, it->second, std::pair<int, std::string>(__new_client, __sender_nickname), std::pair<int, std::string>(__new_client, __sender_nickname));
			ref_channels.push_back(__new);
			__message = ":" + __sender_nickname + " JOIN * Welcome To " + it->first + " channel\n";
			if (send(__new_client, __message.c_str(), __message.size(), 0) == -1)
					return (-1);
		}
	}
	return (0);
}
