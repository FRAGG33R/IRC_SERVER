
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
};