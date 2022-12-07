# include "includes/main.hpp"

bool is_str_digit(const string &__s) {
	return __s.find_first_not_of("0123456789") == string::npos;
}

int parse_arguments(const string &__port, const string &__password)
{
	int	__port_as_number = atoi(__port.c_str());
	if (!is_str_digit(__port) || !(__port_as_number <= 65353 && __port_as_number >= 1)|| __password.length() < 4)
		return -1;
	return (0);
}

int main(int __ac, char *__av[])
{
	int 				__socket_fd, __connection;
	vector<int>			__clients;
	struct sockaddr_in	__server_addr = {};
	char __buffer[1024] = {0};
	struct pollfd	__poll_fds[100];
	if (__ac != 3)
	{
		cerr << RED << "Bad command : usage : ./ircserv <port> <password>" << RESET << endl;
		return (1);
	}
	string __port(__av[1]), __password(__av[2]);
	if (parse_arguments(__port, __password) == -1)
	{
		cerr << RED << "Bad arguments : please enter a valid arguments" << RESET << endl;
	    return (1);
	}
	if ((__socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
		cerr << RED << "Socket error : could not creat socket" << RESET << endl;
		return (1);
	}
	__server_addr.sin_family = AF_INET;
	__server_addr.sin_port = htons(stoi(__port));
	__server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(__socket_fd, (struct sockaddr *)&__server_addr, sizeof(__server_addr)) == -1)
	{
		cerr << RED << "Bind error : failed to bind socket to port " << __port << RESET << endl;
		return (1);
	}
	if (listen(__socket_fd, 100) == -1) {
		cerr << RED << "listen error : failed to listen on socket " << __socket_fd << RESET << endl;
		return (1);
	}
	unsigned long __address_len = sizeof(__server_addr);
	__connection = accept(__socket_fd, (struct sockaddr *)&__server_addr, (socklen_t *)&__address_len);
	if (__connection == -1)
	{
		cerr << RED << "Accept error : failed to accept connection" << RESET << endl;
		for (size_t i = 0; i < __clients.size(); i++) {
			close(__clients[i]);
		}
		close(__socket_fd);
		return (1);
	}
	string __response = string(GRN) + "Connected with the irc server successfully\n" + string(RESET);
	string __confirmation  = string(GRN) + "the message was successfully sent\n" + string(RESET);
	send(__connection, __response.c_str(), __response.size(), 0);
	while (true)
	{
		recv(__connection, __buffer, sizeof(__buffer), 0);
		if (__buffer[0] == '\0') {
			std::cout << "the Client was exited successfully ! " << endl;
			break;
		}
		send(__connection , __confirmation.c_str(), __confirmation.size(), 0);
		cout << "-> Client message : " << __buffer << endl;
		memset(__buffer, 0, sizeof(__buffer));
	}
	for(size_t i  = 0; i < __clients.size(); i++) {
		close(__clients[i]);
	}
	close(__socket_fd);
	return (0);
}