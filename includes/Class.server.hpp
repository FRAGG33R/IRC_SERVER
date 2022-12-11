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
		Server(int socket_fd, string password, int port, string name);
		~Server(){};
		void	start_server();
};