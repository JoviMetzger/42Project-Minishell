/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/01 13:26:55 by jmetzger      ########   odam.nl         */
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
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

// Defining Colors
# define RED     "\033[31m"
# define RESET	 "\033[0m"

// Structs for token
enum type
{
	EMPTY,
	WORD,
	PIPE,
	INPUT_RE,
	INFILE,
	OUTPUT_RE,
	OUTFILE,
	AT,
	APPEND_RE,
	APPFILE,
	HERE_DOCUMENT,
	DELIMITER,
	ENV_VAR,
};

typedef struct s_token
{
	char				*str;
	int					type;
	int					index;
	struct s_token		*next;
	struct s_token		*prev;
} t_token;

// Struct for history
typedef struct s_history
{
	char				*oneline;
	int					index;
	struct s_history	*next;
} t_history;


// Struct for command
typedef struct s_cmd
{
	char				**words;
	int					len;
	struct s_history	*history;
	struct s_cmd		*next;
	struct s_token		*redi;
} t_cmd;

// main struct
typedef struct s_data
{
	struct s_cmd		*cmd;
	struct s_token		*token;
	char				*input;
} t_data;

// -- Function declaration --
// OTHER
char    	*display_prompt();
void		ft_commands(char **envp, t_data *data);
void		ft_free(void *ptr);

// HISTORY
int			printf_history(t_history *data);
void		create_history(t_data *all);
t_history	*create_newnode(char *str);

// SIGNALS
void		signals_wait(void);
void		signals_run(void);

// TOKEN
int			quote_check(char *str);
int			quote_count(char *str, int i,int *quo_nb, char quo);
int 		strlen_char(char *str, char c);
void		tokenized(t_data *all);
void		add_token_end(t_token **top, t_token *new);
t_token		*new_token(char *str);
t_token		*split_token(char *str);
t_token		*copy_token(t_token *old);

// CMD
int			cmd_len(t_token **token, int index);
void		add_cmd_end(t_cmd **top, t_cmd *new);
void		token_to_cmd(t_data *all);
t_cmd		*new_cmd(char **words, int len);
t_cmd		*ft_new_cmd(void);

// RUN
int			path_index(char **envp);
char		*find_path(char *cmd, char **envp);
void		run_cmd(t_cmd *cmd, char **envp);

// CHILD
void		cmd_child(t_cmd *cmd, char **envp);
void		last_cmd_child(t_cmd *cmd, char **envp);

// FREE AND PRINT ERROR : cmd && token && str
void		print_error(char *str);
void		free_2dstr(char **str);
void		free_token(t_data *all);
void		free_cmd(t_data *all);

// REDI
void		redi_in(t_token *redi);
void		redi_out(t_token *redi);
void		redi_app(t_token *redi);
void		add_redirection(t_data *all);
void		do_redirection(t_cmd *cmd);

// BUILTIN
void        ft_cd(char *path);
void        ft_echo(char **input);
void		ft_env(char **envp);
void        ft_exit(char **input);
void		ft_export(char **input, char **envp);
void        ft_pwd();
void		ft_unset(char **input, char **envp);
void		exec_builtin_cmd(char **input, char **envp);
int			is_builtin_cmd(char *command);

#endif