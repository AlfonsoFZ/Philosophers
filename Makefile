# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 19:30:12 by alfofern          #+#    #+#              #
#    Updated: 2023/08/16 20:19:46 by alfofern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers.a
PROGRAM = philo
CFLAGS = -Wall -Werror -Wextra -pthread
SANITIZE = -fsanitize=thread -g
PROJECTNAME = Philosophers
CC = gcc
CLEAN = rm -Rf
SRC = 	src/main.c\
		src/philo_utils.c \
		src/checker.c \
		src/philo_th.c \
		src/time.c
		
DATETIME := $(shell date +%Y-%m-%d' '%H:%M:%S)

OBJS := $(SRC:.c=.o)

all: $(PROGRAM)

$(PROGRAM): $(NAME)
	@$(CC) $(CFLAGS) $(NAME) -o $(PROGRAM)
	@echo "$(YELLOW) $(PROGRAM) program $(GREEN)successfully $(YELLOW)created .$(DEFAULT)"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

# $(PROGRAM): $(NAME)
# 	@$(CC) $(SANITIZE) $(CFLAGS) $(NAME) -o $(PROGRAM)
# 	@echo "$(YELLOW) $(PROGRAM) program $(GREEN)successfully $(YELLOW)created .$(DEFAULT)"

# .c.o:
# 	@$(CC) $(SANITIZE) $(CFLAGS) -c $< -o ${<:.c=.o}
	
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
clean:
	@$(CLEAN) ./$(OBJS)
fclean: clean
	@$(CLEAN) ./$(NAME) ./$(PROGRAM)

re: fclean all

#COLORS
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
DEFAULT	:= \033[0m

.PHONY : all clean fclean re bonus git gitignore submodules 42prepare .c.o
