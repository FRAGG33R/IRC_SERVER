#include "main.hpp"

class Server 
{
	private:
		int					__socket_fd;
		int					__poll_res;
		struct sockaddr_in	__server_addr;
		struct pollfd		__poll_fds[MAX_FD];
		int                	__address_len;
		string				__password;
		int					__port;
	public:
		Server();
		~Server();
		Server(int __socket_fd, int __poll_res, string __password, int __port);
};