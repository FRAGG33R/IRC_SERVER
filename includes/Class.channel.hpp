#ifndef CLASS_CHANNEL_HPP
#define CLASS_CHANNEL_HPP
# include "Class.client.hpp"
// # include "Class.server.hpp"
# include <iostream>
# include <vector>
class Client;
class Channel 
{
	protected:
		std::vector<Client>	__clients;
		int				__channel_id;
		int				__clients_size;
		std::string		__channel_name;

	public:
		Channel();
		Channel(std::vector<Client> users, int channel_id, int users_count, std::string channel_name);
		// Channel(const Channel &obj);
		std::string	setchannel();
		~Channel();
};
#endif