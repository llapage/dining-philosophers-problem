# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llapage <llapage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 16:59:28 by llapage           #+#    #+#              #
#    Updated: 2024/01/15 11:03:54 by llapage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

#-------------------SOURCES PATH----------------------
SOURCES     = src/
HEADER_PWD  = ./includes/

#-------------------COMPILATION-----------------------
CC	= cc

FLAGS	= -Wall -Werror -Wextra
#FLAGS	= -Wall -Werror -Wextra -g
#FLAGS	= -Wall -Werror -Wextra -pthread -g -fsanitize=thread
#FLAGS	= -Wall -Werror -Wextra -g -fsanitize=address

#-------------------SOURCES FILES----------------------
HEADERS     =   $(HEADER_PWD)philo.h

SRCS        =	$(SOURCES)main.c \
				$(SOURCES)params.c \
				$(SOURCES)utils.c \
				$(SOURCES)philo.c \
				$(SOURCES)forks.c \
				$(SOURCES)thread.c \
				$(SOURCES)tasks.c \
				$(SOURCES)main_thread.c \
				$(SOURCES)free.c \

SRC_LIBFT   =

#-------------------OBJECTS----------------------
OBJS        =   $(SRCS:.c=.o)
LIBFT_OBJ	=	$(SRC_LIBFT:.c=.o)

#-------------------HEADERS----------------------
I_HEADER    =   $(addprefix( -include, $(HEADERS)))
I_H_LIB     =   $(addprefix( -include, $(H_LIB)))

#-------------------COLORS-----------------------
RED         =   \x1b[31m
YELLOW      =   \x1b[33m
GREEN       =   \x1b[32m
NO_COLOR    =   \x1b[0m
BOLD        =   \x1b[1m
BOLD_OFF    =   \x1b[21m

#-------------------RULES-----------------------
%.o: %.c
			@printf "$(YELLOW)Generating $(NAME) objects... %-33.33s\r$(NO_COLOR)" $@
			@$(CC) $(FLAGS) -Iincludes $(I_H_LIB) -c $< -o $@
$(NAME):    $(LIBFT_OBJ) $(OBJS)
			@printf "$(GREEN)Compiling $(NAME)... %33s\r$(NO_COLOR)" " "
			@$(CC) $(FLAGS) $(OBJS) $(LIBFT_OBJ) -o $(NAME)
			@echo "\n$(GREEN)$(BOLD)$@ done !$(BOLD_OFF)$(NO_COLOR)"

all:	$(NAME)

clean:
		@echo "$(RED)Deleting objects...$(NO_COLOR)"
		@rm -rf $(OBJS)
		@rm -rf $(B_OBJS)
fclean:	clean
		@echo "$(RED)Deleting executables...$(NO_COLOR)"
		@rm -f $(NAME)
		@rm -f $(CHECKER)
re:	fclean all

.PHONY: all clean fclean bonus re
