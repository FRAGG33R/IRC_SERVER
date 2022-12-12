#include "main.hpp"
class Client
{
	private :
		string	__username;
		string	__nickname;
		bool	__is_operator;
		bool	__authentication;
		int		__fd;
	public :
		~Client();
		Client(string username, string nickname, bool is_operator, bool authentication, int fd);
		Client(int fd);
		int	get_fd() const;
		bool    is_authenticate() const;
		void	set_authentication(bool authentication);

};