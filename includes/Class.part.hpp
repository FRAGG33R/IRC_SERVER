#ifndef CLASS_PART_HPP
 #define CLASS_PART_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include "Class.channel.hpp"
# include <sys/socket.h>

class Part
{
    public:
        int	                part(std::vector<std::string> __params, int __client, std::vector<Channel> &__channels);
        bool                searchChannel(std::string __nameChannel, std::vector<Channel> __channels);
        bool                searchClient(int __clientId, std::vector<Channel> __channels, int	__channel_index);
        int                 indexOfChannel(std::string __channelName, std::vector<Channel> __channels);
        void                noticeAll(Channel __channel, std::string __client);

};

#endif