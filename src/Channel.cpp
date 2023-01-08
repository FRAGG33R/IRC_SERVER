# include "../includes/Class.channel.hpp"

Channel::Channel(){
	this->__channel_id = 1;
	this->__channel_name  = "Name";
	this->__clients_size  = 0;
}

// Channel::Channel(const Channel &obj) : __clients(obj.__clients), __channel_id(obj.__channel_id),
// 										__clients_size(obj.__clients_size),
// 										__channel_name(obj.__channel_name)
// {}

// Channel::Channel(std::vector<Client> users, int channel_id, int users_count, std::string channel_name)
// {
// 	this->__channel_id = channel_id;
// 	this->__channel_name = channel_name;
// 	this->__clients = users;
// 	this->__clients_size  = users_count;
// }

Channel::~Channel()
{

}