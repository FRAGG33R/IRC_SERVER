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

int Mode::parseMode(std::vector<std::string> __params,  std::vector<Channel> __channels)
{
	int		__valid = 0;
	size_t 	__index = 0;
	if (__params[0][0] != '#')
	{
		//error message
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
		//error message
	}
	if ((__params[1][0]  != '-' && __params[1][0] != '+'))
    {
        //error message 501
    }
	if (__params[1][1] != 'o' || __params[1].size() > 2 )
	{
		//error message 472
	}
	for (size_t i = 0; i < __channels[__index].get_clients().size(); i++)
	{
		// if (__params[2] == __channels[__index].get_clients()[i])
		// {
		// }
	}
	return (0);
}