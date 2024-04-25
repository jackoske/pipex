# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 17:11:12 by Jskehan           #+#    #+#              #
#    Updated: 2024/04/24 19:24:33 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Variables

NAME		= libftprintf.a
LIBFT		= libft


OBJ_DIR		= ./obj
SRC_DIR		= src

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
AR			= ar rcs
INCLUDE		= -I.
# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources
SRC_FILES	= ft_printf.c ft_printf_utils.c ft_printf_unsigned.c ft_printf_hex.c
SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

###


all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(AR) $(NAME) $(OBJS)
			@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@echo "$(BLUE)ft_printf object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a
			@$(RM) -f $(TEST_EXEC)
			@echo "$(CYAN)ft_printf executable files cleaned!$(DEF_COLOR)"
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for ft_printf!$(DEF_COLOR)"

norm:
			@norminette . $(INCLUDE) $(LIBFT) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
