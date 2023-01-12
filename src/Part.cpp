#include "../includes/Class.part.hpp"

void    Part::part(std::vector<std::string> __params, int __client, std::vector<Channel> __channels, int __sender, std::string __sender_nickname)
{
    __params[0].erase(__params[0].find_last_not_of("") + 1);
    std::vector<std::string>    __leave_channels;
    std::stringstream           __stream(__params[0]);
    std::string                 __temp;

    while(getline(__stream, __temp, ','))
    {
        if (!__temp.empty())
            __leave_channels.push_back(__temp);
    }
    for (size_t i = 0; i < __leave_channels.size(); i++)
    {
        for (size_t j = 0; j < __channels.size(); j++)
        {
            if (!this->searchChannel(__leave_channels[i], __channels))
            {
                std::cout << __leave_channels[i] << " :No such channel" << std::endl;
                break ; 
            }
            else if (!this->searchClient(__client, __channels, __leave_channels[i]))
            {
                std::cout << __leave_channels[i] <<" :You're not on that channel" << std::endl;
                break ; 
            }
            
        }
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
        if (__clientId == __channels[index].get_clients()[i])
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