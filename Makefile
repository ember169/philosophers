# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 13:42:29 by lgervet           #+#    #+#              #
#    Updated: 2026/06/11 15:09:52 by mskn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CC			:= cc
CFLAGS		:= -pthread -Wall -Wextra -Werror -g3 -fsanitize=thread
INC			:= includes

SRCSDIR		:= srcs
OBJSDIR		:= objs

SRCS		:= \
				main.c \
				init.c \
				philo_spawn.c \
				philo_meals.c \
				manager.c \
				utils.c \
				time.c
OBJS		:= $(SRCS:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re