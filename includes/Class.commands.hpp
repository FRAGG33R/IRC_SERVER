
#ifndef CLASS_COMMANDS_HPP
#define CLASS_COMMANDS_HPP
#include "main.hpp"

class   command : public Server
{
    private:
        string  __cmd;
        string  __params;
    public:
        void    __join__();
        void    __oper__();
        void    __mode__();
        void    __quit__();
        void    __part__();
        void    __kick__();
        void    __privmsg__();
        void    __sendfile__();
        void    __whois__();
        void    __kill__();
        void    __op__();
};
#endif