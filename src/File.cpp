#include "../includes/Class.file.hpp"

File::File()
{

}

File::~File()
{

}
File::File(std::string file_content, std::string file_path, int recever_fd)
{
	this->__file_content = file_content;
	this->__file_path = file_path;
	this->__receiver_fd = recever_fd;

}
File& File::operator=(const File& other) {
	if (this != &other) {
		this->__file_content = other.__file_content;
		this->__file_path = other.__file_path;
		this->__receiver_fd = other.__receiver_fd;
	}
	return *this;
}

void	File::set_extension(const std::string& extension)
{
	this->__extension = extension;
}