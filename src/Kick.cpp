# include "../includes/Class.KICK.hpp"
//garbage value in the reason message
// the operator can kick himself

void	Kick::kick(std::vector<std::string> __params, std::pair<std::string, int> __client, std::vector<Channel> &__channels)
{
    __params[0].erase(__params[0].find_last_not_of(" ") + 1);
    std::string                 __message;
    std::string                 __nameofchannels;
    std::string                 __nameofclients;
    std::string                 __tmp;
    std::vector<std::string>    __args;
    std::vector<std::string>    __listofchannels;
    std::vector<std::string>    __listofclients;
    std::stringstream           __splitargs(__params[0]);
    while (getline(__splitargs, __tmp, ' '))
    {
        if (!__tmp.empty())
            __args.push_back(__tmp);
    }
 
    std::stringstream           __splitchannels(__args[0]);
	if (__args.size() == 1)
	{
		__message =  std::string(RED) + ": " + __client.first + " 401 * No such nick/channel\n" + std::string(RESET);
		send(__client.second, __message.c_str(), __message.size(), 0);
		return ;
	}
    std::stringstream           __splitclients(__args[1]);
    
    __tmp.erase();
    while(getline(__splitchannels, __tmp, ','))
    {
        if (!__tmp.empty())
            __listofchannels.push_back(__tmp);
    }
    __tmp.erase();

    while(getline(__splitclients, __tmp, ','))
    {
        if (!__tmp.empty())
            __listofclients.push_back(__tmp);
    }

    for (size_t i = 0; i < __listofchannels.size(); i++)
    {
        if (__listofchannels[i][0] != '#')
        {
			__message = std::string(RED) + ": " + __listofchannels[i] + " 403 * No such channel\n" + std::string(RESET);
            send(__client.second, __message.c_str(), __message.size(), 0);
            __listofchannels.erase(__listofchannels.begin());
        }
    }

    for (size_t i = 0; i < __listofchannels.size(); i++)
    {
        if (!this->searchChannel(__listofchannels[i], __channels))
        {
			__message = std::string(RED) + ": " + __listofchannels[i] + " 403 * No such channel\n" + std::string(RESET);
            send(__client.second, __message.c_str(), __message.size(), 0);
        }
        else if (!this->searchClient(__client.second, __channels, __listofchannels[i]))
        {
			__message = std::string (RED) + ": " + __listofchannels[i] + " 442 * You're not on that channel\n" + std::string(RESET);
            send(__client.second, __message.c_str(), __message.size(), 0);
        }
        else if (this->searchClient(__client.second, __channels, __listofchannels[i]))
        {
			bool	__is_operator = this->checkOperator(__client.second, __channels, __listofchannels[i]);
			if (__is_operator)
			{
				for (size_t j = 0; j < __listofclients.size(); j++)
                {
                    if (this->searchClient(__listofclients[j], __channels, __listofchannels[i]))
                    {
						std::cout << "!!!\n";
						std::cout << "there is  " << __channels.size() << " channels before \n";
						std::cout << "this channel contain " << __channels[i].get_clients().size() << " client \n";
						this->noticeAll(__channels[i], __client.second, __listofclients[j], (__params[1].size() > 1 && __params[1][0] == ':'), __params[1]);
						std::cout << "Shoud I remove " << this->indexOfClient(__listofclients[j], __channels, __listofchannels[i]) << "client\n";
						__channels[i].get_clients().erase(__channels[i].get_clients().begin() + this->indexOfClient(__listofclients[j], __channels, __listofchannels[i]));
						// if (__channels[i].get_clients().size() == 0)
						// 	__channels.erase(__channels.begin() + i);
						std::cout << "there is  " << __channels.size() << " channels after \n";
                    }
					else
					{
						__message  = std::string(RED) + ":" + __listofclients[j] + " 401 * No such nick/channel\n" + std::string(RESET);
						send(__client.second, __message.c_str(), __message.size(), 0);
					}
                }
			}
			else
			{
				__message = std::string (RED) + ": " + __listofchannels[i] + " 482 * You're not channel operator\n" + std::string(RESET);
				send(__client.second, __message.c_str(), __message.size(), 0);
			}
        }
    }
}

void	Kick::noticeAll(Channel __channel,int   __client, std::string  __nameofclient, bool    __reason, std::string __reasonMsg)
{
    (void) __client;
    std::string __message;

    if (__reason && !(__reasonMsg.size() == 1 && __reasonMsg[0] == ':'))
    {
        __message =  "KICK " + __channel.getchannelname() + " " + __nameofclient + " "+ __reasonMsg +"\n";
        for(size_t i = 0; i < __channel.get_clients_size(); i++)
        {
			if (__channel.get_clients()[i].first != __client)
            	send(__channel.get_clients()[i].first, __message.c_str(), __message.size(), 0);
        }
    }
    else
    {
		__message =  "KICK " + __channel.getchannelname() + " " + __nameofclient + "\n";
        for(size_t i = 0; i < __channel.get_clients_size(); i++)
        {
			if (__channel.get_clients()[i].first != __client)
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

bool	Kick::searchClient(int __clientId, std::vector<Channel> __channels, std::string __nameChannel)
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

bool	Kick::searchClient(std::string  __client, std::vector<Channel> __channels, std::string __nameChannel)
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

int		Kick::indexOfChannel(std::string __channelName, std::vector<Channel> __channels)
{
    for (size_t i = 0; i < __channels.size(); i++)
    {
        if (__channelName == __channels[i].getchannelname())
            return i;
    }
    return -1;
}