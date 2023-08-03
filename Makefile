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

NAME		= minishell
LIBFT		= ./libft/libft.a
CC			= gcc
CFLAGS		= -Werror -Wall -Wextra -g
Include	= -lreadline

SRC			= ./src/main.c \
				./src/display_prompt.c \
				./src/command.c \
				./src/tokenized/split_token.c\
				./src/tokenized/token_util.c \
				./src/tokenized/tokenized.c\
				./src/execute/run.c\
				./src/execute/create_cmd.c\
				./src/execute/find_path.c\
				./src/execute/redirection.c\
				./src/execute/redi_here_doc.c\
				./src/execute/open_pipe.c\
				./src/env/find_env.c\
				./src/env/handle_dollar_sign.c\
				./src/tool/free_error.c\
				./src/tool/protection.c\
				./src/tool/tool_utils.c\
				./src/builtin/builtin_cmd.c \
				./src/builtin/ft_cd.c \
				./src/builtin/ft_echo.c \
				./src/builtin/ft_env.c \
				./src/builtin/ft_exit.c \
				./src/builtin/ft_export.c \
				./src/builtin/ft_pwd.c \
				./src/builtin/ft_unset.c \
				./src/builtin/utils.c \
				./src/env/init_env.c \
				./src/env/env_list.c \
				
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