SRC_FILE = main.cpp \
			src/Client.cpp src/Channel.cpp src/Server.cpp src/Error.cpp src/Parsing.cpp \
			src/Parser.cpp src/Registration.cpp src/Commands.cpp src/Privmsg.cpp src/Join.cpp \
			src/mode.cpp src/Part.cpp src/Kick.cpp

OBJ_FILE = $(SRC_FILE:.cpp=.o)

NAME = ircserv

RED = \033[0;31

YELLOW = \033[0;33m

BLUE=\033[0;34m

RESET = \033[0m

GREEN=\033[0;32m

INCLUDE = $(wildcard includes/*.hpp)

CC = c++

CFLAGS = -Wextra  -std=c++98

all:$(NAME)

%.o:%.cpp $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@ -g
	@echo "[$(GREEN) OK $(RESET)]$(YELLOW) Compiling $<$(RESET)"

$(NAME) : $(OBJ_FILE)
	@$(CC) $(FLAGS) $(OBJ_FILE) -o $(NAME) -g

clean :
	@rm -rf $(OBJ_FILE)
	@echo "[$(GREEN) OK $(RESET)]$(YELLOW) Object files deleted$(RESET)"

fclean :
	@rm -rf $(OBJ_FILE) $(NAME)
	@echo "[$(GREEN) OK $(RESET)]$(YELLOW) $(NAME) deleted$(RESET)"
run : 
	make && ./ircserv 3 local

re : fclean all

.PHONY : clean fclean re
