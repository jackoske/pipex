# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 10:13:23 by Jskehan           #+#    #+#              #
#    Updated: 2024/02/13 13:44:39 by Jskehan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c)
OBJDIR := ./obj

# Ensure object file paths are correctly prefixed with OBJDIR
OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# The all target should depend on $(NAME)
all: $(NAME)

# Ensure OBJDIR exists before compiling anything
$(NAME): $(OBJDIR) $(OBJ)
		ar rcs $(NAME) $(OBJ)
		ranlib $(NAME)

# Rule to create OBJDIR
$(OBJDIR):
		mkdir -p $(OBJDIR)

# Rule to compile .c files into .o files within OBJDIR
$(OBJDIR)/%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ -I .

# Clean only object files
clean:
		rm -f $(OBJDIR)/*.o

# Full clean including the library file and the OBJDIR
fclean: clean
		rm -f $(NAME)
		rm -rf $(OBJDIR)

# Rebuild everything
re: fclean all
