# include "main.hpp"

class Channel
{
	private:
		vector<Client>	__clients;
		int				__channel_id;
		int				__clients_size;
		string			__channel_name;

	public:
		Channel();
		Channel(vector<Client> users, int channel_id, int users_count, string channel_name);
		Channel(const Channel &obj);
		~Channel();
};
