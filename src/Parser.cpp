# include "../includes/main.hpp"

Parser::Parser()
{
	this->nb_command = 0;
}

void	Parser::set_command(string command)
{
	this->command = command;
}

string	Parser::get_command()
{
	return (this->command);
}

int	Parser::get_nb_command() const
{
	return (nb_command);
}

void	Parser::increment_nb_command()
{
	nb_command++;
}

void	Parser::erase_command()
{
	this->command.erase();
}

Registration Parser::get_registration() const
{
	return (this->regsitration);
}

bool	Parser::check_registration()
{
	if (!this->regsitration.get_pass())
	{
		if (this->command.find(PASS_COMMAND) == string::npos)
			return (false);
		this->command = this->command.substr(this->command.find(PASS_COMMAND) + strlen(PASS_COMMAND), string::npos);
		this->command = this->command.substr(0, this->command.find("\n"));
	}
	else if (!this->regsitration.get_nick())
	{
		if (this->command.find(NICK_COMMAND) == string::npos)
			return (false);
		this->command = this->command.substr(this->command.find(NICK_COMMAND) + strlen(NICK_COMMAND), string::npos);
		this->command = this->command.substr(0, this->command.find("\n"));
	}
	else
	{
		if (this->command.find(USER_COMMAND) == string::npos)
			return (false);
		this->command = this->command.substr(this->command.find(USER_COMMAND) + strlen(USER_COMMAND), string::npos);
		this->command = this->command.substr(0, this->command.find("\n"));
	}
	return (true);
}

bool	Parser::chack_already_registred()
{
	string copy(this->command);
	if (copy.find(PASS_COMMAND) == string::npos)
		return (true);
}

void	Parser::set_pass_registration(bool __bool)
{
	this->regsitration.set_pass(__bool);
}

void	Parser::set_nick_registration(bool __bool)
{
	this->regsitration.set_nick(__bool);
}

void	Parser::set_user_registration(bool __bool)
{
	this->regsitration.set_user(__bool);
}

void	Parser::send_error(int __err, int fd)
{	
	switch (__err)
	{
		case  ERR_NEEDMOREPARAMS : 
		{
			(send(fd, MSG_461, strlen(MSG_461), 0) == -1)?/* throw Error("failling to send msg") */0:1;
			break;
		}
		case ERR_ALREADYREGISTRED : 
		{
			(send(fd, MSG_462, strlen(MSG_462), 0) == -1)?/* throw Error("failling to send msg") */0:1;
			break;
		}
		case ERR_NONICKNAMEGIVEN :
		{
			(send(fd, MSG_431, strlen(MSG_431), 0) == -1)?/* throw Error("failling to send msg") */0:1;
			break;
		}
		case ERR_ERRONEUSNICKNAME : 
		{
			(send(fd, MSG_432, strlen(MSG_432), 0) == -1)?/* throw Error("failling to send msg") */0:1;
			break;
		}
	}
}