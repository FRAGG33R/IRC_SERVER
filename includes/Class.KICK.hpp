#ifndef CLASS_KICK_HPP
 #define CLASS_KICK_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include "Class.channel.hpp"
# include <sys/socket.h>


class   Kick
{
    public:
        void                kick(std::vector<std::string> __params, int __client, std::vector<Channel> &__channels);
        bool                searchChannel(std::string __nameChannel, std::vector<Channel> __channels);
        bool                searchClient(int __clientId, std::vector<Channel> __channels, std::string __nameChannel);
        bool                searchClient(std::string  __client, std::vector<Channel> __channels, std::string __nameChannel);
        int                 indexOfChannel(std::string __channelName, std::vector<Channel> __channels);
        int                 indexOfClient(std::string __client, std::vector<Channel> __channels, std::string __nameChannel);
        bool                checkOperator(int   __id, std::vector<Channel> __channels, std::string __nameChannel);
        void                noticeAll(Channel __channel, int __client, bool __reason, std::string __reasonMsg);
};

#endif