# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 18:36:14 by cjulienn          #+#    #+#              #
#    Updated: 2022/05/30 20:46:56 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= lab

SRCS_PATH= ./

SRCS= ./lab.c

OBJS = $(SRCS:.c=.o)

CC= gcc
CFLAGS= -Wall -Wextra -Werror

RM= rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(NAME) successfully made !!!

all: $(NAME)

clean:
	$(RM) $(OBJS)
	
fclean:	clean
	$(RM) $(NAME)

re:	fclean
	$(MAKE)

.PHONY: all clean fclean re
