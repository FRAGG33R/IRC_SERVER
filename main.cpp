# include "includes/irc.hpp"

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
	int 				__socket_fd, __connection;
	vector<int>			__clients;
	struct sockaddr_in	__server_addr = {};
	if (__ac != 3)
	{
		cerr << "Bad command : usage : ./ircserv <port> <password>" << endl;
		return (1);
	}
	string __port(__av[1]), __password(__av[2]);
	if (parse_arguments(__port, __password) == -1)
	{
		cerr << "Bad arguments : please enter a valid arguments" << endl;
	    return (1);
	}
	if ((__socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
		cerr << "Socket error : could not creat socket" << endl;
		return (1);
	}
	__server_addr.sin_family = AF_INET;
	__server_addr.sin_port = htons(3000);
	__server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(__socket_fd, (struct sockaddr *)&__server_addr, sizeof(__server_addr)) == -1)
	{
		cerr << "Bind error : failed to bind socket to port " << __port << endl;
		return (1);
	}
	if (listen(__socket_fd, 2) == -1) {
		cerr << "listen error : failed to listen on socket " << __socket_fd << endl;
		return (1);
	}
	unsigned long __address_len = sizeof(__server_addr);
	while (true)
	{
		__connection = accept(__socket_fd, (struct sockaddr *)&__server_addr, (socklen_t *)&__address_len);
		if (__connection == -1)
		{
			cerr << "Accept error : failed to accept connection" << endl;
			for (size_t i = 0; i < __clients.size(); i++) {
				close(__clients[i]);
			}
			close(__socket_fd);
			return (1);
		}
		__clients.push_back(__connection);
		string __response = "Connected successfully <3";
		send(__connection, __response.c_str(), __response.size(), 0);
	}
	close(__connection);
	close(__socket_fd);
	return (0);
}