/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/19 11:23:52 by yizhang       ########   odam.nl         */
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
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

// Defining Colors
# define RED     "\033[31m"
# define RESET	 "\033[0m"

enum
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
	DQUO,
	SPACES,
};

// Struct for environment
typedef struct s_env
{
	char				*name;
	char				*value;
	bool				for_export;
	struct s_env		*next;
} t_env;

typedef struct s_data
{
	struct s_env		*env;
	struct s_cmd		*cmd;
	struct s_token		*token;
	int					status;
	char				*input;
	pid_t				*id;
	int					cmd_len;
	int					tmp_fd;
	int					tmp_out;
	int					tmp_in;
}t_data;

typedef struct s_cmd
{
	char			**words;
	int				index;
	int				len;
	int				fd_in;
	int				fd_out;
	struct s_token	*redi;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}t_token;

int			ft_strcmp(char *s1, char *s2);

//yixin
int			quote_check(char *str);
int			quote_count(char *str, int i, int *quo_nb, char quo);
int			strlen_char(char *str, char c);

//token
void		tokenized(t_data *all);
void		add_token_end(t_token **top, t_token *new);
t_token		*new_token(char *str);
t_token		*split_token(char *str);
t_token		*copy_token(t_token *old);
int			split_redi(char *str, int i, char c, t_token **top);
int			split_char(char *str, int i, t_token **top, char c);
void		check_token(t_data *all);
int			space_len(char *str);
int			split_general_char(char *str, int i, t_token **top);
int			split_with_quote(char *str, int i, char c, t_token **top);
int			split_without_quote(char *str, int i, char c, t_token **top);
int			split_spaces_char(char *str, int i, t_token **top);
int			dollar_split_dollar(char *str, int i, t_token **top);
void		give_token_type(t_data *all);
t_token		*delspace_jointoken(t_token ** token, char **envp, t_data *all);

//cmd
int			cmd_len(t_token **token, int index);
void		add_cmd_end(t_cmd **top, t_cmd *new);
void		token_to_cmd(t_data *all);
t_cmd		*new_cmd(char **words, int len);
t_cmd		*ft_new_cmd(void);

//run
char		*find_path(char *cmd, char **envp);
int			path_index(char **envp);
void		run_cmd(t_cmd *cmd, char **envp, t_data *all);

//child
int			cmd_child(t_cmd *cmd, char **envp, t_data *all);

//free and print error : cmd && token && str
void		print_error(char *str, int errcode, t_data *all);
void		free_2dstr(char **str);
void		free_token(t_token *token);
void		free_cmd(t_data *all);
void		free_all(t_data *all);

//protect
int			protect_waitpid(pid_t id, int *status, int options, t_data *all);
void		protect_dup2(int file, int file2, t_data *all);
void		protect_close(int file, t_data *all);
void		protect_write(int fd, char *buf, int count, t_data *all);
int			protect_pipe(int fd[2], t_data *all);

//redi
int			redi_in(t_cmd *cmd, t_token *redi, t_data *all);
int			redi_out(t_cmd *cmd, t_token *redi, t_data *all);
int			redi_app(t_cmd *cmd, t_token *redi, t_data *all);
int			redi_here_doc(t_cmd *cmd, t_token *redi, t_data *all, char **envp);
void		add_redirection(t_data *all);
void		do_redirection(t_cmd *cmd, t_data *all, char **envp);
void		here_doc(int out, char *limiter, t_data *all, char **envp);

//env
int			all_upper(char *str);
int			env_index(t_token *token, char **envp);
char		*find_env(t_token **token, char **envp);

//dollar
t_token		*dollar_split(char *str, int quo);
int			dollar_len(char *str);
int			non_dollar_len(char *str, int quo);
int			have_dollar(char *str);
int			space_len(char *str);
void		swap_val(t_token **top, char **envp, t_data *all);
char		*token_to_str(t_token **top);
void		dollar_swap_val(t_token **curr, char **envp, t_data *all);
char		*add_str_to_strend(char *lang_str, char *str);
int			dollar_split_nondollar(char *str, int i, t_token **top, int quo);
char		*find_env_swap_dollar(t_data *all, char *swap_str,
				char **envp, int quo);

//void free_history(t_history *history); //
void		ft_commands(t_data *data);
void		fork_loop(t_data *all);
//tool
int			ft_isspace(char c);

//pipe
void		free_fd_2d(int **fd_2d);
int			init_pipe(t_data *all, t_cmd *cmd, int **fd_2d);
int			open_pipe(t_data *all);
int			redi_loop(t_cmd **top, t_data *all, char **envp);
int			close_all_fd(t_cmd **top, t_data *all);


//-----------JOVI_FUNCTIONS--------------
// OTHER
int			ft_argc(char **input);
char		*display_prompt(void);
void		ft_free(void *ptr);

// SIGNALS
void		handle_signal(int sig, t_data *data);
void		rl_replace_line(const char *text, int clear_undo);

// ENVIRONMENT
char		**ft_get_envp(t_env *env);
char		**split_envp(char *env);
t_env		*init_env(char **envp);

// ENVIRONMENT (linked-list)
void		env_lstadd_back(t_env **head, t_env *new);
t_env		*env_lstlast(t_env *lst);
t_env		*env_lstnew(char *name, char *value, bool export);

// BUILTIN COMMANDS
int			ft_cd(char *path, t_data *data);
int			ft_echo(char **input);
int			ft_env(t_data *data);
int			ft_exit(char **input, t_data *data);
int			ft_export(char **input, t_data *data);
int			ft_pwd(void);
int			ft_unset(char **input, t_env **env);
int			is_builtin_cmd(char *command);
bool		exec_builtin_cmd(char **input, t_data *data);

// BUILTIN COMMANDS (extra functions)
int			ft_is_digit(char *str);
int			add_new_env_var(char *statement, t_env **env, bool export);
int			unset_var(char *name, t_env **env);


void		leaks(void);
#endif
