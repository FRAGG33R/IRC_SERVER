#include "../includes/Class.join.hpp"

Join::Join()
{

}

// void	Join::set_channels_keys(std::vector<std::string> __params)
// {
// 	size_t	begin;
// 	size_t	end;

// 	//TODO send error if there is a message to send
// 	while (params[0].find("#") != std::string::npos)
// 	{
// 		begin = params[0].find("#");
// 		end = params[0].find(",");
// 		if (end = std::string::npos)
// 			end = params[0].size();
// 		this->__channels.push_back(params[0].);
// 		params[0] = params[0].substr(begin, end);
// 	}
// 	if (!params[0].empty())
// 		this->__channels.push_back(0, std::string::npos);
// }