#ifndef CLASS_CHANNEL_HPP
#define CLASS_CHANNEL_HPP
# include <iostream>
# include <vector>

class Channel 
{
	private:
		std::string									__channel_name;
		std::string									__password;
		std::vector<std::pair<int, std::string> >	__clients;
		std::vector<std::pair<int, std::string> >	__operators;
	public:
		Channel();
		Channel(std::string channel_name);
		~Channel();
		std::string									getchannelname();
		void										add_client(std::pair<int, std::string>);
		void										add_operator(std::pair<int, std::string>);
		size_t										get_clients_size();
		std::vector<std::pair<int, std::string> >	get_clients(void);
		std::vector<std::pair<int, std::string> >	get_operators(void);
		void										remove_client(int index);
};
#endif