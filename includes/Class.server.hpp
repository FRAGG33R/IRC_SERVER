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
	public:
		Server();
		Server(string password, int port, string name);
		~Server(){};
		void	start_server();
		void	add_to_poll(struct pollfd *__poll_fds, int __fd);
		void	remove_from_poll(struct pollfd *__poll_fds, int __fd);
		void	full_close(struct pollfd *__poll_fd);
		int		password_autontification(string __server_password, int __client_fd, struct pollfd *__poll_fds);
};


