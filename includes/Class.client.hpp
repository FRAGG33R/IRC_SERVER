
class Client
{
	private :
		string	__name;
		string	__password;
		string	__neckname;
		int		__id;
		bool	__is_operator;
	public :
		~Client();
		Client();
		Client(string name, string password, string neckname, int id, bool is_operator);
		Client(const Client& other);
};