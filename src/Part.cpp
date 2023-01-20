#include "../includes/Class.part.hpp"
// If the last client leave the channel then the channel should be closed
// if the client was operator , then You should remove the client from the clients vector and the operators vector 

int    Part::part(std::vector<std::string> __params, int __client, std::vector<Channel> &__channels)
{
    __params[0].erase(__params[0].find_last_not_of("") + 1);
    std::vector<std::string>    __leave_channels;
    std::stringstream           __stream(__params[0]);
    std::string                 __temp;
    std::string                 __message;

    while(getline(__stream, __temp, ','))
    {
        if (!__temp.empty())
            __leave_channels.push_back(__temp);
    }
    for (size_t i = 0; i < __leave_channels.size(); i++)
    {
		if (__leave_channels[i][0] == '#')
		{
			int __channel_index = this->indexOfChannel(__leave_channels[i], __channels);
			if (__channel_index == -1)
			{
				__message = ": " + __leave_channels[i] + " 403 * No such channel\n";
				if (send(__client, __message.c_str(), __message.size(), 0) == -1)
					return (-1);
			}
			else
			{
				if (this->searchClient(__client, __channels, __channel_index))
				{
					for (size_t k = 0; k < __channels[__channel_index].get_clients_size(); k++)
					{
						if (__client == __channels[__channel_index].get_clients()[k].first)
						{
							this->noticeAll(__channels[__channel_index],  __channels[__channel_index].get_clients()[k].second);
							__channels[__channel_index].remove_client(k);
						}
					}
					for (size_t k = 0; k < __channels[__channel_index].get_operators().size(); k++)
					{
						if (__client == __channels[__channel_index].get_operators()[k].first)
							__channels[__channel_index].get_operators().erase(__channels[__channel_index].get_operators().begin() + k);
					}
				}
				else
				{
					__message = ": " + __leave_channels[i] + " 442 * You're not on that channel\n";
					if (send(__client, __message.c_str(), __message.size(), 0) == -1)
						return (-1);
				}
			}
		}
		else
		{
			__message = ": " + __leave_channels[i] + " 403 * No such channel\n";
			send(__client, __message.c_str(), __message.size(), 0);
		}
    }
	return (0);
}

void    Part::noticeAll(Channel __channel, std::string __client)
{
    std::string __message;
    for(size_t i = 0; i < __channel.get_clients_size(); i++)
    {
        __message = ":" + __client + " PART " + __channel.getchannelname() + "\n";
        send(__channel.get_clients()[i].first, __message.c_str(), __message.size(), 0);
    }
}

bool    Part::searchChannel(std::string __nameChannel, std::vector<Channel> __channels)
{
    bool found(false);
    
    for(size_t i = 0; i < __channels.size(); i++)
    {
        if (__nameChannel == __channels[i].getchannelname())
            found = true;
    }
    return found;
}

bool    Part::searchClient(int __clientId, std::vector<Channel> __channels, int	__channel_index)
{
    bool found(false);

    for (size_t i = 0; i <  __channels[__channel_index].get_clients_size(); i++)
    {
        if (__clientId == __channels[__channel_index].get_clients()[i].first)
            found = true;
    }
    return found;
}

int   Part::indexOfChannel(std::string __channelName, std::vector<Channel> __channels)
{
    for (size_t i = 0; i < __channels.size(); i++)
    {
        if (__channelName == __channels[i].getchannelname())
            return i;
    }
    return -1;
}