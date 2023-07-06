/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 15:08:29 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>//open
#include <errno.h>//errno

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

typedef struct s_history
{
	char		*oneline;
	int			index;
	struct s_history	*next;
}t_history;

typedef struct s_data
{
	char				**envp;
	struct s_cmd		*cmd;
	struct s_token		*token;
	struct	s_history	*history;
	char				*input;
}t_data;

typedef struct s_cmd
{
	char			**words;
	int				len;
	struct	s_token	*redi;
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
void		display_prompt();

//yixin
void		create_history(t_data *all);
int			printf_history(t_history *data);
t_history	*create_newnode(char *str);
int			quote_check(char *str);
int			quote_count(char *str, int i,int *quo_nb, char quo);
int 		strlen_char(char *str, char c);

//token
void		tokenized(t_data *all, char **envp);
void		add_token_end(t_token **top, t_token *new);
t_token		*new_token(char *str);
t_token		*split_token(char *str);
t_token		*copy_token(t_token *old);

//cmd
int		cmd_len(t_token **token, int index);
void	add_cmd_end(t_cmd **top, t_cmd *new);
t_cmd	*new_cmd(char **words, int len);
void	token_to_cmd(t_data *all);
t_cmd	*ft_new_cmd(void);


//run
char	*find_path(char *cmd, char **envp);
int		path_index(char **envp);
void	run_cmd(t_cmd *cmd, char **envp);

//child
void	cmd_child(t_cmd *cmd, char **envp);
void	last_cmd_child(t_cmd *cmd, char **envp);

//free and print error : cmd && token && str
void	print_error(char *str, int errcode);
void	free_2dstr(char **str);
void	free_token(t_token *token);
void	free_cmd(t_data *all);

//redi
void	redi_in(t_token *redi);
void	redi_out(t_token *redi);
void	redi_app(t_token *redi);
void	redi_here_doc(t_token *redi);
void	add_redirection(t_data *all);
void	do_redirection(t_cmd *cmd);
void	here_doc(int in, char *limiter);

//env
int		all_upper(char *str);
int		env_index(t_token *token, char **envp);
char	*find_env(t_token **token, char **envp);

//void free_history(t_history *history); //
void ft_commands(char **envp, t_data *data);

#endif
