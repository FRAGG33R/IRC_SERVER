#include "../includes/Class.TOPIC.hpp"


void    Topic::topic(std::vector<std::string> __params, std::pair<std::string, int> __client, std::vector<Channel> &__channels){
    __params[0].erase(__params[0].find_last_not_of(" ") + 1);
    std::string             __message;
    std::string             __tmp;
    (void) __client;
    (void) __channels;


    if (!__params[1].empty())
        __message = __params[1];
    
    
}