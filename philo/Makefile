NAME = philo
GCC = gcc
FLAGS = -Wall -Wextra -Werror

PATH_SRC = src/
PATH_OBJ = obj/
INC = includes/

FILES= 	utiles.c\
	  	main.c\
	  	utiles2.c

OBJ = $(addprefix $(PATH_OBJ), $(FILES:.c=.o))
SRC = $(addprefix $(PATH_SRC), $(FILES:.c=.o))

DEF = 		\x1B[1;0m
RED = 		\x1B[1;31m
PURPLE =	\x1B[1;34m
BLUE = 		\x1B[1;96m
GREEN = 	\x1B[1;32m
SILVER = 	\x1B[1;90m
YELLOW = 	\x1B[1;33m

all: $(NAME)

$(NAME): $(OBJ)
	@$(GCC) $(FLAGS) $(OBJ) -o $(NAME)
	@printf "$(SILVER)[$(PURPLE)Output$(RED) $(NAME) $(SILVER)] $(GREEN)Created.$(DEF)\n"

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(INC)header.h
	@mkdir -p $(PATH_OBJ)
	@$(GCC) $(FLAGS) -c $< -o $@ -I $(INC)
	@printf "$(SILVER)[$(PURPLE)Object file$(BLUE) $< $(SILVER)] $(GREEN)Created.$(DEF)\n"

clean:
	@rm -rf $(PATH_OBJ)
	@printf "$(SILVER)[$(PURPLE)Diroctory $(YELLOW) $(PATH_OBJ) $(SILVER)] $(RED)Deleted.$(DEF)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(SILVER)[$(PURPLE)Output	$(YELLOW) $(NAME) $(SILVER)] $(RED)Deleted.$(DEF)\n"

re: fclean all

.PHONY: all clean fclean re