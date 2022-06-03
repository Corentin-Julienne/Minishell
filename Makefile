# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 16:57:50 by cjulienn          #+#    #+#              #
#    Updated: 2022/06/03 13:07:24 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRCS_PATH= ./srcs/

SRCS= $(SRCS_PATH)builtins/bt_cd.c \
	  $(SRCS_PATH)builtins/bt_echo.c \
	  $(SRCS_PATH)builtins/bt_env.c \
	  $(SRCS_PATH)builtins/bt_exit.c \
	  $(SRCS_PATH)builtins/bt_export.c \
	  $(SRCS_PATH)builtins/bt_pwd.c \
	  $(SRCS_PATH)builtins/bt_unset.c \
	  $(SRCS_PATH)debug/debug_utils.c \
	  $(SRCS_PATH)env/envdup.c \
	  $(SRCS_PATH)env/paths.c \
	  $(SRCS_PATH)exec/exec_cmd.c \
	  $(SRCS_PATH)exec/exec_errors.c \
	  $(SRCS_PATH)exec/exec_path_cmd.c \
	  $(SRCS_PATH)minishell/minishell.c \
	  $(SRCS_PATH)parsing/expansions.c \
	  $(SRCS_PATH)parsing/parsing.c \
	  $(SRCS_PATH)parsing/quotes.c \
	  $(SRCS_PATH)parsing/tokenisation.c \
	  $(SRCS_PATH)redirs/fd_redirs.c \
	  $(SRCS_PATH)redirs/pipes.c \
	  $(SRCS_PATH)redirs/spawn_children.c \
	  $(SRCS_PATH)utils/free.c \
	  $(SRCS_PATH)structs/init_structs.c \
	  $(SRCS_PATH)structs/token_utils_1.c \
	  $(SRCS_PATH)structs/token_utils_2.c \
	  $(SRCS_PATH)utils/ft_triple_join.c

# suppress in final repo	  
SRCS_TEST= \
	  $(SRCS_PATH)debug/debug_utils.c \
	  $(SRCS_PATH)env/envdup.c \
	  $(SRCS_PATH)env/paths.c \
	  $(SRCS_PATH)exec/exec_cmd.c \
	  $(SRCS_PATH)exec/exec_errors.c \
	  $(SRCS_PATH)exec/exec_path_cmd.c \
	  $(SRCS_PATH)minishell/minishell.c \
	  $(SRCS_PATH)minishell/process_tokens.c \
	  $(SRCS_PATH)parsing/parsing.c \
	  $(SRCS_PATH)parsing/quotes.c \
	  $(SRCS_PATH)parsing/tokenisation.c \
	  $(SRCS_PATH)redirs/fd_redirs.c \
	  $(SRCS_PATH)redirs/pipes_redirs_cmd.c \
	  $(SRCS_PATH)redirs/pipes.c \
	  $(SRCS_PATH)utils/free_tools.c \
	  $(SRCS_PATH)utils/init_structs.c \
	  $(SRCS_PATH)utils/redir_utils.c \
	  $(SRCS_PATH)utils/token_utils_1.c \
	  $(SRCS_PATH)utils/token_utils_2.c

# suppress in final repo
OBJS_TEST = $(SRCS_TEST:.c=.o)

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

re:	fclean
	$(MAKE)

test: $(OBJS_TEST)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS_TEST) -Llibft -lft $(RDL) $(RDL_HISTORY) -o $(NAME)
	cp /usr/local/opt/readline/lib/libreadline.8.1.dylib .
	cp /usr/local/opt/readline/lib/libhistory.8.1.dylib .
	@echo $(NAME) successfully made !!!

clean_test:
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(OBJS_TEST)
	$(RM) $(NAME)
	rm ./libreadline.8.1.dylib
	rm ./libhistory.8.1.dylib

.PHONY: all clean fclean re test clean_test
