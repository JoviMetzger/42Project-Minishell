/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:46 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/05 15:24:14 by jmetzger      ########   odam.nl         */
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

int	ft_strcmp(char *s1, char *s2);
void    display_prompt();
t_history	*create_history();//
void add_coomand_to_history(t_history *history, const char *input);//
void print_history(t_history *history);//
void free_history(t_history *history); //
void ft_commands(char **input, char **envp);

#endif
