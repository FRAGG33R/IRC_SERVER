# include "../includes/main.hpp"

Parser::Parser()
{

}

void	Parser::set_command(string command)
{
	this->command = command;
}

string	Parser::get_command()
{
	return (this->command);
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
	int pos;
	if (!this->regsitration.get_pass())
	{
		if (this->command.find(PASS_COMMAND) == string::npos)
			return (false);
		else
		{
			pos = this->command.find(PASS_COMMAND) + strlen(PASS_COMMAND);
			while (this->command[pos] == ' ')
				pos++;
			this->command = this->command.substr(pos, string::npos);
		}
		if (this->command == "\n")
			return (false);
		this->command = this->command.substr(0, this->command.find("\n"));
	}
	else if (!this->regsitration.get_nick())
	{
		if (this->command.find(NICK_COMMAND) == string::npos)
			return (false);
		else
		{
			pos = this->command.find(NICK_COMMAND) + strlen(NICK_COMMAND);
			while (this->command[pos] == ' ')
				pos++;
			this->command = this->command.substr(pos, string::npos);
		}
		if (this->command == "\n")
			return (false);
		this->command = this->command.substr(0, this->command.find("\n"));
	}
	else
	{
		if (this->command.find(USER_COMMAND) == string::npos)
			return (false);
		else
		{
			pos = this->command.find(USER_COMMAND) + strlen(USER_COMMAND);
			while (this->command[pos] == ' ')
				pos++;
			this->command = this->command.substr(pos, string::npos);
		}
		if (this->command == "\n")
			return (false);
		pos = 0;
		while (this->command[pos] != ' ' && this->command[pos] != '\n')
			pos++;
		this->command = this->command.substr(0, pos);
	}
	return (true);
}

bool	Parser::chack_already_registred()
{
	string copy(this->command);
	if (copy.find(PASS_COMMAND) != string::npos)
		return (true);
	return (false);
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

void	Parser::send_msg(int __err, int fd)
{	
	switch (__err)
	{
		case  ERR_NEEDMOREPARAMS : 
		{
			(send(fd, MSG_461, strlen(MSG_461), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_ALREADYREGISTRED : 
		{
			(send(fd, MSG_462, strlen(MSG_462), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_NONICKNAMEGIVEN :
		{
			(send(fd, MSG_431, strlen(MSG_431), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_ERRONEUSNICKNAME : 
		{
			(send(fd, MSG_432, strlen(MSG_432), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_NICKNAMEINUSE : 
		{
			(send(fd, MSG_433, strlen(MSG_433), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_WRONGPASSWORD : 
		{
			(send(fd, MSG_666, strlen(MSG_666), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_UNKNOWNCOMMAND : 
		{
			(send(fd, MSG_421, strlen(MSG_421), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_REGIST_ORDER : 
		{
			(send(fd, MSG_667, strlen(MSG_667), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case ERR_ERRONEUSUSERNAME : 
		{
			(send(fd, MSG_668, strlen(MSG_668), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
		case RPL_WELCOME : 
		{
			(send(fd, MSG_WELCOME, strlen(MSG_WELCOME), 0) == -1)?throw Error("failling to send msg"):1;
			break;
		}
	}
}

bool	Parser::check_command()
{
	string __command = this->command;
	if (__command.find(" ") != string::npos)
		__command = __command.substr(0, __command.find(" "));
	else
		__command = __command.substr(0, __command.find("\n"));
	if (!is_command(__command))
		return (false);
	return (true);
}

#define PRIVMSG "PRIVMSG"
// void	Parser::put_cmd_params()
// {
// 	size_t	__first_space;
// 	string	__backup;

// 	__backup = this->command;
// 	__first_space = this->command.find_first_not_of(" ");
// 	if (__first_space != 0)
// 		this->command = this->command.substr(__first_space, string::npos);
// 	if (this->command == PRIVMSG)

// 	if (this->command.find(" ") != string::npos)
// 	{
// 		this->command = this->command.substr(0, this->command.find(" "));
// 		__backup = this->command.substr(0, this->command.find(" "));
// 		while (!__backup.empty())
// 		{
// 			this->params.push_back(0, 1);
// 		}
// 	}
// }

Parser::~Parser()
{

}
