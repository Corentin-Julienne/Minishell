# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 16:57:50 by cjulienn          #+#    #+#              #
#    Updated: 2022/04/24 16:58:13 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRCS= ./srcs/builtins/bt_cd.c \
	  ./srcs/builtins/bt_echo.c \
	  ./srcs/builtins/bt_env.c \
	  ./srcs/builtins/bt_exit.c \
	  ./srcs/builtins/bt_export.c \
	  ./srcs/builtins/bt_pwd.c \
	  ./srcs/builtins/bt_unset.c \
	  ./srcs/env/env_ops.c \
	  ./srcs/exec/exec_cmd.c \
	  ./srcs/exec/exec_builtins.c \
	  ./srcs/errors/errors.c \
	  ./srcs/free/free_utils.c \
	  ./srcs/minishell/init_structs.c \
	  ./srcs/minishell/minishell.c \
	  ./srcs/ops/expansions.c \
	  ./srcs/ops/pipes.c \
	  ./srcs/ops/redirections.c \
	  ./srcs/parsing/parse_input.c \
	  ./srcs/parsing/quotes.c \
	  ./srcs/utils/args_utils_1.c \
	  ./srcs/utils/args_utils_2.c
	  
OBJS = $(SRCS:.c=.o)

INCLUDE_PATH = ./includes/

LIBFT_LIB = libft.a
LIBFT_PATH = ./libft/

RDL_PATH = -L/usr/local/opt/readline/lib/
RDL_HISTORY_PATH = -L/usr/local/opt/readline/lib/

RDL = -lreadline.8.1 $(RDL_PATH)
RDL_HISTORY = -lhistory.8.1 $(RDL_HISTORY_PATH)

CC= gcc
CFLAGS= -Wall -Wextra -Werror -I$(INCLUDE_PATH)

RM= rm -f

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft $(RDL) $(RDL_HISTORY) -o $(NAME)
	cp /usr/local/opt/readline/lib/libreadline.8.1.dylib .
	cp /usr/local/opt/readline/lib/libhistory.8.1.dylib .
	@echo $(NAME) successfully made !!!

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)
	rm ./libreadline.8.1.dylib
	rm ./libhistory.8.1.dylib
	
fclean:	clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
