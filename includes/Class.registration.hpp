#include<iostream>
using std::string;

#ifndef CLASS_REGISTRATION_HPP

#define CLASS_REGISTRATION_HPP

#define PASS_COMMAND "PASS "
#define NICK_COMMAND "NICK "
#define USER_COMMAND "USER "

#define ERR_NEEDMOREPARAMS "461 * PASS :Not enough parameters\n"
#define ERR_ALREADYREGISTRED "462 * REGISTER :Wrong password\n"
#define ERR_NONICKNAMEGIVEN "431 * REGISTER :No nickname given\n"

class Registration
{
	private :
		bool pass;
		bool nick;
		bool user;

	public :
		Registration();
		bool	get_pass() const;
		bool	get_nick() const;
		bool	get_user() const;
		void	set_pass(bool);
		void	set_nick(bool);
		void	set_user(bool);
};

#endif