#include "../includes/Class.KICK.hpp"

void    Kick::kick(std::vector<std::string> __params, int __client, std::vector<Channel> __channels)
{
    std::string     __nameChannel = __params[0].erase(__params[0].find_last_not_of(" ") + 1);
    std::string     __message;
    
    for (size_t i = 0; i < __channels.size(); i++)
    {
        if (!this->searchChannel(__nameChannel, __channels))
        {
            __message = __nameChannel + " :No such channel\n";
            send(__client, __message.c_str(), __message.size(), 0);
            break ; 
        }
        else if (!this->searchClient(__client, __channels, __nameChannel))
        {
            __message = __nameChannel + " :You're not on that channel\n";
            send(__client, __message.c_str(), __message.size(), 0);
            break ;
        }
        else if (this->searchClient(__client, __channels, __nameChannel))
        {
            if (!this->checkOperator(__client, __channels, __nameChannel))
            {
                __message = __nameChannel + " :You're not channel operator\n";
                send(__client, __message.c_str(), __message.size(), 0);
            }
            else
            {
                if (this->searchClient(__params[1], __channels, __nameChannel))
                {
                    if (__params[2][0] == ':')
                    {
                        this->noticeAll(__channels[i], __client, true, __params[2]);
                        __channels[i].remove_client(this->indexOfClient(__params[1], __channels, __nameChannel));
                    }
                    else
                    {
                        this->noticeAll(__channels[i], __client, false, NULL);
                        __channels[i].remove_client(this->indexOfClient(__params[1], __channels, __nameChannel));
                    }
                }
            }
        }
    }
}


void    Kick::noticeAll(Channel __channel,int   __client, bool    __reason, std::string __reasonMsg)
{
    std::string __message;
    if (__reason)
    {
        for(size_t i = 0; i < __channel.get_clients_size(); i++)
        {
            __message =  "KICK " + __channel.getchannelname()+ " " + __channel.get_clients()[__client].second + __reasonMsg +"\n";
            send(__channel.get_clients()[i].first, __message.c_str(), __message.size(), 0);
        }
    }
    else
    {
        for(size_t i = 0; i < __channel.get_clients_size(); i++)
        {
            __message =  "KICK " + __channel.getchannelname()+ " " + __channel.get_clients()[__client].second +"\n";
            send(__channel.get_clients()[i].first, __message.c_str(), __message.size(), 0);
        }
    }
}

bool    Kick::checkOperator(int   __id, std::vector<Channel> __channels, std::string __nameChannel)
{
    bool found(false);
    int index = this->indexOfChannel(__nameChannel, __channels);
    for (size_t i = 0; i < __channels[index].get_clients_size(); i++)
    {
        if (__id ==  __channels[index].get_operators()[i].first)
            found = true;
    }
    return found;
}

bool    Kick::searchChannel(std::string __nameChannel, std::vector<Channel> __channels)
{
    bool found(false);
    
    for(size_t i = 0; i < __channels.size(); i++)
    {
        if (__nameChannel == __channels[i].getchannelname())
            found = true;
    }
    return found;
}


int    Kick::indexOfClient(std::string __client, std::vector<Channel> __channels, std::string __nameChannel)
{
 
    int index = this->indexOfChannel(__nameChannel, __channels);
    for (size_t i = 0; i <  __channels[index].get_clients_size(); i++)
    {
        if (__client == __channels[index].get_clients()[i].second)
            return i;
    }
    return -1;
}

bool    Kick::searchClient(int __clientId, std::vector<Channel> __channels, std::string __nameChannel)
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

bool    Kick::searchClient(std::string  __client, std::vector<Channel> __channels, std::string __nameChannel)
{
    bool found(false);

    int index = this->indexOfChannel(__nameChannel, __channels);
    for (size_t i = 0; i <  __channels[index].get_clients_size(); i++)
    {
        if (__client == __channels[index].get_clients()[i].second)
            found = true;
    }
    return found;
}

int   Kick::indexOfChannel(std::string __channelName, std::vector<Channel> __channels)
{
    for (size_t i = 0; i < __channels.size(); i++)
    {
        if (__channelName == __channels[i].getchannelname())
            return i;
    }
    return -1;
}