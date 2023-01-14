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

vector<Channel>	&Server::get_ref_channels(void)
{
	return (this->__channels);
}

vector<std::pair<string, int> >	Server::get_clients(void)
{
	vector<std::pair<string, int> >    __returned_clients;
	for (size_t i = 0; i < this->__clients.size(); i++)
		__returned_clients.push_back(std::pair<string, int>(this->__clients[i].get_nickname(), this->__clients[i].get_fd()));
	return (__returned_clients);
}

vector<Channel>    Server::get_channels(void)
{
	return(this->__channels);
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

							this->__clients[j].__command.set_command(this->__clients[j].__command.get_command() + string(__buffer));
							if (this->__clients[j].__command.get_command().find_last_of("\n") != std::string::npos || this->__clients[j].__command.get_command().find_last_of("\r"))
							{
								if (!this->__clients[j].is_registred())
								{
									backup = this->__clients[j].__command.get_command();
									while (backup.find("\r") != string::npos)
									{
										size_t j = backup.find("\r");
										backup.erase(j, 1);
									}
									while (!backup.empty())
									{
										this->__clients[j].__command.set_command(backup.substr(0, backup.find("\n") + 1));
										this->connect_client(j);
										backup = backup.substr(backup.find("\n") + 1, string::npos);
									}
								}
								else
								{
									this->__clients[j].__command.set_command(this->__clients[j].__command.get_command().substr(0, this->__clients[j].__command.get_command().size() - 1));
									std::vector<std::string>	substrings;
									std::string 				temp;
									int							index;
									int						sep_index = 0;

									backup = this->__clients[j].__command.get_command();
									if (backup.find(" ") != string::npos)
									{
										this->__clients[j].__command.set_command(backup.substr(0, backup.find(" ")));
										backup = backup.substr(backup.find(" ") + 1, string::npos);
										for (index = 0;backup[index] == ' '; index++);
										backup = backup.substr(index, string::npos);
										index = backup.size() - 1;
										while (index >= 0)
										{
											if (backup[index] == ':')
												sep_index = index;
											index--;
										}
										if (sep_index > 0)
										{
											temp = backup.substr(sep_index, string::npos);
											backup = backup.substr(0, sep_index);
										}
										if (!backup.empty())
											substrings.push_back(backup);
										if (!temp.empty())
											substrings.push_back(temp);
									}
									else
										this->__clients[j].__command.set_command(backup);
									if (substrings.size() != 0)
									{
										temp = "";
										size_t k;
										size_t t;
										while (substrings[0].find(",") != string::npos)
										{
											t = 0;
											k = substrings[0].find(",");
											while (k >= 0 && substrings[j][--k] == ' ') ;
											while (substrings[0][t] == ' ')
												t++;
											if (temp == "")
												temp = substrings[0].substr(t, ++k - t);
											else
												temp += substrings[0].substr(t, ++k - t);
											temp += ",";
											substrings[0] = substrings[0].substr(substrings[0].find(",") + 1, string::npos);
										}
										t = 0;
										k = substrings[0].size();
										while (substrings[j][t] == ' ')
											t++;
										while (k >= 0 && substrings[j][--k] == ' ') ;
										if (substrings[j][k + 1] != ' ')
											k++;
										substrings[0] = substrings[0].substr(t, k - t + 1);
										if (temp != "")
											substrings[0] = temp + substrings[0];
										this->__clients[j].__command.set_params(substrings);
									}
									// Channel c1("Channel1");
									// c1.add_client(std::pair<int, std::string> (4, "mohamed"));
									// c1.add_client(std::pair<int, std::string> (5, "oussama"));
									// std::vector<Channel> __Channel_list;
									// __Channel_list.push_back(c1);
									if (this->__clients[j].__command.get_command()  == "PRIVMSG" || this->__clients[j].__command.get_command()  == "NOTICE")
									{
										// try
										// {
										// 	if (this->__clients[j].__command.get_params().size() != 2)
										// 		this->__clients[j].__command.send_error(461, this->__clients[j].get_fd());
										// 	else
										// 	{
										// 		int res  = this->__clients[j].__privmsg.parsPrivmsg(this->__clients[j].__command.get_params(), this->get_clients(), __Channel_list, this->__clients[j].get_fd(), this->__clients[j].get_nickname());
										// 		if ( res == -1)
										// 			throw Error("Failed to send message to client");
										// 		else
										// 			this->__clients[j].__command.send_error(res, this->__clients[j].get_fd());
										// 	}
										// }
										// catch(const std::exception& e)
										// {
										// 	std::cerr << e.what() << '\n';
										// 	close (this->__clients[j].get_fd());
										// 	std::cout << "Disconnet Client " << this->__clients[j].get_fd() << std::endl;
										// 	this->__clients.erase(this->__clients.begin() + j);
										// }
									}
									else if (this->__clients[j].__command.get_command()  == "JOIN")
									{
										this->__clients[j].__join.set_channels_keys(this->__clients[j].__command.get_params(), this->__clients[j].get_fd(), this->__clients[j].get_nickname(), this->get_ref_channels());
										cout << "list of channels : \n";
										for (size_t ii = 0; ii < this->__channels.size(); ii++)
										{
											cout << "shannel name : ||" << this->__channels[ii].getchannelname() << "||\n";
											cout << "shannel password : ||" << this->__channels[ii].get_password() << "||\n";
											cout << "existing clients : \n";
											for (size_t jj = 0; jj < this->__channels[ii].get_clients().size(); jj++)
											{
												cout << "|" << this->__channels[ii].get_clients()[jj].second << "| ";
											}
											cout << "\nthe operator is : " << this->__channels[ii].get_operators()[0].second << "\n";
										}
									}
									else if  (this->__clients[j].__command.get_command()  == "PART")
									{
										// this->__clients[j].__part.part(this->__clients[j].__command.get_params(), this->__clients[j].get_fd(), __Channel_list);
									}
									else if (this->__clients[j].__command.get_command() == "MODE")
									{
										// if (this->__clients[j].__command.get_params().size() == 0)
										// 	this->__clients[j].__command.send_error(461, this->__clients[j].get_fd());
										// else
										// 	if (this->__clients[j].__mode.parseMode(this->__clients[j].__command.get_params(),  __Channel_list, this->__clients[j].get_fd(), this->__clients[j].get_nickname()) == -1)
										// 		throw Error("Failed to send message to client");
									}
								}
							}
								this->__clients[j].__command.erase_command();
							memset(__buffer, 0, sizeof(__buffer));
						}
					}
				}
			}
		}
	}
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
};

