#include "includes/irc.hpp"

bool is_str_digit(const string &__s) {
	return __s.find_first_not_of("0123456789") == string::npos;
}

int parse_arguments(const string &__port, const string &__password)
{
	if (!is_str_digit(__port) || __password.length() < 4)
		return -1;
	return (0);
}

int main(int __ac, char *__av[])
{
	int 				__socket_fd;
	struct sockaddr_in	__server_add = {};
	if (__ac != 3) {
		cerr << "Bad command : usage : ./ircserv <port> <password>" << endl;
		return (1);
	}
	string __port(__av[1]), __password(__av[2]);
	if (parse_arguments(__port, __password) == -1){
		cerr << "Bad arguments : please enter a valid arguments" << endl;
	    return (1);
	}
	if ((__socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
		cerr << "Socket error : could not creat socket" << endl;
		return (1);
	}
	__server_add.sin_family = AF_INET;
	__server_add.sin_port = htons(stoi(__port));
	cout  << "- Socekt file descriptor :  " << __socket_fd << endl;
	return (0);
}