#include "main.hpp"

class Server
{
	private:
		int					__socket_fd;
		int					__poll_res;
		struct sockaddr_in	__server_addr;
		struct pollfd		__poll_fds[MAX_FD];
		unsigned long		__address_len;
		string				__password;
		string              __server_name;
		in_port_t			__port;
		vector<Client>		__clients;
		string				__request;
		string				__interpret;
		Server(string password, int port, string name);
		static Server		*__instance;
	public:
		void			run();
		void			print(void);
		void			create_server(void);
		static Server*	getInstance(string password, int port, string name = "CW9");
		void			add_to_poll(struct pollfd *__poll_fds, int __fd);
		void			full_close(struct pollfd *__poll_fd);
		int				password_authentication(int __client_fd, int index);
		void			remove_from_poll(struct pollfd *__poll_fds, int __fd);
		int				parse_input(string __input, int flag);
		int 			client_register(int __client_fd, int index);
		void			fill_username(int __client_fd, int index);
		void    		fill_nickname(int __client_fd, int index);
		void			fill_operator(int __client_fd, int index);
		~Server(){};
};
