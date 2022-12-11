# include <iostream>
# include <string>

class Error : public std::exception
{
	private:
		std::string	__message;
	public:
		Error();
	    Error(const std::string& message);
		const char *what() const throw();
		~Error() throw(){};
};