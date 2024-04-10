# Compiler
CC = cc

#adding GNL 
GNL = get_next_line.c get_next_line_utils.c
SRC_GNL = $(addprefix lib/gnl/, $(GNL))

# Source file directory
SRC_DIR = src/

# Source files (automatically include all .c files from SRC_DIR)
SRC = $(wildcard $(SRC_DIR)*.c) $(SRC_GNL)

# Output file
NAME = pipex

# Compiler flags
DFLAGS = -g
WFLAGS = -Wall -Wextra -Werror

LIBFTPRINTF_A = libftprintf.a
LIBFTPRINTF_DIR = lib/libftprint/
LIBFTPRINTF  = $(addprefix $(LIBFTPRINTF_DIR), $(LIBFTPRINTF_A))

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
RED='\033[31m'

# Default target
all: $(NAME)

# Compile the source file
$(NAME): $(SRC)
	@make -C $(LIBFTPRINTF_DIR) > /dev/null
	$(CC) $(WFLAGS) -o $(NAME) $(SRC) -L$(LIBFTPRINTF_DIR) -lftprintf -I$(LIBFTPRINTF_DIR)
	@echo -e $(CURSIVE)$(GREEN) '\t- BUILD SUCCESS!' $(NONE)

# Clean the generated files
clean:
	rm -f $(NAME)
	@make -C $(LIBFTPRINTF_DIR) clean
	@echo -e $(CURSIVE)$(RED) '\t- CLEAN SUCCESS!' $(NONE)

# Clean the generated files and the executable
fclean: clean
	@make -C $(LIBFTPRINTF_DIR) fclean
	@echo -e $(CURSIVE)$(RED) '\t- FCLEAN SUCCESS!' $(NONE)

# Rebuild the project
re: fclean all

# Build with debug symbols
debug: WFLAGS += $(DFLAGS)
debug: $(NAME)
	@echo -e $(CURSIVE)$(GREEN) '    DEBUG - BUILD SUCCESS!' $(NONE)

# Run valgrind with specific parameters
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pipex pipex.h "cat -e" "nonexistingcommand" "outfile"

.PHONY: all clean fclean re debug valgrind
