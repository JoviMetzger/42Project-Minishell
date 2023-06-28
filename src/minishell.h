/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/28 11:02:05 by jmetzger      ########   odam.nl         */
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
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}   t_token;

// Struct for history
typedef struct s_history
{
	char                *oneline;
	int                 index;
	struct s_history    *next;
}   t_history;

// Struct for command
typedef struct s_cmd
{
	char			**words;
	int				len;
	struct s_cmd	*next;
}t_cmd;

// Struct for environment
typedef struct s_env
{
	char            *name;
	char            *value;
    struct s_env    *next;
}   t_env;


// main struct
typedef struct s_data
{
	struct s_cmd		*cmd;
	struct s_token		*token;
	struct	s_history	*history;
	struct s_env		*env;
	char				*input;
	int					infile;
	int					outfile;
} t_data;

// -- Function declaration --
// OTHER
int         ft_strcmp(char *s1, char *s2);
void        display_prompt();

// HISTORY
int         printf_history(t_history *data);
void		create_history(t_data *all);

// SIGNALS
// void        ft_signal_handler();
void signals_wait_cmd(void);
void signals_run_cmd(void);

// TOKEN
int			quote_count(char *str, int i,int *quo_nb, char quo);
int 		strlen_char(char *str, char c);
int			quote_check(char *str);
void		add_token_end(t_token **top, t_token *new);
t_history   *create_newnode(char *str);
t_token		*new_token(char *str);
t_token		*split_token(char *str);
void		tokenized(t_data *all);

// CMD
int		cmd_len(t_token **token, int index);
void	add_cmd_end(t_cmd **top, t_cmd *new);
t_cmd	*new_cmd(char **words, int len);
void	token_to_cmd(t_data *all);
char	*find_path(char *cmd, char **envp);
int		path_index(char **envp);
void	run_cmd(t_cmd *cmd, char **envp);
void	last_cmd_child(t_cmd *cmd, char **envp);
void	cmd_child(t_cmd *cmd, char **envp);

// ENV
void env_init(t_env *env_list, char **input);
void free_env(t_env *env);
char *expand_env_vars(const char *input, t_env *env_list);

// BUILTIN
void        ft_cd(char **arg);
void        ft_echo(char **input);
void        ft_env(t_env *env);
void        ft_exit(char **argv);
void        ft_export(char **arg);
void        ft_pwd();
void        ft_unset(char **arg);

// FREE AND PRINT_ERROR: cmd && token && str
void	print_error(void);
void	free_2dstr(char **str);
void	free_token(t_data *all);
void	 free_cmd(t_data *all);

// EXEXUTE
void ft_commands(char **input, t_data *all);
void    exec_builtin_cmd(char **input);
//void    exec_builtin_cmd(char **input) ; //, t_data *data);

#endif