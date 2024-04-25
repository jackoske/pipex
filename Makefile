# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 19:10:25 by Jskehan           #+#    #+#              #
#    Updated: 2024/04/24 19:20:11 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex
CFLAGS	:=  -Wunreachable-code -Ofast -Wextra -Wall -Werror
OBJ_DIR	:= ./obj
DEBUG_FLAGS = -g


HEADERS	:= -I .

LIBFTPRINTF_A = libftprintf.a
LIBFTPRINTF_DIR = lib/libftprint/
LIBFTPRINTF  = $(addprefix $(LIBFTPRINTF_DIR), $(LIBFTPRINTF_A))

GNL = get_next_line.c get_next_line_utils.c
SRC_GNL = $(addprefix lib/gnl/, $(GNL))
SRC_FILES = main.c parser.c utils.c piping.c


SRC = $(addprefix src/, $(SRC_FILES))
SRCS	:= $(SRC_GNL)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
OBJS += $(SRCS:%.c=$(OBJ_DIR)/%.o) 

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFTPRINTF_DIR) > /dev/null
	@$(CC) $(OBJS) $(LIBFTPRINTF) $(LIBS) $(HEADERS) -o $(NAME)
	@@echo -e $(CURSIVE)$(GREEN) '     - SUCCESS!' $(NONE)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFTPRINTF_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re check_build_state
