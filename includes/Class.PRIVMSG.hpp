#ifndef __PRIVMSG_HPP__
#define __PRIVMSG_HPP__
# include <iostream>
# include <vector>
# include <sstream>
class Channel;
class Privmsg
{
	private:
	    std::vector<int>	__receivers;
		std::string			__message;
		int					__sender;
		std::string			__type;
    public:
			Privmsg();
			~Privmsg();
			std::string			getMessage() const;
			std::vector<int>	getReceivers() const;
			int                 getSender() const;
			std::string         getType() const;
			void                setReceivers(std::vector<int> &receivers);
			void                setMessage(std::string &message);
			void                setSender(int sender);
			void                setType(std::string &type);
			int					parsPrivmsg(std::vector<std::string> __params, std::vector<std::string> __clients, std::vector<Channel> __channels);
};

#endif