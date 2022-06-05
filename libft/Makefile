# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/10 21:26:49 by xle-boul          #+#    #+#              #
#    Updated: 2022/06/05 00:47:29 by xle-boul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR := .
SRC_DIR_BONUS := bonus

SRC := $(wildcard $(SRC_DIR)/*.c)
SRC_BONUS := $(SRC) $(wildcard $(SRC_DIR_BONUS)/*.c)

OBJ_DIR := obj
OBJ_DIR_BONUS := obj_bonus
OBJ := $(SRC:.c=.o)
OBJECTS_PREFIXED := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ)))

OBJ_BONUS := $(SRC_BONUS:.c=.o)
OBJECTS_BONUS_PREFIXED := $(addprefix $(OBJ_DIR_BONUS)/, $(notdir $(OBJ_BONUS)))

INCLUDE := .

CC := gcc
CC_FLAGS := -Wall -Wextra -Werror

VPATH = $(SRC_DIR_BONUS)

all: $(NAME)

$(OBJ_DIR)/%.o : %.c libft.h
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o : %.c libft.h
	@mkdir -p $(OBJ_DIR_BONUS)
	@echo "Compiling: $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_PREFIXED)
	@echo "$(NAME), created!"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rd $(OBJ_DIR_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJECTS_BONUS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_BONUS_PREFIXED)
	@echo "$(NAME) Bonus, created!"

.PHONY: directory directory_bonus clean fclean bonus all re