#include "Class.registration.hpp"
#include "main.hpp"

#ifndef CLASS_PARSER_HPP

#define CLASS_PARSER_HPP

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
		void			send_msg(int __err, int fd);
		Parser();
};

#endif