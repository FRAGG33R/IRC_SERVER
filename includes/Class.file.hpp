#ifndef __FILE_HPP__
# define __FILE_HPP__

# include <iostream>
class File
{
	private:
		std::string	__file_content;
		std::string	__file_path;
		std::string	__extension;
		int		__receiver_fd;
	public:
        File();
		File(std::string file_content, std::string file_path, int recever_fd);
        ~File();
		File& operator=(const File& other);
		void	set_extension(const std::string& extension);
};
#endif