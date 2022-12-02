#include "includes/irc.hpp"

bool is_str_digit(const string &s) {
	return s.find_first_not_of("0123456789") == string::npos;
}

int parse_arguments(char *av[]) {
	string __port(av[1]);
	string __password(av[2]);
	if (!is_str_digit(__port)){
		return -1;
	}
	return (0);
}

int main(int ac, char *av[])
{
	if (ac != 3) {
		cerr << "Bad command : usage : ./ircserv <port> <password>" << endl;
		return (1);
	}
	if (parse_arguments(av) == -1){
		cerr << "Bad argument " << endl;
	}

}