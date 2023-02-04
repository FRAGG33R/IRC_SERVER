#include "../includes/main.hpp"
#include "../includes/Class.server.hpp"
bool is_str_digit(const string &__s) 
{
	return __s.find_first_not_of("0123456789") == string::npos;
}

int parse_arguments(const string &__port, const string &__password)
{
	int	__port_as_number = atoi(__port.c_str());
	if (!is_str_digit(__port) || !(__port_as_number <= MAX_PORT && __port_as_number >= 1)|| __password.length() < 4)
		return -1;
	return (0);
}

int	is_command(string __request)
{
	string __commands[15] = {"PASS", "NICK", "USER", "OPER", "MODE", "QUIT", "JOIN", "PART", "KICK", "PRIVMSG", "SENDFILE", "WHOIS", "KILL", "OP", \
							"pass", "nick", "user", "oper", "mode", "quit", "join", "part", "kick", "privmsg", "sendfile", "whois", "kill", "op"};
	for (int i = 0; i < 15; i++)
	{
		if (__commands[i] == __request)
			return 1;
	}
	return (0);
}

int Server::parse_input(string __input, int flag)
{
	if (flag == 1)
	{
		if (__input.length() < 5 || std::isdigit(__input[0]))
			return  0;
		return (1);
	}
	if (flag == 2)
	{
		if ((__input.length() < 5  || __input.length() > 15 ) || std::isdigit(__input[0]))
			return  0;
		for (unsigned int  i = 0; i < this->__clients.size(); i++)
			if (this->__clients[i].get_nickname() == __input)
				return (-1); //username already exist
		return (1);
	}
	return (0);
}
