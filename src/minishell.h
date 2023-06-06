/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/06 11:42:18 by yizhang       ########   odam.nl         */
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


typedef struct s_history
{
	char		*oneline;
	int			index;
	struct s_history	*next;
}t_history;

int	ft_strcmp(char *s1, char *s2);
void    display_prompt();
void	create_history(char *str, t_history **data);
int	printf_history(t_history *data);
t_history	*create_newnode(char *str);
//void add_coomand_to_history(t_history *history, const char *input);//
//void print_history(t_history *history);//
//void free_history(t_history *history); //
void ft_commands(char **input, char **envp, t_history *data);

#endif
