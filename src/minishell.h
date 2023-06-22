/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/22 17:51:19 by yizhang       ########   odam.nl         */
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

typedef struct s_data
{
	struct s_cmd		*cmd;
	struct s_token		*token;
	struct	s_history	*history;
	char				*input;
	int					infile;
	int					outfile;
}t_data;

typedef struct s_cmd
{
	char			**words;
	int				len;
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
void		tokenized(t_data *all);
void		add_token_end(t_token **top, t_token *new);
t_token		*new_token(char *str);
t_token		*split_token(char *str);

//cmd
int		cmd_len(t_token **token, int index);
void	add_cmd_end(t_cmd **top, t_cmd *new);
t_cmd	*new_cmd(char **words, int len);
void	token_to_cmd(t_data *all);

//run
char	*find_path(char *cmd, char **envp);
int		path_index(char **envp);
void	run_cmd(t_cmd *cmd, char **envp);
void	last_cmd_child(t_cmd *cmd, char **envp);

//child
void	cmd_child(t_cmd *cmd, char **envp);

//free and print error : cmd && token && str
void	print_error(void);
void	free_2dstr(char **str);
void	free_token(t_data *all);
void	 free_cmd(t_data *all);

//void free_history(t_history *history); //
void ft_commands(char **envp, t_data *data);

#endif
