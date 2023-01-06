#include<iostream>
using std::string;

#ifndef CLASS_REGISTRATION_HPP

#define CLASS_REGISTRATION_HPP

#define PASS_COMMAND "PASS "
#define NICK_COMMAND "NICK "
#define USER_COMMAND "USER "

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