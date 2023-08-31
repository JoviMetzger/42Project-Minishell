# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yizhang <yizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/22 12:30:01 by yizhang       #+#    #+#                  #
#    Updated: 2023/07/13 10:41:08 by yizhang       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Executable
NAME		= minishell

# Libraries
LIBFT		= ./libft/libft.a

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -g #-fsanitize=address
CFLAGS		+= -Werror

# Readline Files
INC_FILE	= -I includes -I $(HOME)/.brew/Cellar/readline/8.2.1/include
Include		= -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
mute		= -Wno-unused-command-line-argument

# Sources files
SRC			= ./src/main.c \
				./src/utils/command.c \
				./src/utils/display_prompt.c \
				./src/utils/signals.c \
				./src/tokenized/quote_utils.c \
				./src/tokenized/split_token_utils.c \
				./src/tokenized/split_token.c \
				./src/tokenized/syntax_error.c \
				./src/tokenized/token_util.c \
				./src/tokenized/tokenized_utils.c \
				./src/tokenized/tokenized.c \
				./src/execute/create_cmd.c \
				./src/execute/find_path.c \
				./src/execute/redi_here_doc.c \
				./src/execute/redirection.c \
				./src/execute/run.c \
				./src/builtin/builtin_cmd.c \
				./src/builtin/ft_cd.c \
				./src/builtin/ft_echo.c \
				./src/builtin/ft_env.c \
				./src/builtin/ft_exit.c \
				./src/builtin/ft_export.c \
				./src/builtin/ft_pwd.c \
				./src/builtin/ft_unset.c \
				./src/builtin/utils.c \
				./src/env/dollar_split_utils.c \
				./src/env/find_env.c \
				./src/env/handle_dollar_sign.c \
				./src/env/env_list.c \
				./src/env/init_env.c \
				./src/env/get_envp.c \
				./src/tool/free_error.c \
				./src/tool/print_error.c \
				./src/tool/protection.c \
				./src/tool/tool_utils.c \



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
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(Include) $(mute) -o $(NAME)
		@echo "$(CORAL) $(UNDER) $(BOLD) $(ITALIC) ✨Compilation Done✨   $(RESET)"

$(LIBFT): 
		@$(MAKE) -C ./libft

$(OBJDIR)/%.o: ./src/%.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) $(INC_FILE) $(Include) $(mute) -c -o $@ $<

$(OBJDIR)/%.o: ./src/utils/%.c
		$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/tokenized/%.c
		$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/builtin/%.c
		$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/execute/%.c
		$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/env/%.c
		$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/tool/%.c
		$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
		@$(MAKE) clean -C ./libft
		@rm -rf $(OBJDIR)
		@echo "$(GREEN) $(ITALIC) ✅ Cleaned object files ✅$(RESET)"

fclean: clean
		@$(MAKE) fclean -C ./libft
		@rm -f $(NAME)
		@echo "$(GREEN) $(ITALIC)   ✅ Cleaned executer ✅$(RESET)"

re:		fclean all

.PHONY: all clean fclean re

run: all
	./minishell
	
