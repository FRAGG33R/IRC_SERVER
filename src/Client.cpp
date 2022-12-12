# include "../includes/main.hpp"

Client::Client(string username, string nickname, bool is_operator, bool authentication, int fd)
{
	this->__username = username;
    this->__nickname = nickname;
	this->__is_operator = is_operator;
    this->__authentication = authentication;
	this->__fd = fd;
}

bool Client::is_authenticate() const
{
	return (this->__authentication);
}

void	Client::set_authentication(bool authentication)
{
	this->__authentication = authentication;
}

Client::Client(int fd) : __fd(fd), __authentication(false)
{}

int	Client::get_fd() const
{
	return this->__fd;
}

Client::~Client(){}
