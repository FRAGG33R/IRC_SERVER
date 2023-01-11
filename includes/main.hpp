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
# include <sstream>

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
# include "Class.error.hpp"
# include "Class.parser.hpp"
# include "Class.registration.hpp"



//commands
#define PASS_COMMAND "PASS"
#define NICK_COMMAND "NICK"
#define USER_COMMAND "USER"

//error reply numbers
#define ERR_NEEDMOREPARAMS 461
#define MSG_461 ":* 461 * Not enough parameters\n"
#define ERR_ALREADYREGISTRED 462
#define MSG_462 ":* 462 * You may not reregister\n"
#define ERR_NONICKNAMEGIVEN 431
#define MSG_431 ":* 431 * No nickname given\n"
#define ERR_ERRONEUSNICKNAME 432
#define MSG_432 ":NICK 432 * Erroneus nickname\n"
#define ERR_NICKNAMEINUSE 433
#define MSG_433 ":NICK 433 * Nickname is already in use\n"
#define ERR_WRONGPASSWORD 666
#define MSG_666 ":PASS 666 * wrong password\n"
#define ERR_UNKNOWNCOMMAND 421
#define MSG_421 ":* 421 * Unknown command\n"
#define ERR_REGIST_ORDER 667
#define MSG_667 ":* 667 * Enter PASS <password>, NICK <nickname>, USER <user>\n"
#define ERR_ERRONEUSUSERNAME 668
#define MSG_668 ":NICK 668 * Erroneus username\n"

#define MSG_411 ":* 411 * No recipient given\n"
#define ERR_NORECIPIENT 411
#define MSG_412 ":* 412 * No text to send\n"
#define ERR_NOTEXTTOSEND 412
#define MSG_407 ":* 407 * Duplicate recipients. No message delivered\n"
#define ERR_TOOMANYTARGETS 407
#define MSG_401 ":* 401 * No such nick/channel\n"
#define ERR_NOSUCHNICK 401
// # include "Class.channel.hpp"

//server informations

#define RPL_WELCOME 1

#define SERVER_NAME "machlouj"
#define CONCAT(x, y) x ##y

#define WELCOME ":* 001 * welcome to "
#define MSG_WELCOME WELCOME SERVER_NAME "\n"

//Functions
bool	is_str_digit(const string &__s);
int		parse_arguments(const string &__port, const string &__password);
int		is_command(string __request);

#endif