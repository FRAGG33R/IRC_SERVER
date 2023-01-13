#include "../includes/Class.JOIN.hpp"

Join::Join()
{

}

int	Join::set_channels_keys(std::vector<std::string> __params , std::vector<Channel> &__channels, int __new_client, std::string __sender_nickname, std::vector<Channel> &ref_channels)
{
	size_t			__begin;
	size_t			__end;
	std::string		__names;
	std::string		__keys;

//JOIN kamal,#sba3,#lba3,#nmer,#faouzi key1,key2,key3

	/* (void)__channels;
	(void)__sender_nickname;
	(void)__new_client; */
	//TODO send error if there is a message to send
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

	bool	client_exist(false);
	for (std::map<std::string, std::string>::iterator it = this->__channels.begin(); it != this->__channels.end(); it++)
	{
		for (size_t i = 0; i < __channels.size(); i++)
		{
			if (it->first[0] == '#' && __channels[i].getchannelname() == it->first)
			{
				for (size_t j = 0; j < __channels[i].get_clients().size(); j++)
					if (__channels[i].get_clients()[j].second == __sender_nickname)
						client_exist = true;
				if (!client_exist)
				{
					if (!__channels[i].get_password().empty())
					{
						if (__channels[i].get_password() == it->second)
						{
							if (send(__new_client, "welcome to channel\n", sizeof("welcome to channel\n"), 0) == -1)
								return (-1);
						}
						else
							if (send(__new_client, "incorrect password\n", sizeof("incorrect password\n"), 0) == -1)
								return (-1);
					}
					else
					{
						__channels[i].add_client(std::pair<int, std::string>(__new_client, __sender_nickname));
						if (send(__new_client, "welcome to channel\n", sizeof("welcome to channel\n"), 0) == -1)
								return (-1);
					}
				}
				else
				{
					Channel	__new(it->first, it->second, std::pair<int, std::string>(__new_client, __sender_nickname), std::pair<int, std::string>(__new_client, __sender_nickname));
					ref_channels.push_back(__new);
				}
			}
		}
	}
	return (0);
}