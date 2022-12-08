#include "main.hpp"

class Channel
{
	private:
		vector<string>	__users;
		int				__channel_id;
		int				__users_count;
		string			__channel_name;


	public:
		Channel();
		Channel(vector<string> users, int channel_id, int users_count, string channel_name);
		Channel(const Channel &obj);
		~Channel();
};
