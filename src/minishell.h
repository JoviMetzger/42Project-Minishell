/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/02 11:43:12 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libaries
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

// Defining Colors
# define RED     "\033[31m"
# define RESET	 "\033[0m"

// enum for token
typedef enum e_num
{
	EMPTY,
	WORD,
	PIPE,
	INPUT_RE,
	INFILE,
	OUTPUT_RE,
	OUTFILE,
	APPEND_RE,
	APPFILE,
	HERE_DOC,
	DELIMI,
	DOLLAR,
	ENV,
	SQUO,
	SPACES,
}	t_enum;

// Struct for token
typedef struct s_token
{
	char				*str;
	int					type;
	int					index;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

// Struct for environment
typedef struct s_env
{
	char				*name;
	char				*value;
	bool				for_export;
	struct s_env		*next;
}	t_env;

// Struct for command
typedef struct s_cmd
{
	char				**words;
	int					len;
	struct s_token		*redi;
	struct s_cmd		*next;
}	t_cmd;

// main struct
typedef struct s_data
{
	int					status;
	char				*input;
	char				**envp;
	struct s_env		*env;
	struct s_cmd		*cmd;
	struct s_token		*token;
}	t_data;

// -- Function declaration --
// OTHER
int			ft_argc(char **input);
int			ft_isspace(char c);
char		*display_prompt(void);
void		ft_commands(char **envp, t_data *data);
void		ft_free(void *ptr);

// SIGNALS
void		handle_signal(int sig, t_data *data);
void		rl_replace_line(const char *text, int clear_undo);

// TOKEN
int			quote_count(char *str, int i, int *quo_nb, char quo);
int			split_char(char *str, int i, t_token **top);
int			split_redi(char *str, int i, char c, t_token **top);
int			split_without_quote(char *str, int i, char c, t_token **top);
int			split_no_space(char *str, int i, t_token **top);
void		ft_assign_to_enum(t_token *curr);
void		tokenized(t_data *all, char **envp);
t_token		*split_again_token(char *str);
t_token		*split_token(char *str);

// TOKEN (utils)
int			strlen_char(char *str, char c);
void		add_token_end(t_token **top, t_token *new);
t_token		*new_token(char *str);
t_token		*copy_token(t_token *old);

// EXECUTE (cmd)
char		*find_path(char *cmd, char **envp);
void		token_to_cmd(t_data *all);
void		add_redirection(t_data *all);
void		here_doc(int out, char *limiter, t_data *all, char **envp);
void		redi_here_doc(t_token *redi, t_data *all, char **envp);
void		cmd_child(t_cmd *cmd, char **envp, t_data *data);
void		last_cmd_child(t_cmd *cmd, char **envp, t_data *data);

// EXECUTE (redi)
void		redi_in(t_token *redi);
void		redi_out(t_token *redi);
void		redi_app(t_token *redi);

// TOOL (free and print_error)
void		print_error(char *str, int errcode);
void		free_2dstr(char **str);
void		free_token(t_token *token);

// TOOL (protection)
void		protect_waitpid(pid_t id, int *status, int options);
void		protect_dup2(int file, int file2);
void		protect_close(int file);
void		protect_write(int fd, char *buf, int count);
void		protect_pipe(int fd[2]);

// ENV
char		*find_env(t_token **token, char **envp);
char		*token_to_str(t_token **top);
char		**split_envp(char *env);
t_env		*init_env(char **envp);

// ENV (dollar_sign)
int			have_dollar(char *str);
int			dollar_len(char *str);
int			space_len(char *str);
void		swap_val(t_token **top, char **envp, t_data *all);
t_token		*dollar_split(char *str);

// ENV (linked-list)
void		env_lstadd_back(t_env **head, t_env *new);
t_env		*env_lstlast(t_env *lst);
t_env		*env_lstnew(char *name, char *value, bool export);

// BUILTIN (main functions)
int			ft_cd(char *path, t_data *data);
int			ft_echo(char **input);
int			ft_env(t_data *data);
int			ft_exit(char **input, t_data *data);
int			ft_export(char **input, t_data *data);
int			ft_pwd(void);
int			ft_unset(char **input, t_env **env);
int			is_builtin_cmd(char *command);
bool		exec_builtin_cmd(char **input, t_data *data);

// BUILTIN (extra functions)
int			ft_is_digit(char *str);
int			add_new_env_var(char *statement, t_env **env, bool export);
int			unset_var(char *name, t_env **env);

#endif
