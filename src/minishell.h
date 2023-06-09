/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/12 15:24:35 by jmetzger      ########   odam.nl         */
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
enum type
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
};

// Struct for token
typedef struct s_token
{
	char				*str;
	int					type;
	int					index;
	struct s_token		*next;
	struct s_token		*prev;
} t_token;

// Struct for environment
typedef struct s_env
{
	char				*name;
	char				*value;
	bool				for_export;
	struct s_env		*next;
} t_env;

// Struct for command
typedef struct s_cmd
{
	char				**words;
	int					len;
	struct s_token		*redi;
	struct s_cmd		*next;
} t_cmd;

// main struct
typedef struct s_data
{
	int					status;
	char				*input;
	char				**envp;
	struct s_env		*env;
	struct s_cmd		*cmd;
	struct s_token		*token;
	// struct s_history	*history;
}t_data;

// -- Function declaration --
// OTHER
char    	*display_prompt();
void		ft_commands(char **envp, t_data *data);
void		ft_free(void *ptr);

// SIGNALS
void		signals_wait();
void		signals_run();
void		rl_replace_line(const char *text, int clear_undo);

// TOKEN
int			quote_check(char *str);
int			quote_count(char *str, int i,int *quo_nb, char quo);
char		*token_to_str(t_token **top);
void		tokenized(t_data *all, char **envp);
void		add_token_end(t_token **top, t_token *new);
void		swap_val(t_token **top, char **envp, t_data *all);
t_token		*new_token(char *str);
t_token		*split_token(char *str);
t_token		*copy_token(t_token *old);
t_token		*dollar_split(char *str);

// TOKEN (utils)
int 		strlen_char(char *str, char c);
int			space_len(char *str);
int			dollar_len(char *str);
int			have_dollar(char *str);

// CMD
int			cmd_len(t_token **token, int index);
void		add_cmd_end(t_cmd **top, t_cmd *new);
void		token_to_cmd(t_data *all);
t_cmd		*new_cmd(char **words, int len);
t_cmd		*ft_new_cmd(void);

// CMD (run)
int			path_index(char **envp);
char		*find_path(char *cmd, char **envp);
void		run_cmd(t_cmd *cmd, char **envp, t_data *data);

// CMD (child)
void		cmd_child(t_cmd *cmd, char **envp, t_data *data);
void		last_cmd_child(t_cmd *cmd, char **envp, t_data *data);

// FREE AND PRINT ERROR : cmd && token && str
void		print_error(char *str, int errcode);
void		free_2dstr(char **str);
void		free_token(t_token *token);
void		free_cmd(t_data *all);

// REDI
void		redi_in(t_token *redi);
void		redi_out(t_token *redi);
void		redi_app(t_token *redi);
void		redi_here_doc(t_token *redi, t_data *all, char **envp);
void		add_redirection(t_data *all);
void		do_redirection(t_cmd *cmd, t_data *all, char **envp);
void		here_doc(int out, char *limiter, t_data *all, char **envp);

// ENV
char		*find_env(t_token **token, char **envp);
char		**split_envp(char *env);
t_env		*init_env(char **envp);

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
int			ft_pwd();
int			ft_unset(char **input, t_env **head);
int			is_builtin_cmd(char *command);
bool		exec_builtin_cmd(char **input, t_data *data);

// BUILTIN (extra functions)
void		update_oldpwd(char *tmp, t_data *data);
void		update_pwd(t_data *data);
int			add_new_env_var(char *statement, t_env **head, bool export);
int			unset_var(char *name, t_env **head);

#endif