#ifndef CLASS_PARSER_HPP

#define CLASS_PARSER_HPP
#include "main.hpp"
#include "Class.registration.hpp"

class Parser
{
	private :
		string			command;
		vector<string>	params;
		Registration	regsitration;

	public :
		void			set_command(string);
		string			get_command();
		bool			check_command();
		void			erase_command();
		bool			check_cmmand_registration();
		bool			check_registration();
		bool			chack_already_registred();
		Registration	get_registration() const;
		void			set_pass_registration(bool);
		void			set_nick_registration(bool);
		void			set_user_registration(bool);
		void			send_error(int __err, int fd);
		void			send_message(std::string __msg, int __fd);
		vector<string>	&get_params( void );
		void			set_params(const vector<string> &parametters);
		Parser();
		~Parser();
};

#endif