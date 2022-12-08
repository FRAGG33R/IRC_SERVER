#include "../includes/Class.channel.hpp"

Channel::Channel(){
	this->__channel_id = 1;
	this->__channel_name  = "Name";
	this->__users = vector<string>(0);
	this->__users_count  = 0;
}

Channel::Channel(const Channel &obj) : __users(obj.__users), __channel_id(obj.__channel_id),
										__users_count(obj.__users_count),
										__channel_name(obj.__channel_name)
{}

Channel::Channel(vector<string> users, int channel_id, int users_count, string channel_name){
	this->__channel_id = channel_id;
	this->__channel_name = channel_name;
	this->__users = users;
	this->__users_count  = users_count;
}
Channel::~Channel(){
}