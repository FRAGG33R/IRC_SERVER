# include "../includes/main.hpp"

Server::Server()
{
	this->__socket_fd = -1;
	this->__poll_res = 0;
	this->__server_addr.sin_family = AF_INET;
	this->__server_addr.sin_addr.s_addr = INADDR_ANY;
	this->__server_addr.sin_port = htons(this->__port);
	for (int i = 0; i < MAX_FD; i++) {
		__poll_fds[i].fd = -1;
		__poll_fds[i].events = 0;
		__poll_fds[i].events |= POLLIN;
	}
	this->__address_len = sizeof(this->__server_addr);
	this->__port = 3000;
	this->__server_name = "CW9";
}

Server::Server(string password, int port, string name = "CW9")
{
	this->__socket_fd = -1;
	this->__poll_res = 0;
	this->__server_addr.sin_family = AF_INET;
	this->__server_addr.sin_addr.s_addr = INADDR_ANY;
	this->__server_addr.sin_port = htons(port);
	for (int i = 0; i < MAX_FD; i++) {
		__poll_fds[i].fd = -1;
		__poll_fds[i].events = 0;
		__poll_fds[i].events |= POLLIN;
	}
	this->__address_len = sizeof(this->__server_addr);
	this->__password = password;
	this->__port = port;
	this->__server_name = name;
}

void	Server::add_to_poll(struct pollfd *__poll_fds, int __fd)
{
	int i = 0;
	while (i < MAX_FD)
	{
		if (__poll_fds[i].fd == -1)
		{
			__poll_fds[i].fd =  __fd;
			fcntl(__poll_fds[i].fd, F_SETFL, O_NONBLOCK);
			return ;
		}
		i++;
	}
}

void	Server::remove_from_poll(struct pollfd *__poll_fds, int __fd) {
	int i = 0;
	while  (i < MAX_FD)
	{
		if (__poll_fds[i].fd == __fd)
		{
			__poll_fds[i].fd = -1;
			return ;
		}
		i++;
	}
}

void	Server::full_close(struct pollfd *__poll_fd)
{
	for(int i = 0; i < MAX_FD; i++)
		if (__poll_fd[i].fd != -1)
			close(__poll_fd[i].fd);
}

int	Server::password_autontification(string __server_password, int __client_fd, struct pollfd *__poll_fds)
{
	int		__bytes = 0;
	char	__buffer[1024] = {0};
	string	__client_password;
	string	__response = string(GRN) + "Connected with the irc server successfully\n" + string(RESET);
	string	__try_password = string(RED) + "Password incorrect please try again.\n" + string(RESET);
	string	__request;
	string	__interpret;
	int i = 0;
	while (i < MAX_FD)
    {
		 if (__poll_fds[i].fd == __client_fd)
		 	break ;
		i++;
	}
	if (send(__poll_fds[i].fd, "password ➜ ", 12, 0) == -1)
	{
		cerr << RED <<  "send error : failed to send response  to " << __client_fd << RESET << endl;
		return (-1);
	}
	while (true)
	{
		__bytes = recv(__poll_fds[i].fd, __buffer, sizeof(__buffer), 0);
		if (__bytes == 0)
			return (1);
		if (__bytes > 0)
		{
			__request = __buffer;
			if (__request[__request.size() - 1] == '\n') {
				if (!__interpret.empty())
				{
					__interpret += __request;
					__request = __interpret;
				}
				if (__request.substr(0, __request.size() - 1) == __server_password)
				{
					if (send(__poll_fds[i].fd, __response.c_str(), __response.size(), 0) == -1)
					{
						cerr << RED <<  "send error : failed to send response  to " << __client_fd << RESET << endl;
						return (-1);
					}
					return (1);
				}
				else {
					if (send(__poll_fds[i].fd, __try_password.c_str(), __try_password.size(), 0) == -1)
					{
						cerr << RED <<  "send error : failed to send response  to " << __client_fd << RESET << endl;
						return (-1);
					}
					if (send(__poll_fds[i].fd, "password ➜ ", 12, 0) == -1)
					{
						cerr << RED <<  "send error : failed to send response  to " << __client_fd << RESET << endl;
						return (-1);
					}
					memset(__buffer, 0, sizeof(__buffer));
					continue ;
				}
			}
			else {
				__interpret  = __interpret + __request;
				memset(__buffer, 0, sizeof(__buffer));
			}
		}
	}
	return (1);
}

void	Server::start_server()
{
	int		__connection;
	int		__recv_res;
	char	__buffer[MAX_FD];
	//CREATE SERVER FUNCTION
	if ((this->__poll_fds[0].fd = this->__socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw Error("Socket error : could not open socket");
	if (fcntl(this->__socket_fd, F_SETFL, O_NONBLOCK) == -1)
		throw Error("fcntl error : could not set socket in non-blocking mode");
	if (bind(this->__socket_fd, (struct sockaddr *)&this->__server_addr, sizeof(this->__server_addr)) == -1)
		throw Error("bind error : could not bind socket");
	if (listen(this->__socket_fd, MAX_FD) == -1)
		throw Error("listen error : could not listen on socket");

	cout << "Socket descriptor : " << __socket_fd << endl;
	cout << "The password is : " << this->__password << endl;
	cout << "THe server name : " << this->__server_name << endl;
	cout << "The port : " << this->__port << endl;
	cout << "socket descriptor in poll array : " << this->__poll_fds[0].fd << endl;
	cout << "the socket event : " << this->__poll_fds[0].events << endl;
	while (true)
	{
		// cout << "loading.." << endl;
		this->__poll_res = poll(this->__poll_fds, MAX_FD, 0);
		// cout << __poll_res << endl;
		if (__poll_res == -1)
			throw Error("poll error : failed to poll on socket " + std::to_string(this->__socket_fd));
		else if (this->__poll_res > 0)
		{
			for (int i = 0; i < MAX_FD; i++)
			{
				if (this->__poll_fds[i].revents & POLLIN)
				{
					if (this->__poll_fds[i].fd == this->__socket_fd)
					{
						cout << GRN << "New request from " << this->__poll_fds[i].fd << RESET << endl;
						__connection = accept(this->__socket_fd, (struct sockaddr *)&this->__server_addr, (socklen_t *)&this->__address_len);
						if (__connection == -1)
                        {
							cerr << RED << "accept error : could not accept clinet at socket " << this->__socket_fd <<  RESET << endl;
							break;
						}
						add_to_poll(this->__poll_fds, __connection);
						if (password_autontification(this->__password, __connection, __poll_fds) == -1)
							throw Error("send error : could not send response to " + std::to_string(__connection));
					}
					else
					{
						__recv_res = recv(__poll_fds[i].fd, __buffer, sizeof(__buffer), 0);
						if (__recv_res == -1)
						{
							cerr << RED << "recv error : failed to receiven request from client " << RESET << endl;
							break;
						}
						if (__recv_res == 0) 
						{
							cerr << RED << "The client " << __poll_fds[i].fd <<  " disconnected !" << RESET << endl;
							close(__poll_fds[i].fd);
							remove_from_poll(__poll_fds, __poll_fds[i].fd);
							break ;
						}
						cout << GRN << "➜ " << RESET << __buffer << endl;
						memset(__buffer, 0, sizeof(__buffer));
					}
				}
			}
		}
	}
}