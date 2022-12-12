
class Client
{
	private :
		string	__username;
		string	__nickname;
		bool	__is_operator;
		bool	__authentication;
	public :
		~Client();
		Client(string username, string nickname, bool is_operator, bool authentication);
};