bool	check_user_params(string command)
{
	int	__nb_params;

	__nb_params = 0;
	while (!command.empty())
	{
		__nb_params++;
		if (command.find(" ") != string::npos)
		{
			command = command.substr(command.find(" ") + 1, string::npos);
			int i = 0;
			for (; command[i] && command[i] == ' '; i++);
			command = command.substr(i, string::npos);
		}
		else
			command.erase();
	}
	return (__nb_params >= 5);
}

void	Server::connect_client(int nb_client)
{
	try
	{
		if (!this->__clients[nb_client].__command.check_command())
			this->__clients[nb_client].__command.send_error(ERR_UNKNOWNCOMMAND, this->__clients[nb_client].get_fd());
		else if (!this->__clients[nb_client].__command.get_registration().get_pass())
		{
			if (!check_order(this->__clients[nb_client].__command.get_command(), 1))
				this->__clients[nb_client].__command.send_error(ERR_REGIST_ORDER, this->__clients[nb_client].get_fd());
			else if (!this->__clients[nb_client].__command.check_registration())
				this->__clients[nb_client].__command.send_error(ERR_NEEDMOREPARAMS, this->__clients[nb_client].get_fd());
			else if (this->__clients[nb_client].__command.get_command() != this->__password)
				this->__clients[nb_client].__command.send_error(ERR_WRONGPASSWORD, this->__clients[nb_client].get_fd());
			else 
				this->__clients[nb_client].__command.set_pass_registration(true);
		}
		else if (this->__clients[nb_client].__command.get_registration().get_pass() && !this->__clients[nb_client].__command.get_registration().get_nick())
		{
			if (!check_order(this->__clients[nb_client].__command.get_command(), 2))
				this->__clients[nb_client].__command.send_error(ERR_REGIST_ORDER, this->__clients[nb_client].get_fd());
			else if (this->__clients[nb_client].__command.chack_already_registred())
				this->__clients[nb_client].__command.send_error(ERR_ALREADYREGISTRED, this->__clients[nb_client].get_fd());
			else if (!this->__clients[nb_client].__command.check_registration())
				this->__clients[nb_client].__command.send_error(ERR_NONICKNAMEGIVEN, this->__clients[nb_client].get_fd());
			else if (this->parse_input(this->__clients[nb_client].__command.get_command(), 2) == 0)
				this->__clients[nb_client].__command.send_error(ERR_ERRONEUSNICKNAME, this->__clients[nb_client].get_fd());
			else if (this->parse_input(this->__clients[nb_client].__command.get_command(), 2) == -1)
				this->__clients[nb_client].__command.send_error(ERR_NICKNAMEINUSE, this->__clients[nb_client].get_fd());
			else
			{
				this->__clients[nb_client].set_nickname(this->__clients[nb_client].__command.get_command());
				this->__clients[nb_client].__command.set_nick_registration(true);
			}
		}
		else if (this->__clients[nb_client].__command.get_registration().get_nick() && !this->__clients[nb_client].__command.get_registration().get_user())
		{
			if (!check_order(this->__clients[nb_client].__command.get_command(), 3))
				this->__clients[nb_client].__command.send_error(ERR_REGIST_ORDER, this->__clients[nb_client].get_fd());
			else if (!check_user_params(this->__clients[nb_client].__command.get_command()))
				this->__clients[nb_client].__command.send_error(ERR_NEEDMOREPARAMS, this->__clients[nb_client].get_fd());
			else if (!this->__clients[nb_client].__command.check_registration())
				this->__clients[nb_client].__command.send_error(ERR_NEEDMOREPARAMS, this->__clients[nb_client].get_fd());
			else if (this->__clients[nb_client].__command.chack_already_registred() || (this->parse_input(this->__clients[nb_client].__command.get_command(), 1) == -1))
				this->__clients[nb_client].__command.send_error(ERR_ALREADYREGISTRED, this->__clients[nb_client].get_fd());
			else if (this->parse_input(this->__clients[nb_client].__command.get_command(), 1) == 0)
				this->__clients[nb_client].__command.send_error(ERR_ERRONEUSUSERNAME, this->__clients[nb_client].get_fd());
			else
			{
				this->__clients[nb_client].set_username(this->__clients[nb_client].__command.get_command());
				this->__clients[nb_client].__command.set_user_registration(true);
				this->__clients[nb_client].__command.send_error(RPL_WELCOME, this->__clients[nb_client].get_fd());
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

