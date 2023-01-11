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
		vector<int>		__clients;
	public:
		Channel();
		Channel(std::string channel_name);
		~Channel();
		string			getchannelname();
		void			add_client(int);
		size_t			get_clients_size();
		vector<int>		get_clients(void);
		void			remove_client(int);
};
#endif