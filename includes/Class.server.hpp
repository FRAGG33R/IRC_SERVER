#ifndef CLASS_SERVER_HPP
#define CLASS_SERVER_HPP
#include "main.hpp"
#include "Class.channel.hpp"
class Client;
class Channel;
#include "Class.commands.hpp"
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
		void			run();
		void			print(void);
		void			create_server(void);
		static Server*	getInstance(string password, int port, string name = "CW9");
		void			add_to_poll(struct pollfd *__poll_fds, int __fd);
		void			full_close(struct pollfd *__poll_fd);
		void			remove_from_poll(struct pollfd *__poll_fds, int __fd);
		int				parse_input(string __input, int flag);
		int 			client_register(int __client_fd, int index);
		void			fill_username(int __client_fd, int index);
		void    		fill_nickname(int __client_fd, int index);
		void			fill_operator(int __client_fd, int index);
		void			connect_client(int nb_client);
		static void		sent_from_registration(int nb_client);
		void			join_client_to_channel(string nick_name, string shannel);
		void			__privmsg__(string, vector<string>);
		void			__notice__(string, vector<string>);
		void			__bot__(string,string);
		void			__mutualChannels__(string,string);
		Server(){};
		~Server(){};
};
#endif
