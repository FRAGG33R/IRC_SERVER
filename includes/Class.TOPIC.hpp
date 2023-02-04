#ifndef __TOPIC_HPP__
# define __TOPIC_HPP__

# include <iostream>
# include <vector>
# include <sstream>
# include "Class.channel.hpp"
# include <sys/socket.h>

class   Topic
{
    public:
        void        topic(std::vector<std::string> __params, std::pair<std::string, int> __client, std::vector<Channel> &__channels);
        bool        searchChannel(std::string __nameChannel, std::vector<Channel> __channels);
        
};

#endif