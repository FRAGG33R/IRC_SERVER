#include "../includes/main.hpp"

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
	string str[15] = {"PASS", "NICK", "USER", "OPER", "MODE", "QUIT", "JOIN", "PART", "TOPIC", "KICK", "PRIVMSG", "NOTICE", "SENDFILE", "GETFILE", "DEEZNUTS"};
	for (int i = 0; i < 15; i++){
		if (str[i] == __request)
            return 1;
	}
	return (0);
}

int Server::parse_input(string __input, int flag)
{
	if (flag == 1)
	{
		if (__input.length() < 4 || std::isdigit(__input[0]))
			return  0;
		for (unsigned int  i = 0; i < this->__clients.size(); i++)
			if (this->__clients[i].get_username() == __input)
				return (-1); //username already exist
		return (1);
	}
	if (flag == 2)
	{
		if (__input.length() < 4 || std::isdigit(__input[0]))
			return  0;
		for (unsigned int  i = 0; i < this->__clients.size(); i++)
			if (this->__clients[i].get_nickname() == __input)
				return (-1); //username already exist
		return (1);
	}
	if (flag == 3)
    {
		if (__input == "YES" || __input == "yes")
			return (0);
		else if (__input == "NO" || __input == "no")
		    return (1);
		else
			return (-1);
	}
	return (0);
}
