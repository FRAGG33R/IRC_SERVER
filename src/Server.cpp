# include "../includes/main.hpp"

Server	*Server::__instance = nullptr;

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

Server *Server::getInstance(string password, int port, string name )
{
	if (__instance == nullptr)
		__instance = new Server(password, port, name);
	return __instance;
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
void Server::print(void)
{
	cout << GRN << "	███████████████████████████████████" << endl;
	cout << "	█" <<  RESET << "     Server name ➜ " << GRN<< this->__server_name << "   	  █" <<  endl;
	cout << "	█                                 █" << endl;
	cout << "	█" << RESET <<"     Server port ➜ "<< GRN << this->__port
	<< ( this->__port > 9 && this->__port < 100 ? std::setw(15)
		: this->__port >= 100 && this->__port < 1000 ? std::setw(14)
		: this->__port >= 1000 && this->__port < 10000 ? std::setw(13)
		: this->__port > 10000 ? std::setw(12)
		: std::setw(16)) << "█" << endl;
	cout << "	███████████████████████████████████" << RESET << endl;
}

int	Server::password_authentication(int __client_fd, int index)
{
	int		__bytes = 0, __recv_res = 0;
	char	__buffer[1024] = {0};
	string	__client_password;
	string	__response = string(GRN) + "Connected with the irc server successfully\n" + string(RESET);
	string	__try_password = string(RED) + "Password incorrect please try again.\n" + string(RESET);

	__recv_res = recv(__client_fd, __buffer, sizeof(__buffer), 0);
	if(__recv_res == 0)
		throw Error (" Client " + std::to_string(__client_fd) + " disconnected");
	if (__recv_res > 0)
	{
		this->__clients[index].__request = __buffer;
		if (this->__clients[index].__request[this->__clients[index].__request.size() - 1] == '\n')
		{
			if (!this->__clients[index].__interpret.empty())
			{
				this->__clients[index].__interpret += this->__clients[index].__request;
				this->__clients[index].__request = this->__clients[index].__interpret;
			}
			if (this->__clients[index].__request.substr(0, this->__clients[index].__request.size() - 1) == this->__password)
			{
				if (send(__client_fd, __response.c_str(), __response.size(), 0) == -1)
					throw Error("send error : could not send response to " + std::to_string(__client_fd));
				if (send(__client_fd, "Create an account\n", 19, 0) == -1)
					throw Error ("send error : could not send response to "+ std::to_string(__client_fd));
				this->__clients[index].set_authentication(true);
				if (send(__client_fd, "Username : ", 12, 0) == -1)
					throw Error ("send error : could not send response");
				this->__clients[index].__request.clear();
				this->__clients[index].__interpret.clear();
				return (0);
			}
			else
			{
				if (send(__client_fd, __try_password.c_str(), __try_password.size(), 0) == -1)
					throw Error("send error : could not send response to " + std::to_string(__client_fd));
				if (send(__client_fd, "password ➜ ", 12, 0) == -1)
					throw Error("send error : could not send response to " + std::to_string(__client_fd));
				memset(__buffer, 0, sizeof(__buffer));
				this->__clients[index].__request.clear();
				this->__clients[index].__interpret.clear();
			}
		}
		else
			this->__clients[index].__interpret  = this->__clients[index].__interpret + this->__clients[index].__request;
	}
	return (0);
}

void	Server::fill_username(int __client_fd, int index)
{
	int		__recv_res, __parsing_res;
	char	__buffer[1024] = {};
	string	__invalid_username_msg = string(RED) + "Invalid username\n" + string(RESET);
	string	__duplicated__username  = string(RED) + "The username already exists\n" + string(RESET);

	if (this->__clients[index].__username_filled == false)
	{
		__recv_res = recv(__client_fd, __buffer, sizeof(__buffer), 0);
		if (__recv_res == 0){
			close(this->__clients[index].get_fd());
			this->__clients.erase(this->__clients.begin() + index); 
			throw Error(" Client " + std::to_string(__client_fd) + " disconnected");
		}
		if (__recv_res > 0)
		{
			this->__clients[index].__request = __buffer;
			if (this->__clients[index].__request[this->__clients[index].__request.size() - 1] == '\n') 
			{
				if (!this->__clients[index].__interpret.empty())
				{
					this->__clients[index].__interpret += this->__clients[index].__request;
					this->__clients[index].__request = this->__clients[index].__interpret;
				}
				this->__clients[index].__request = this->__clients[index].__request.substr(0, this->__clients[index].__request.size() - 1);
				__parsing_res = this->parse_input(this->__clients[index].__request, 1);
				if (__parsing_res == 0) {
					this->__clients[index].__request.clear();
					this->__clients[index].__interpret.clear();
					if (send(__client_fd, __invalid_username_msg.c_str(), __invalid_username_msg.length(), 0) == -1)
						throw Error ("send error : could not send response");
					if (send(__client_fd, "Username : ", 12, 0) == -1)
						throw Error ("send error : could not send response");
					throw Error("Invalid username");
				}
				else if (__parsing_res == -1)
				{
					this->__clients[index].__request.clear();
					this->__clients[index].__interpret.clear();
					if (send(__client_fd, __duplicated__username.c_str(), __duplicated__username.length(), 0) == -1)
						throw Error ("send error : could not send response");
					if (send(__client_fd, "Username : ", 12, 0) == -1)
						throw Error ("send error : could not send response");
					throw Error("the username already exist");
				}
				this->__clients[index].__username_filled  = true;
				this->__clients[index].set_username(this->__clients[index].__request);
				this->__clients[index].__request.clear();
				this->__clients[index].__interpret.clear();
				if (send(__client_fd, "Nickname : ", 12, 0) == -1)
					throw Error ("send error : could not send response");
				return ;
			}
			else
			this->__clients[index].__interpret  = this->__clients[index].__interpret + this->__clients[index].__request;
		}
	}
}

void	Server::fill_nickname(int __client_fd, int index)
{
	int		__recv_res, __parsing_res;
	char	__buffer[1024] = {};
	string	__invalid_nickname = string(RED) + "Invalid nickname\n" + string(RESET);
	string	__duplicated__nickname  = string(RED) + "The nickname already exists\n" + string(RESET);

	if (this->__clients[index].__nickname_filled == false)
	{
		__recv_res = recv(__client_fd, __buffer, sizeof(__buffer), 0);
		if (__recv_res == 0){
			close(this->__clients[index].get_fd());
			this->__clients.erase(this->__clients.begin() + index); 
			throw Error(" Client " + std::to_string(__client_fd) + " disconnected");
		}
		if (__recv_res > 0)
		{
			this->__clients[index].__request = __buffer;
			if (this->__clients[index].__request[this->__clients[index].__request.size() - 1] == '\n') 
			{
				if (!this->__clients[index].__interpret.empty())
				{
					this->__clients[index].__interpret += this->__clients[index].__request;
					this->__clients[index].__request = this->__clients[index].__interpret;
				}
				this->__clients[index].__request = this->__clients[index].__request.substr(0, this->__clients[index].__request.size() - 1);
				__parsing_res = this->parse_input(this->__clients[index].__request, 2);
				if (__parsing_res == 0) {
					this->__clients[index].__request.clear();
					this->__clients[index].__interpret.clear();
					if (send(__client_fd, __invalid_nickname.c_str(), __invalid_nickname.length(), 0) == -1)
						throw Error ("send error : could not send response");
					if (send(__client_fd, "Nickname : ", 12, 0) == -1)
						throw Error ("send error : could not send response");
					throw Error("Invalid nickname");
				}
				else if (__parsing_res == -1)
				{
					this->__clients[index].__request.clear();
					this->__clients[index].__interpret.clear();
					if (send(__client_fd, __duplicated__nickname.c_str(), __duplicated__nickname.length(), 0) == -1)
						throw Error ("send error : could not send response");
					if (send(__client_fd, "Nickname : ", 12, 0) == -1)
						throw Error ("send error : could not send response");
					throw Error("the nickname already exist");
				}
				this->__clients[index].__nickname_filled  = true;
				this->__clients[index].set_nickname(this->__clients[index].__request);
				this->__clients[index].__request.clear();
				this->__clients[index].__interpret.clear();
				if (send(__client_fd, "Are you an operator ? yes/no ", 30, 0) == -1)
					throw Error ("send error : could not send response");
				return ;
			}
			else
			this->__clients[index].__interpret  = this->__clients[index].__interpret + this->__clients[index].__request;
		}
	}
}


void	Server::fill_operator(int __client_fd, int index)
{
	int		__recv_res, __parsing_res;
	char	__buffer[1024] = {};
	string	__invalid_answer = string(RED) + "Invalid answer\n" + string(RESET);

	__recv_res = recv(__client_fd, __buffer, sizeof(__buffer), 0);
	if (__recv_res == 0){
		close(this->__clients[index].get_fd());
		this->__clients.erase(this->__clients.begin() + index); 
		throw Error(" Client " + std::to_string(__client_fd) + " disconnected");
	}
	if (__recv_res > 0)
	{
		this->__clients[index].__request = __buffer;
		if (this->__clients[index].__request[this->__clients[index].__request.size() - 1] == '\n') 
		{
			if (!this->__clients[index].__interpret.empty())
			{
				this->__clients[index].__interpret += this->__clients[index].__request;
				this->__clients[index].__request = this->__clients[index].__interpret;
			}
			this->__clients[index].__request =this->__clients[index].__request.substr(0, this->__clients[index].__request.size() - 1);
			__parsing_res = this->parse_input(this->__clients[index].__request, 3);
			if (__parsing_res == -1) {
				this->__clients[index].__request.clear();
				this->__clients[index].__interpret.clear();
				if (send(__client_fd, __invalid_answer.c_str(), __invalid_answer.length(), 0) == -1)
					throw Error ("send error : could not send response");
				if (send(__client_fd, "Are you an operator ? (yes/no) ", 30, 0) == -1)
					throw Error ("send error : could not send response");
				throw Error("Invalid answer");
			}
			else if (__parsing_res == 1)
			{
				this->__clients[index].__request.clear();
				this->__clients[index].__interpret.clear();
				this->__clients[index].set_is_operator(false);
			}
			else if (__parsing_res == 0)
			{
				this->__clients[index].__request.clear();
				this->__clients[index].__interpret.clear();
				this->__clients[index].set_is_operator(true);
			}
			this->__clients[index].set_is_registred(true);
		}
		else
		this->__clients[index].__interpret  = this->__clients[index].__interpret + this->__clients[index].__request;
	}
}

void	Server::create_server(void)
{
	 int n = 1;
	if ((this->__poll_fds[0].fd = this->__socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw Error("Socket error : could not open socket");
	if (setsockopt(this->__socket_fd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n)) == -1)
		throw Error("setsockopt error : could not set SO_REUSEADDR");
	if (fcntl(this->__socket_fd, F_SETFL, O_NONBLOCK) == -1)
		throw Error("fcntl error : could not set socket in non-blocking mode");
	if (bind(this->__socket_fd, (struct sockaddr *)&this->__server_addr, sizeof(this->__server_addr)) == -1)
		throw Error("bind error : could not bind socket");
	if (listen(this->__socket_fd, MAX_FD) == -1)
		throw Error("listen error : could not listen on socket");
}

void	Server::run()
{
	int				__connection;
	int				__recv_res;
	char			__buffer[MAX_FD];
	string	__response = string(GRN) + "Connected with the irc server successfully\n" + string(RESET);
	string	__try_password = string(RED) + "Password incorrect please try again.\n" + string(RESET);
	string	__request;
	string	__interpret;

	this->print();
	while (true)
	{
		this->__poll_res = poll(this->__poll_fds, MAX_FD, 0);
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
							break ;
						}
						add_to_poll(this->__poll_fds, __connection);
						this->__clients.push_back(Client(__connection));
						if (send(__connection, "password ➜ ", 12, 0) == -1)
								throw Error("send error : could not send response to " + std::to_string(__connection));
					}
					else
					{
						if (this->__clients.size() != 0) {
							size_t j = 0;
							for (; j < this->__clients.size(); j++)
							{
								if (this->__clients[j].get_fd() == this->__poll_fds[i].fd)
									break ;
							}
							if (!this->__clients[j].is_authenticate())
							{
								try
								{
									this->password_authentication(this->__clients[j].get_fd(), j);
								}
								catch(const std::exception& e)
								{
									std::cerr << e.what() << '\n';
									remove_from_poll(__poll_fds, __poll_fds[i].fd);
									this->__clients.erase(this->__clients.begin() + j);
									close(__poll_fds[i].fd);
									close(this->__clients[j].get_fd());
									break ;
								}
							}
							if (!this->__clients[j].is_registred())
							{
								try
								{
									this->fill_username(this->__clients[j].get_fd(), j);
									this->fill_nickname(this->__clients[j].get_fd(), j);
									this->fill_operator(this->__clients[j].get_fd(), j);
								}
								catch(const std::exception& e)
								{
									std::cerr << e.what() << '\n';
								}
							}
							else
							{
								__recv_res = recv(this->__clients[j].get_fd(), __buffer, sizeof(__buffer), 0);
								if (__recv_res == 0)
								{
									cerr << RED << "The client " << this->__clients[j].get_fd() <<  " disconnected !" << RESET << endl;
									close(this->__clients[j].get_fd());
									remove_from_poll(__poll_fds, this->__clients[j].get_fd());
									this->__clients.erase(this->__clients.begin() + j);
									break ;
								}
								static string __fullCmdl;

								__fullCmdl += string(__buffer);
								if (__fullCmdl.find('\n') != std::string::npos)
								{
									cout << "<<" << __fullCmdl << ">>\n";
									__fullCmdl.erase();
								}
								else
									cout << "not complete\n";
								// cout << GRN << "➜ " << RESET << __buffer << endl;
								memset(__buffer, 0, sizeof(__buffer));
							}
						}
					}
				}
			}
		}
	}
}
