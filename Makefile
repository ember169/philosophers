# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgervet <42@leogervet.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 13:42:29 by lgervet           #+#    #+#              #
#    Updated: 2026/03/13 15:52:11 by lgervet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CC			:= cc
CFLAGS		:= -pthread -Wall -Wextra -Werror -g3 -fsanitize=thread
INC			:= includes

SRCSDIR		:= srcs
OBJSDIR		:= objs

SRCS		:= \
				philo.c \
				threads.c \
				utils.c
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