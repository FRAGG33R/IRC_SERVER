#include "../includes/Class.TOPIC.hpp"
# include "../includes/main.hpp"


void    Topic::topic(std::vector<std::string> __params, std::pair<std::string, int> __client, std::vector<Channel> &__channels){
    __params[0].erase(__params[0].find_last_not_of(" ") + 1);
    std::string             __message;
    std::string             __error;
    std::string             __tmp;


    if (!this->searchChannel(__params[0], __channels))
    {
        __error = std::string(RED) + ": " + __error + " 403 * No such channel\n" + std::string(RESET);
        if (send(__client.second, __error.c_str(), __error.size(), 0) == -1) throw Error("falling to send msg");
        return ;
    }
    if (__params[0][0] != '#'){
        __error = std::string(RED) + ": " + __params[0] + " 403 * No such channel\n" + std::string(RESET);
        if (send(__client.second, __error.c_str(), __error.size(), 0) == -1) throw Error("falling to send msg");
        return ;
    }
    
    
    if (__params.size() > 1)
    {
        if (__channels[indexOfChannel(__params[0], __channels)].get_topic()){
            __message = __params[1];
            if (!this->searchClient(__client.first, __channels, __params[0]))
            {
                __message = std::string (RED) + ":   442 * You're not on that channel\n" + std::string(RESET);
                if (send(__client.second, __message.c_str(), __message.size(), 0) == -1) throw Error("falling to send msg");
                return ;
            }
            if (checkOperator(__client.second, __channels, __params[0])){
                __channels[indexOfChannel(__params[0], __channels)].set_topicInfo(__message);
                __message = ":" + __client.first + " TOPIC " + __params[0] + " " + __params[1] + "\n";
                if (send(__client.second, __message.c_str(), __message.size(), 0) == -1) throw Error("falling to send msg");
            }else{
                __error= std::string (RED) + ":  482 * You're not channel operator\n" + std::string(RESET);
                if (send(__client.second, __error.c_str(), __error.size(), 0) == -1) throw Error("falling to send msg");
                return ;
            }
        }
    }
    else{
        if (!__channels[indexOfChannel(__params[0], __channels)].get_topicInfo().empty()){
            __message =  std::string(": ") + " 332 * "+ __params[0] + " " + __channels[indexOfChannel(__params[0], __channels)].get_topicInfo() + "\n";
            if (send(__client.second, __message.c_str(), __message.size(), 0) == -1) throw Error("falling to send msg");
        }
        else{
            __message = std::string (RED) + ": " + " 331 * "+ __params[0] + " :No topic is set\n"+ std::string(RESET);
            if (send(__client.second, __message.c_str(), __message.size(), 0) == -1) throw Error("falling to send msg");
        }
        
    }
    
}


bool    Topic::checkOperator(int	__id, std::vector<Channel>	__channels, std::string	__nameChannel)
{
    bool found(false);
    int index = this->indexOfChannel(__nameChannel, __channels);
    for (size_t i = 0; i < __channels[index].get_operators().size(); i++)
    {
        if (__id ==  __channels[index].get_operators()[i].first)
            found = true;
    }
    return found;
}

int		Topic::indexOfChannel(std::string __channelName, std::vector<Channel> __channels)
{
    for (size_t i = 0; i < __channels.size(); i++)
    {
        if (__channelName == __channels[i].getchannelname())
            return i;
    }
    return -1;
}

bool	Topic::searchClient(std::string  __client, std::vector<Channel> __channels, std::string __nameChannel)
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

bool    Topic::searchChannel(std::string __nameChannel, std::vector<Channel> __channels)
{
    bool found(false);
    
    for(size_t i = 0; i < __channels.size(); i++)
    {
        if (__nameChannel == __channels[i].getchannelname())
            found = true;
    }
    return found;
}