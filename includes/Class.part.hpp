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
        Part();
        ~Part();
        void                part(std::vector<std::string> __params, int __client, std::vector<Channel> __channels, int __sender, std::string __sender_nickname);
        bool                searchChannel(std::string __nameChannel, std::vector<Channel> __channels);
        bool                searchClient(int __clientId, std::vector<Channel> __channels, std::string __nameChannel);
        int                 indexOfChannel(std::string __channelName, std::vector<Channel> __channels);
        void                noticeAll(Channel __channel);

};

#endif