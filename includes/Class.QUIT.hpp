#ifndef __QUIT_HPP__
#define __QUIT_HPP__

# include "Class.channel.hpp"
# include <iostream>
# include <sstream>
# include <vector>
# include <sys/socket.h>
# include <unistd.h>

class Quit
{
	public:
		int	quit(std::vector<std::string> &__params, std::vector<Channel> &__channels, std::pair<std::string, int> __client);
};
#endif