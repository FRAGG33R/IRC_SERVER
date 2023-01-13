# include "../includes/Class.channel.hpp"


Channel::Channel(std::string channel_name)
{
	this->__channel_name = channel_name;
}

std::string	Channel::getchannelname(){
	return __channel_name;
}

void	Channel::add_client(std::pair<int, std::string> __client)
{
	this->__clients.push_back(__client);
}

void	Channel::add_operator(std::pair<int, std::string> __operator)
{
	this->__operators.push_back(__operator);
}

size_t	Channel::get_clients_size()
{
	return (this->__clients.size());
}

void	Channel::remove_client(int i)
{
	this->__clients.erase(this->__clients.begin() + i);
}

std::vector<std::pair<int, std::string> >	Channel::get_clients()
{
	return (this->__clients);
}

std::vector<std::pair<int, std::string> >	Channel::get_operators()
{
	return (this->__operators);
}

std::string	Channel::get_password()
{
	return (this->__password);
}

Channel::~Channel()
{

}
Channel::Channel(std::string __channel_name, std::string __password, std::pair<int, std::string> __client, std::pair<int, std::string> __operator)
{
	this->__channel_name = __channel_name;
	this->__password = __password;
	this->__clients.push_back(__client);
	this->__operators.push_back(__operator);
}