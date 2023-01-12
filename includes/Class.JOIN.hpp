#ifndef CLASS_JOIN_HPP
#define CLASS_JOIN_HPP
#include <string>
#include <vector>
#include <map>
# include "Class.channel.hpp"

class Join
{
	private:
		std::map<std::string, std::string> __channels;
		// std::vector<string> __channels;
		// std::string __keys;
	public:
		Join();
		void	set_channels_keys(std::vector<std::string> __params/* , std::vector<Channel> __channels, int __new_client, std::string __sender_nickname */);
};
#endif