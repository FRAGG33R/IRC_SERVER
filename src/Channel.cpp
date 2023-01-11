# include "../includes/Class.channel.hpp"


// Channel::Channel(const Channel &obj) : __clients(obj.__clients), __channel_id(obj.__channel_id),
// 										__clients_size(obj.__clients_size),
// 										__channel_name(obj.__channel_name)
// {}

Channel::Channel(string channel_name)
{
	this->__channel_name = channel_name;
}

string	Channel::getchannelname(){
	return __channel_name;
}

void	Channel::add_client(string nick_name)
{
	this->__clients.push_back(nick_name);
}

size_t	Channel::get_clients_size()
{
	return (this->__clients.size());
}

string	Channel::get_client(size_t i)
{
	return (this->__clients[i]);
}
void	Channel::remove_client(int i){
	this->__clients.erase(this->__clients.begin() + i);
}

Channel::~Channel()
{

}