#ifndef CLASS_CLIENT_HPP
# define CLASS_CLIENT_HPP

#include "Class.parser.hpp"
#include "Class.commands.hpp"
#include "Class.JOIN.hpp"
#include "Class.PRIVMSG.hpp"
#include "Class.MODE.hpp"

class Client
{
	private :
		string	__username;
		string	__nickname;
		string	__channel_name; 
		bool	__is_operator;
		bool	__is_authenticated;
		bool	__is_registred;
		int		__fd;
	public :
		Parser	__command;
		Privmsg	__privmsg;
		Mode	__mode;
		bool	__username_filled;
		bool	__nickname_filled;
		string	__request;
		string	__interpret;

		~Client();
		Client(string username, string nickname, bool is_operator, bool authentication, int fd);
		Client(int fd);

		int		get_fd() const;
		string	get_username() const;
		string	get_nickname() const;
		bool    is_operator() const;
		bool	is_registred() const;
		bool    is_authenticate() const;
		void	set_fd(int fd);
        void    set_username(string username);
		void    set_nickname(string nickname);
		void    set_is_operator(bool is_operator);
		void    set_is_registred(bool is_registred);
		void	set_authentication(bool authentication);

};
#endif