#ifndef __IRC__HPP__
#define __IRC__HPP__

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

//colors

#define GRN "\e[1;32m"
#define RESET "\e[0m"
#define RED "\e[1;31m"
#define MAX_PORT 65353
#define MAX_FD 1024

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::cerr;

# include "Class.client.hpp"
# include "Class.server.hpp"
# include "Class.error.hpp"

#endif