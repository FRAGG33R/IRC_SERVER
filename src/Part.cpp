#include "../includes/Class.part.hpp"

void    Part::part(std::vector<std::string> __params, int __client, std::vector<Channel> &__channels)
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
			__leave_channels[i] = __leave_channels[i].substr(1, __leave_channels[i].size());
			for (size_t j = 0; j < __channels.size(); j++)
			{
				if (!this->searchChannel(__leave_channels[i], __channels))
				{
					__message = __leave_channels[i] + " :No such channel\n";
					send(__client, __message.c_str(), __message.size(), 0);
					break ;
				}
				else if (!this->searchClient(__client, __channels, __leave_channels[i]))
				{
					__message = __leave_channels[i] + " :You're not on that channel\n";
					send(__client, __message.c_str(), __message.size(), 0);
					break ; 
				}
				else if (this->searchClient(__client, __channels, __leave_channels[i]))
				{
					int index = this->indexOfChannel(__leave_channels[i], __channels);
					for (size_t k = 0; k < __channels[index].get_clients_size(); k++)
					{
						if (__client == __channels[index].get_clients()[k].first){
							this->noticeAll(__channels[index],  __channels[index].get_clients()[k].second);
							__channels[index].remove_client(k);
						}
					}
				}
			}
		}
		else
		{
			__message = __leave_channels[i] + " :No such channel\n";
			send(__client, __message.c_str(), __message.size(), 0);
		}
    }
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

bool    Part::searchClient(int __clientId, std::vector<Channel> __channels, std::string __nameChannel)
{
    bool found(false);

    int index = this->indexOfChannel(__nameChannel, __channels);
    for (size_t i = 0; i <  __channels[index].get_clients_size(); i++)
    {
        if (__clientId == __channels[index].get_clients()[i].first)
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