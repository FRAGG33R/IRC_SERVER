# include "../includes/main.hpp"
# include "../includes/Class.server.hpp"
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
						Server::sent_from_registration(__connection);
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
							__recv_res = recv(this->__clients[j].get_fd(), __buffer, sizeof(__buffer), 0);
							if (__recv_res == 0)
							{
								cerr << RED << "The client " << this->__clients[j].get_fd() <<  " disconnected !" << RESET << endl;
								close(this->__clients[j].get_fd());
								remove_from_poll(__poll_fds, this->__clients[j].get_fd());
								this->__clients.erase(this->__clients.begin() + j);
								break ;
							}
							string	backup;
							size_t	first_space;

							this->__clients[j].regiteration.set_command(this->__clients[j].regiteration.get_command() + string(__buffer));
							if (this->__clients[j].regiteration.get_command().find_last_of("\n") != std::string::npos || this->__clients[j].regiteration.get_command().find_last_of("\r"))
							{
								if (!this->__clients[j].is_registred())
								{
									backup = this->__clients[j].regiteration.get_command();
									while (backup.find("\r") != string::npos)
									{
										size_t j = backup.find("\r");
										backup.erase(j, 1);
									}
									while (!backup.empty())
									{
										this->__clients[j].regiteration.set_command(backup.substr(0, backup.find("\n") + 1));
										this->connect_client(j);
										backup = backup.substr(backup.find("\n") + 1, string::npos);
									}
								}
								this->__clients[j].regiteration.erase_command();
							}
							memset(__buffer, 0, sizeof(__buffer));
						}
					}
				}
			}
		}
	}
}



bool	check_command(string command)
{
	if (command.find(" ") != string::npos)
		command = command.substr(0, command.find(" "));
	else
		command = command.substr(0, command.find("\n"));
	if (!is_command(command))
		return (false);
	return (true);
}

bool	check_order(string command, int order)
{
	if (order == 1)
		if (command.find(PASS_COMMAND) == string::npos)
			return (0);
	if (order == 2)
		if (command.find(NICK_COMMAND) == string::npos)
			return (0);
	if (order == 3)
		if (command.find(USER_COMMAND) == string::npos)
			return (0);
	return (1);
}

void	Server::connect_client(int nb_client)
{
	try
	{
		if (!check_command(this->__clients[nb_client].regiteration.get_command()))
			this->__clients[nb_client].regiteration.send_msg(ERR_UNKNOWNCOMMAND, this->__clients[nb_client].get_fd());
		else if (!this->__clients[nb_client].regiteration.get_registration().get_pass())
		{
			if (!check_order(this->__clients[nb_client].regiteration.get_command(), 1))
				this->__clients[nb_client].regiteration.send_msg(ERR_REGIST_ORDER, this->__clients[nb_client].get_fd());
			else if (!this->__clients[nb_client].regiteration.check_registration())
				this->__clients[nb_client].regiteration.send_msg(ERR_NEEDMOREPARAMS, this->__clients[nb_client].get_fd());
			else if (this->__clients[nb_client].regiteration.get_command() != this->__password)
				this->__clients[nb_client].regiteration.send_msg(ERR_WRONGPASSWORD, this->__clients[nb_client].get_fd());
			else 
				this->__clients[nb_client].regiteration.set_pass_registration(true);
		}
		else if (this->__clients[nb_client].regiteration.get_registration().get_pass() && !this->__clients[nb_client].regiteration.get_registration().get_nick())
		{
			if (!check_order(this->__clients[nb_client].regiteration.get_command(), 2))
				this->__clients[nb_client].regiteration.send_msg(ERR_REGIST_ORDER, this->__clients[nb_client].get_fd());
			else if (this->__clients[nb_client].regiteration.chack_already_registred())
				this->__clients[nb_client].regiteration.send_msg(ERR_ALREADYREGISTRED, this->__clients[nb_client].get_fd());
			else if (!this->__clients[nb_client].regiteration.check_registration())
				this->__clients[nb_client].regiteration.send_msg(ERR_NONICKNAMEGIVEN, this->__clients[nb_client].get_fd());
			else if (this->parse_input(this->__clients[nb_client].regiteration.get_command(), 2) == 0)
				this->__clients[nb_client].regiteration.send_msg(ERR_ERRONEUSNICKNAME, this->__clients[nb_client].get_fd());
			else if (this->parse_input(this->__clients[nb_client].regiteration.get_command(), 2) == -1)
				this->__clients[nb_client].regiteration.send_msg(ERR_NICKNAMEINUSE, this->__clients[nb_client].get_fd());
			else
			{
				this->__clients[nb_client].set_nickname(this->__clients[nb_client].regiteration.get_command());
				this->__clients[nb_client].regiteration.set_nick_registration(true);
			}
		}
		else if (this->__clients[nb_client].regiteration.get_registration().get_nick() && !this->__clients[nb_client].regiteration.get_registration().get_user())
		{
			if (!check_order(this->__clients[nb_client].regiteration.get_command(), 3))
				this->__clients[nb_client].regiteration.send_msg(ERR_REGIST_ORDER, this->__clients[nb_client].get_fd());
			else if (!this->__clients[nb_client].regiteration.check_registration())
				this->__clients[nb_client].regiteration.send_msg(ERR_NEEDMOREPARAMS, this->__clients[nb_client].get_fd());
			else if (this->__clients[nb_client].regiteration.chack_already_registred() || (this->parse_input(this->__clients[nb_client].regiteration.get_command(), 1) == -1))
				this->__clients[nb_client].regiteration.send_msg(ERR_ALREADYREGISTRED, this->__clients[nb_client].get_fd());
			else if (this->parse_input(this->__clients[nb_client].regiteration.get_command(), 1) == 0)
				this->__clients[nb_client].regiteration.send_msg(ERR_ERRONEUSUSERNAME, this->__clients[nb_client].get_fd());
			else
			{
				this->__clients[nb_client].set_username(this->__clients[nb_client].regiteration.get_command());
				this->__clients[nb_client].regiteration.set_user_registration(true);
				// this->__clients[nb_client].regiteration.send_msg(RPL_WELCOME, this->__clients[nb_client].get_fd());
				this->__clients[nb_client].set_is_registred(true);
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		close (this->__clients[nb_client].get_fd());
		std::cout << "Disconnet Client " << this->__clients[nb_client].get_fd() << std::endl;
		this->__clients.erase(this->__clients.begin() + nb_client);
	}
}

void	Server::sent_from_registration(int nb_client)
{
	(void)nb_client;
	// string str =  string(GRN) + string("█████████████████████████████████████████████\n");
	// send(nb_client, str.c_str(), str.length(), 0);
	// send(nb_client, std::setw(43), 43, 0);
	// string str =  string(GRN) + string("█\n") + string(std::setw(43)) + ;
}
