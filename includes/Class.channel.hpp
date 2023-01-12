#ifndef CLASS_CHANNEL_HPP
#define CLASS_CHANNEL_HPP
# include <iostream>
# include <vector>

class Channel 
{
	private:
		std::string			__channel_name;
		std::string			__password;
		std::vector<int>	__clients;
		std::vector<int>	__operators;

	public:
		Channel();
		Channel(std::string channel_name);
		~Channel();
		std::string			getchannelname();
		void				add_client(int);
		size_t				get_clients_size();
		std::vector<int>	get_clients(void);
		void				remove_client(int);

};
#endif
