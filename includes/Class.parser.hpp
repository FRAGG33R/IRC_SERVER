#include<iostream>
#include "Class.registration.hpp"
using std::string;

#ifndef CLASS_PARSER_HPP

#define CLASS_PARSER_HPP

#define PASS_COMMAND "PASS "
#define NICK_COMMAND "NICK "
#define USER_COMMAND "USER "

#define ERR_NEEDMOREPARAMS 461
#define MSG_461 "PASS :Not enough parameters\n"

#define ERR_ALREADYREGISTRED 462
#define MSG_462 ":You may not reregister\n"

#define ERR_NONICKNAMEGIVEN 431
#define MSG_431 ":No nickname given\n"

#define ERR_ERRONEUSNICKNAME 432
#define MSG_432 ":NICK :Erroneus nickname\n"

#define ERR_NICKNAMEINUSE 433
#define MSG_433 "NICK :Nickname is already in use\n"

#define ERR_WRONGPASSWORD 666
#define MSG_666 "PASS :Wrong pass word\n"

#define ERR_UNKNOWNCOMMAND 421
#define MSG_421 ":Unknown command\n"

#define ERR_REGIST_ORDER 667
#define MSG_667 ":Enter PASS <password>, NICK <nickname>, USER <user>\n"



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
		bool			check_cmmand_registration();
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