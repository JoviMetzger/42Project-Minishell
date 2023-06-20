/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/20 17:38:56 by yizhang       ########   odam.nl         */
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

typedef struct s_history
{
	char		*oneline;
	int			index;
	struct s_history	*next;
}t_history;

typedef struct s_cmd
{
	char			**words;
	int				len;
	int				out;
	int				in;
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
void		create_history(char *str, t_history **data);
int			printf_history(t_history *data);
t_history	*create_newnode(char *str);
int			quote_check(char *str);
int			quote_count(char *str, int i,int *quo_nb, char quo);
int 		strlen_char(char *str, char c);

//token
t_token		*tokenized(char *str);
void		add_token_end(t_token **top, t_token *new);
t_token		*new_token(char *str);
t_token		*split_token(char *str);

//cmd
int		cmd_len(t_token **token, int index);
void	add_cmd_end(t_cmd **top, t_cmd *new);
t_cmd	*new_cmd(char **words, int len);
t_cmd	*token_to_cmd(t_token **token);

//run
char	*find_path(char *cmd, char **envp);
int		path_index(char **envp);
void	run_cmd(t_cmd *cmd, char **envp);
void	last_cmd_child(t_cmd *cmd, char **envp);

//child
void	cmd_child(t_cmd *cmd, char **envp);

//free cmd && token && str

//void free_history(t_history *history); //
void ft_commands(char *input, char **envp, t_history *data);

#endif
