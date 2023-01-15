#ifndef CLASS_JOIN_HPP
#define CLASS_JOIN_HPP
#include <string>
#include <vector>
#include <map>
# include "Class.channel.hpp"
# include <sys/socket.h>

class Join
{
	private:
		std::map<std::string, std::string> __channels;
		void	parse_join_args(std::vector<std::string> &__params);
	public:
		Join();
		int	set_channels_keys(std::vector<std::string> &__params , int __new_client, std::string __sender_nickname, std::vector<Channel> &ref_channels);
};
#endif

// 1-remove # from the channel
// 2-check the password for channel
// 3-remove desconnected client from all channels
// 4-erase the channel from the vector when the last client desconnected
