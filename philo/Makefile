# Makefile for philosophers

# Executable name
NAME		=	philo

# Source directories
SRC_DIR		=	src


# Other directories
OBJ_DIR		=	obj
INCLUDE_DIR	=	include
HEADERS		=	$(INCLUDE_DIR)/philosophers.h

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE_DIR)

# Remove command
RM			=	rm -rf

# Source files
SRC 		=	main.c \
				utils.c

# Object files
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Compile individual source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Target rules
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Create directories for object files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re