/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/08 13:56:38 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

// Defining Others
# define MAX_TOKENS 100

typedef enum 
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    APPEND_REDIRECTION,
    HERE_DOCUMENT,
    PIPE,
    WORD,
} t_token_type;

typedef struct s_token_t
{
    char			*value;
    t_token_type	type;
} t_token_t;

typedef struct s_history
{
	char                *oneline;
	int                 index;
	struct s_history	*next;
}	t_history;


int         ft_strcmp(char *s1, char *s2);
void        display_prompt();
void        handle_sig_d(int signal);
void        ft_signal_handler();
t_history   *create_newnode(char *str);
void        create_history(char *str, t_history **data);
int         printf_history(t_history *data);
void        ft_pwd();

#endif
