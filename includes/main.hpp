#ifndef __IRC__HPP__
#define __IRC__HPP__
//Librarys
# include <iostream>
# include <string>
# include <vector>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <poll.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <iomanip>

//Colors
#define GRN "\e[1;32m"
#define RESET "\e[0m"
#define RED "\e[1;31m"
#define MAX_PORT 65353
#define MAX_FD 1024

//Namespace
using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::cerr;

// Classes
# include "Class.client.hpp"
# include "Class.server.hpp"
# include "Class.error.hpp"
#include "Class.parser.hpp"
// # include "Class.channel.hpp"

//Functions
bool	is_str_digit(const string &__s);
int		parse_arguments(const string &__port, const string &__password);
int		is_command(string __request);

#endif