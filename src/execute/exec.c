/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 14:08:40 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/12 18:54:06 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_cmd(char *token, char **envp)
{
	
}

int main(int argc, char **argv, char **envp)
{
	char *str[2];
	str[0]= "ls";
	str[1]= NULL;
	if (execve("./ls", str, envp) == -1)
		printf("not execve");
} 