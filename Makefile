# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yizhang <yizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/22 12:30:01 by yizhang       #+#    #+#                  #
#    Updated: 2023/07/06 11:35:52 by yizhang       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= ./libft/libft.a
CC			= gcc
CFLAGS		= -Werror -Wall -Wextra -g
Include	= -lreadline

SRC			= ./src/main.c \
				./src/display_prompt.c \
				./src/command.c \
				./src/create_history.c \
				./src/tokenized/split_token.c\
				./src/tokenized/token_util.c \
				./src/tokenized/tokenized.c\
				./src/execute/run.c\
				./src/execute/create_cmd.c\
				./src/execute/find_path.c\
				./src/execute/free_error.c\
				./src/execute/redirection.c\
				./src/execute/redi_here_doc.c\
				./src/env/find_env.c\
				
OBJ			= $(SRC:.c=.o)

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
		@$(MAKE) clean -C ./libft
		@rm -rf $(OBJ)
		@echo "$(GREEN) $(ITALIC) ✅ Cleaned object files ✅$(RESET)"

fclean: clean
		@$(MAKE) fclean -C ./libft
		@rm -f $(NAME)
		@echo "$(GREEN) $(ITALIC)	  ✅ ✅ ✅$(RESET)"

re:		fclean all

.PHONY: all clean fclean re