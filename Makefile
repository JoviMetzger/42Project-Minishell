# Executable
NAME		= minishell

# Libraries
LIBFT		= ./libft/libft.a

# Compiler and flags
CC			= gcc
CFLAGS		= -Wall -Wextra -g #-fsanitize=address
# CFLAGS		+= -Werror

# Readline Files
# INC_FILE	= -I includes -I $(HOME)/.brew/Cellar/readline/8.2.1/include
# Include	= -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
Include	= -lreadline

# Sources files
SRC			= ./src/main.c \
				./src/display_prompt.c \
				./src/command.c \
				./src/create_history.c \
				# ./src/history.c

# Objects files
OBJ			= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

# Object Directory
OBJDIR 		= obj

# Colors
BOLD		= \033[1m
ITALIC		= \033[3m
UNDER 		= \033[4m
GREEN		= \033[32;1m
INDIGO		= \033[38;2;75;0;130m
CORAL		= \033[38;2;255;127;80m
RESET		= \033[0m

# Targets
all:		$(NAME)

$(NAME): $(LIBFT) $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(Include) -o $(NAME)
		@echo "$(CORAL) $(UNDER) $(BOLD) $(ITALIC) ✨Compilation Done✨   $(RESET)"

$(LIBFT): 
		@$(MAKE) -C ./libft

$(OBJDIR)/%.o: ./src/%.c
		@mkdir -p $(OBJDIR)
		@$(CC) $(CFLAGS) $(INC_FILE) $(Include) -c -o $@ $^

# Clean
clean:
		$(MAKE) clean -C ./libft
		@rm -rf $(OBJDIR)
		@echo "$(GREEN) $(ITALIC) ✅ Cleaned object files ✅$(RESET)"

fclean: clean
		@$(MAKE) fclean -C ./libft
		@rm -f $(NAME)
		@echo "$(GREEN) $(ITALIC)	  ✅ ✅ ✅$(RESET)"

re:		fclean all

.PHONY: all clean fclean re