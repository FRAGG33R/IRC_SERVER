#include "../includes/Class.JOIN.hpp"

Join::Join()
{

}

void	Join::set_channels_keys(std::vector<std::string> __params , std::vector<Channel> __channels, int __new_client, std::string __sender_nickname)
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

	for (std::map<std::string, std::string>::iterator it = this->__channels.begin(); it != this->__channels.end(); it++)
	{
		
	}
}