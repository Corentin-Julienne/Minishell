# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/04 14:24:31 by xle-boul          #+#    #+#              #
#    Updated: 2022/06/21 21:31:56 by xle-boul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
UNDERLINE	= \e[4m
RESET		= \033[0m
END			= \e[0m

OS := $(shell uname -s)

NAME := minishell
TEST_NAME := minishell_test

CC := gcc
CFLAGS := -Werror -Wall -Wextra -g

# little if / else statement to assign the proper flags for compilation
# depending on the OS

# add thi to the includes


RDL_PATH := -L/Users/cjulienn/.brew/opt/readline/lib/
RDL_HISTORY_PATH := -L/Users/cjulienn/.brew/opt/readline/lib/
RDL := -lreadline.8.1 $(RDL_PATH)
RDL_HISTORY := -lhistory.8.1 $(RDL_HISTORY_PATH)
READLINE := $(RDL) $(RDL_HISTORY)

#ifeq ($(OS),Linux)
#	READLINE := -lreadline
#else
# 	RDL_PATH := -L/usr/local/opt/readline/lib/
#	RDL_HISTORY_PATH := -L/usr/local/opt/readline/lib/
# 	RDL := -lreadline.8.1 $(RDL_PATH)
# 	RDL_HISTORY := -lhistory.8.1 $(RDL_HISTORY_PATH)
# 	READLINE := $(RDL) $(RDL_HISTORY)
#endif

INCLUDES := -I includes

SRC_DIR := srcs
OBJ_DIR := objs
SUB_DIRS := builtins debug env exec minishell parsing redirs utils gnl
SOURCEDIRS := $(foreach dir, $(SUB_DIRS), $(addprefix $(SRC_DIR)/, $(dir)))

SRC_FILES := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))

RM := rm -rf
MKDIR := mkdir -p

LIB_DIR := libft
LIB_OBJ_DIR := libft/obj
LIB_OBJ_DIR_BONUS := libft/obj_bonus
LIB := libft.a

VPATH := $(SOURCEDIRS)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIB)
	@printf "$(YELLOW)Linking minishell...\n\n$(END)"
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB) $(READLINE) -o $(NAME)
	@printf "\n$(GREEN)minishell compiled.\n$(END)Simply type $(WHITE)./minishell$(END) to execute the program. Enjoy.\n\n"

$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR)
	@printf "$(YELLOW)Compiling object:\n$(END)"
	$(CC) $(CFLAGS) -I/Users/cjulienn/.brew/opt/readline/include/readline $(INCLUDE) -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

$(LIB):
	@printf "$(YELLOW)Compiling libft.a...\n$(END)"
	@make --no-print-directory $(LIB) -C $(LIB_DIR)
	@mv $(LIB_DIR)/$(LIB) .
	@printf "$(GREEN)libft.a compiled\n\n$(END)"

clean:
	@printf "$(YELLOW)Removing objects...\n$(END)"
	$(RM) $(OBJ_DIR)
	$(RM) $(LIB_OBJ_DIR)
	$(RM) $(LIB_OBJ_DIR_BONUS)
	@printf "$(GREEN)Objects removed!\n\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing objects, libft and minishell executable...\n$(END)"
	$(RM) $(NAME)
	$(RM) $(LIB)
	@printf "$(GREEN)All clean!\n\n$(END)"

re: fclean all

norm:
	@norminette includes libft srcs

.PHONY: clean fclean all re
