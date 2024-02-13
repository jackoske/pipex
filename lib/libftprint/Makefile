# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 17:11:12 by Jskehan           #+#    #+#              #
#    Updated: 2023/12/06 17:11:13 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Variables

NAME		= libftprintf.a
LIBFT		= libft
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
AR			= ar rcs
INCLUDE		= .
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

# SRC_FILES	=	ft_printf ft_printf_utils ft_print_ptr ft_print_unsigned ft_print_hex
SRC_FILES	=	ft_printf ft_printf_utils ft_printf_unsigned ft_printf_hex

OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))


TEST_SRC   = test_ft_printf.c
TEST_OBJ   = $(OBJ_DIR)test_ft_printf.o
TEST_EXEC  = test_ft_printf

###

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(AR) $(NAME) $(OBJ)
			@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: %.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

$(TEST_EXEC): $(NAME) $(TEST_OBJ)
	@echo "$(YELLOW)Linking test: $@ $(DEF_COLOR)"
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $@ -L. -lftprintf -I$(INCLUDE)

test: $(NAME) $(TEST_EXEC)


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
