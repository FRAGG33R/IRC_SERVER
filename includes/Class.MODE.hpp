#ifndef __MODE_HPP__
# define __MODE_HPP__

# include <iostream>
# include <vector>
# include <sstream>
# include "Class.channel.hpp"
# include <sys/socket.h>

class Mode 
{
	private:
	    char		__type;
		std::string	__channel_name;
	public:
	Mode();
	~Mode();
	void 			setType(char type);
	char 			getType();
    void 			setChannelName(std::string channel_name);
	std::string		getChannelName();
	int				parseMode(std::vector<std::string> __params, std::vector<Channel> &__channels, int __sender, std::string __sender_name);
};

#endif