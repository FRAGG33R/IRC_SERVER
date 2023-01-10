#ifndef CLASS_CHANNEL_HPP
#define CLASS_CHANNEL_HPP
# include "Class.client.hpp"
# include <iostream>
# include <vector>

class Channel 
{
	private:
		string			__channel_name;
		string			__password;
		vector<string>	__clients;

	public:
		Channel();
		Channel(std::string channel_name);
		string	getchannelname();
		~Channel();
		// Channel(const Channel &obj);
		void	add_client(string);
		size_t	get_clients_size();
		string	get_client(size_t i);
};
#endif