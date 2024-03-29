#ifndef CLASS_CHANNEL_HPP
#define CLASS_CHANNEL_HPP
# include <iostream>
# include <vector>

# define GRN "\e[1;32m"
# define RESET "\e[0m"
# define RED "\e[1;31m"

class Channel 
{
	private:
		std::string									__channel_name;
		std::string									__password;
		std::vector<std::pair<int, std::string> >	__clients;
		std::vector<std::string>					__invited_clients;
		std::vector<std::pair<int, std::string> >	__operators;
		bool										invited;
		bool										__topic;
		std::string									__topic_info;

	public:
		Channel(std::string __channel_name, std::string __password, std::pair<int, std::string> __client, std::pair<int, std::string> __operator);
		Channel(std::string channel_name);
		~Channel();
		std::string									&get_password();
		void										set_password(std::string __pass);
		std::string									getchannelname();
		void										add_client(std::pair<int, std::string>);
		void										add_operator(std::pair<int, std::string>);
		size_t										get_clients_size();
		std::vector<std::pair<int, std::string> >	&get_clients(void);
		std::vector<std::pair<int, std::string> >	&get_operators(void);
		void										remove_client(int index);
		void										set_invited(bool);
		bool										get_invited();
		std::string									get_topicInfo();
		void										set_topicInfo(std::string);
		void										set_topic(bool);
		bool										get_topic();
		std::vector<std::string>					get_invited_clients();
		void										invited_client(std::string new_client);
};
#endif
