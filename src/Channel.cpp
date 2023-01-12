# include "../includes/Class.channel.hpp"


Channel::Channel(std::string channel_name)
{
	this->__channel_name = channel_name;
}

std::string	Channel::getchannelname(){
	return __channel_name;
}

void	Channel::add_client(int __fd)
{
	this->__clients.push_back(__fd);
}

size_t	Channel::get_clients_size()
{
	return (this->__clients.size());
}


void	Channel::remove_client(int i){
	this->__clients.erase(this->__clients.begin() + i);
}

std::vector<int>	Channel::get_clients()
{
	return (this->__clients);
}

Channel::~Channel()
{

}