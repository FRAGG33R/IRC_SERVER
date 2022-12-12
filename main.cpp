# include "includes/main.hpp"

int main(int __ac, char *__av[])
{
	if (__ac != 3)
		return (cerr << RED << "Bad command : usage : ./ircserv <port> <password>" << RESET << endl, 1);
	string __port(__av[1]), __password(__av[2]);
	if (parse_arguments(__port, __password) == -1)
		return (cerr << RED << "Bad arguments : please enter a valid arguments" << RESET << endl, 1);
	Server __irc(__password, stoi(__port), "FRAGGER");
	try
	{
		__irc.create_server();
		__irc.run();
	}
	catch (std::exception &e) {
		cerr << e.what() << endl;
        exit (EXIT_FAILURE);
	}
	return (0);
}
