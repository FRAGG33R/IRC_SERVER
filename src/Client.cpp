# include "../includes/main.hpp"

Client::Client(string username, string nickname, bool is_operator, bool authentication, int fd)
{
	this->__username = username;
    this->__nickname = nickname;
	this->__is_operator = is_operator;
    this->__is_authenticated = authentication;
	this->__is_registred = false;
	this->__username_filled = false;
	this->__nickname_filled = false;
	this->__fd = fd;
}

Client::Client(int fd) : __fd(fd), __is_authenticated(false), __is_registred(false)
{
	this->__username_filled = false;
	this->__nickname_filled = false;
}

int	Client::get_fd() const
{
	return this->__fd;
}

void	Client::set_fd(int fd)
{
	this->__fd = fd;
}

bool Client::is_authenticate() const
{
	return (this->__is_authenticated);
}

void	Client::set_authentication(bool authentication)
{
	this->__is_authenticated = authentication;
}

bool Client::is_registred() const
{
	return (this->__is_registred);
}

void    Client::set_is_registred(bool registred)
{
	this->__is_registred = registred;
}

bool Client::is_operator() const
{
	return (this->__is_operator);
}

void Client::set_is_operator(bool is_operator)
{
	this->__is_operator = is_operator;
}

string Client::get_username() const
{
    return (this->__username);
}

void Client::set_username(string username)
{
	this->__username = username;
}

string Client::get_nickname() const
{
	return (this->__nickname);
}

void Client::set_nickname(string nickname)
{
	this->__nickname = nickname;
	this->__nickname_filled = true;
}

Client::~Client() {}
