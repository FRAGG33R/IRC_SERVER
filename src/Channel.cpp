# include "../includes/Class.channel.hpp"

Channel::Channel(std::string channel_name)
{
	this->__channel_name = channel_name;
	this->invited = false;
	this->__topic = false;
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

std::vector<std::pair<int, std::string> >	&Channel::get_clients()
{
	return (this->__clients);
}

std::vector<std::pair<int, std::string> >	&Channel::get_operators()
{
	return (this->__operators);
}

std::string	&Channel::get_password()
{
	return (this->__password);
}

void	Channel::set_password(std::string __pass)
{
	this->__password = __pass;
}

bool	Channel::get_invited()
{
	return (this->invited);
}

void	Channel::set_invited(bool __is_invated)
{
	this->invited = __is_invated;
}

bool	Channel::get_topic()
{
	return (this->__topic);
}

void	Channel::set_topic(bool __is_topic)
{
	this->__topic = __is_topic;
}

void	Channel::set_topicInfo(std::string __info)
{
	this->__topic_info =  __info;
}

std::string	Channel::get_topicInfo(){
	return (this->__topic_info);
}

std::vector<std::string>	Channel::get_invited_clients()
{
	return (this->__invited_clients);
}

void	Channel::invited_client(std::string new_client)
{
	this->__invited_clients.push_back(new_client);
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
	this->invited = false;
}
