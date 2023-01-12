#ifndef __PRIVMSG_HPP__
# define __PRIVMSG_HPP__

# include <iostream>
# include <vector>
# include <sstream>
# include "Class.channel.hpp"
# include <sys/socket.h>




class Privmsg
{
	private:
	    std::vector<int>	__receivers;
		std::string			__message;
		std::string			__type;
		int					__sender;
    public:
			Privmsg();
			~Privmsg();
			std::string			getMessage() const;
			std::vector<int>	getReceivers() const;
			std::string         getType() const;
			void                setReceivers(std::vector<int> &receivers);
			void                setMessage(std::string message);
			void                setType(std::string &type);
			int					parsPrivmsg(std::vector<std::string> __params, std::vector<std::pair<std::string, int> > __clients, std::vector<Channel> __channels, int __sender, std::string __sender_nickname);
};

#endif