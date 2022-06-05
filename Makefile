# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/04 14:24:31 by xle-boul          #+#    #+#              #
#    Updated: 2022/06/05 09:47:02 by xle-boul         ###   ########.fr        #
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

NAME := minishell
TEST_NAME := minishell_test

CC := gcc
CFLAGS := -Werror -Wall -Wextra
READLINE := -lreadline
INCLUDES := -I includes

SRC_DIR := srcs
OBJ_DIR := objs
SUB_DIRS := builtins debug env exec minishell parsing redirs utils
SOURCEDIRS := $(foreach dir, $(SUB_DIRS), $(addprefix $(SRC_DIR)/, $(dir)))

SRC_FILES := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))

RM = rm -rf
MKDIR = mkdir -p

LIB_DIR := libft
LIB_OBJ_DIR := libft/objs
LIB := libft.a

VPATH = $(SOURCEDIRS)

all: $(NAME)

$(NAME): directories $(OBJ_FILES) $(LIB)
	@printf "$(YELLOW)Compiling minishell...\n\n$(END)"
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB) $(READLINE) -o $(NAME)
	@printf "\n$(GREEN)minishell compiled.\n$(END)Simply type $(WHITE)./minishell$(END) to execute the program. Enjoy.\n\n"

$(OBJ_DIR)/%.o : %.c
	@printf "$(YELLOW)Compiling object:\n$(END)"
	$(CC) $(CFALGS) $(INCLUDE) $(READLINE) -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

directories:
	@$(MKDIR) $(OBJ_DIR)

$(LIB):
	@printf "$(YELLOW)Compiling libft.a...\n$(END)"
	@make $(LIB) -C $(LIB_DIR)
	@mv $(LIB_DIR)/$(LIB) .
	@printf "$(GREEN)libft.a compiled\n\n$(END)"

clean:
	@printf "$(YELLOW)Removing objects...\n$(END)"
	$(RM) $(OBJ_DIR)
	@printf "$(GREEN)Objects removed!\n\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing objects, libft and minishell executable...\n$(END)"
	$(RM) $(NAME)
	$(RM) $(LIB)
	@printf "$(GREEN)All clean!\n\n$(END)"

re: fclean all

.PHONY: directories clean fclean all re