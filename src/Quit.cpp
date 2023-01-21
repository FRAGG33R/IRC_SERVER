# include "../includes/Class.QUIT.hpp"

//close the client file descriptor
//remove the client from all channels (vectors)
//broadcast the message in all  channels that the client exist on
//remove the client from the vector of client in the server class
//default message "user has quit"

int	Quit::quit(std::vector<std::string> &__params, std::vector<Channel> &__channels, std::pair<std::string, int> __client)
{
	std::string __message;
	std::string	__reason;
	int			__exist = 0;

	if (__params[0][0] != ':')
	{
		__message =  ": " + __client.first + " 412 * No text to send\n";
		if (send(__client.second, __message.c_str(), __message.size(), 0) == -1)
			return (-1);
		return (1);
	}
	for (size_t i = 0; i < __params.size(); i++)
		__reason += __params[i];
	for (size_t i = 0; i < __channels.size(); i++)
	{
		__exist = 0;
		for (size_t j = 0; j < __channels[i].get_clients().size(); j++)
		{
			if (__channels[i].get_clients()[j].first == __client.second) {
				__channels[i].get_clients().erase(__channels[i].get_clients().begin() + j);
				__exist = 1;
				break;
			}
		}
		if (__exist == 1)
		{
			__message = __client.first + " has quit :" + __reason + "\n";
			for (size_t j = 0; j < __channels[i].get_clients().size(); j++)
			{
				if (send(__channels[i].get_clients()[j].first, __message.c_str(), __message.size(), 0) == -1)
					return (-1);
			}
			for (size_t j = 0; j < __channels[i].get_operators().size(); j++)
			{
				if (__channels[i].get_operators()[j].first == __client.second) {
					__channels[i].get_operators().erase(__channels[i].get_operators().begin() + j);
					break;
				}
			}
		}
	}
	close (__client.second);
	return (0);
}
