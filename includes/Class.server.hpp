#ifndef CLASS_SERVER_HPP
#define CLASS_SERVER_HPP
#include "main.hpp"
#include "Class.channel.hpp"
class Client;
class Channel;
class command;

class Server
{
	protected:
		int					__socket_fd;
		int					__poll_res;
		struct sockaddr_in	__server_addr;
		struct pollfd		__poll_fds[MAX_FD];
		unsigned long		__address_len;
		string				__password;
		string				__server_name;
		in_port_t			__port;
		vector<Client>		__clients;
		vector<Channel>		__channels;
		Server(string password, int port, string name);
		static Server		*__instance;
	public:
		void							run();
		void							print(void);
		void							create_server(void);
		static Server*					getInstance(string password, int port, string name = "CW9");
		vector<std::pair<string, int> >	get_clients(void);
		vector<Channel>					get_channels(void);
		vector<Channel>					&get_ref_channels(void);
		void							add_to_poll(struct pollfd *__poll_fds, int __fd);
		void							full_close(struct pollfd *__poll_fd);
		void							remove_from_poll(struct pollfd *__poll_fds, int __fd);
		int								parse_input(string __input, int flag);
		void							connect_client(int nb_client);
		void                            clean_channels(std::vector<Channel> &__channels, int __fd);
		void                            bot(std::string __client_name, int __client_fd);

		Server(){};
		~Server(){};
};
#endif
