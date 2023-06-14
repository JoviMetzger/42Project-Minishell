/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/14 10:34:55 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libaries
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

// Defining Colors
# define RED     "\033[31m"
# define BOLD    "\033[1m"
# define RESET	 "\033[0m"

// Structs for token
enum type
{
	EMPTY,
	CMD,
	ARG,
	PIPE,
	INFILE,
	OUTFILE,
	AT,
	INPUT_REDIRECTION,
	OUTPUT_REDIRECTION,
	APPEND_REDIRECTION,
	HERE_DOCUMENT,
	ENV_VAR,
};

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}t_token;

// Struct for history
typedef struct s_history
{
	char		*oneline;
	int			index;
	struct s_history	*next;
}t_history;

// Struct for command
typedef struct s_cmd
{
	int				index;
	char			**words;
	struct s_cmd	*next;
}t_cmd;

// Function declaration
int         ft_strcmp(char *s1, char *s2);
int			quote_count(char *str, int i,int *quo_nb, char quo);
int 		strlen_char(char *str, char c);
int			quote_check(char *str);
int         printf_history(t_history *data);
void        display_prompt();
void        handle_sig_d(int signal);
void        ft_signal_handler(int sig);
void        create_history(char *str, t_history **data);
void        ft_pwd();
void		add_token_end(t_token **top, t_token *new);
t_history   *create_newnode(char *str);
t_token		*new_token(char *str);
t_token		*split_token(char *str);
t_token		*tokenized(char *str);

#endif