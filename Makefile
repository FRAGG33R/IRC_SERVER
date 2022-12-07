SRC_FILE = main.cpp

OBJ_FILE = $(SRC_FILE:.cpp=.o)

NAME = ircserv

RED = \033[0;31

YELLOW = \033[0;33m

BLUE=\033[0;34m

RESET = \033[0m

GREEN=\033[0;32m

INCLUDE = includes/main.hpp

CC = c++

FLAGS = -Wextra -Werror -std=c++98

all:$(NAME)

%.o:%.cpp $(INCLUDE)
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "[$(GREEN) OK $(RESET)]$(YELLOW) Compiling $<$(RESET)"

$(NAME) : $(OBJ_FILE)
	@$(CC) $(FLAGS) $(OBJ_FILE) -o $(NAME)

clean :
	@rm -rf $(OBJ_FILE)
	@echo "[$(GREEN) OK $(RESET)]$(YELLOW) Object files deleted$(RESET)"

fclean :
	@rm -rf $(OBJ_FILE) $(NAME)
	@echo "[$(GREEN) OK $(RESET)]$(YELLOW) $(NAME) deleted$(RESET)"

re : fclean all

.PHONY : clean fclean re
