#include<iostream>
#include "Class.registration.hpp"
using std::string;

#ifndef CLASS_PARSER_HPP

#define CLASS_PARSER_HPP

#define PASS_COMMAND "PASS "
#define NICK_COMMAND "NICK "
#define USER_COMMAND "USER "

#define ERR_NEEDMOREPARAMS 461 //if user send a PASS command without password
#define MSG_461 "PASS :Not enough parameters"//if user send a PASS command without password

#define ERR_ALREADYREGISTRED 462 //if the user already registred and want to register a gain
#define MSG_462 ":You may not reregister"//if user send a PASS command without password

#define ERR_NONICKNAMEGIVEN 431
#define MSG_431 ":No nickname given"//if user send a PASS command without password

#define ERR_ERRONEUSNICKNAME 432
#define MSG_432 ":NICK :Erroneus nickname"//if user send a PASS command without password

class Parser
{
	private :
		string			type;
		string			command;
		int				nb_command;
		Registration	regsitration;
	public :
		int		get_nb_command() const;
		void	increment_nb_command();

		void			set_command(string);
		string			get_command();
		void			erase_command();
		bool			check_registration();
		bool			chack_already_registred();
		Registration	get_registration() const;
		void			set_pass_registration(bool);
		void			set_nick_registration(bool);
		void			set_user_registration(bool);
		void			send_error(int __err, int fd);
		Parser();
};

#endif