/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/13 10:21:45 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fork_loop(t_data *all)
{
	t_cmd	*curr;
	char	**envp;

	envp = ft_get_envp(all->env);
	curr = all->cmd;
	while (curr)
	{
		if (cmd_child(curr, envp, all) == -1)
			break ;
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	close(all->tmp_fd);
	close(all->tmp_out);
}

int	redi_loop(t_cmd **top, t_data *all, char **envp)
{
	t_cmd	*curr;

	curr = *top;
	(void)envp;
	(void)all;
	while (curr)
	{
		if (!curr->next)
			return (0);
		curr = curr->next;
	}
	return (0);
}

int	close_all_fd(t_cmd **top, t_data *all)
{
	t_cmd	*curr;

	curr = *top;
	while (curr)
	{
		if (curr->fd_in != 0)
			protect_close(curr->fd_in, all);
		if (curr->fd_out != 1)
			protect_close(curr->fd_out, all);
		if (!curr->next)
			return (0);
		curr = curr->next;
	}
	return (0);
}

static void	ft_exit_status(t_data *all, int i)
{
	int	status;

	g_exit_status = syntax_error_check(all->input);
	if (g_exit_status == 258)
		return ;
	if (protect_waitpid(all->id[i], &status, 0, all) == -1)
		return ;
	if (WTERMSIG(status) == 2 || WTERMSIG(status) == 3)
		g_exit_status = WTERMSIG(status) + 128;
	else if (all->here_status == 256)
		g_exit_status = 1;
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	ft_commands(t_data *all)
{
	int	i;

	i = 0;
	if (ft_strcmp(all->input, "") != 0)
	{
		tokenized(all);
		token_to_cmd(all);
		free_token(all->token);
		all->token = NULL;
		if (all->cmd && !all->cmd->next 
			&& is_builtin_cmd_single(all->cmd->words[0]) == 1)
		{
			exec_builtin_cmd(all->cmd->words, all);
			return ;
		}
		all->id = malloc(sizeof(pid_t) * all->cmd_len);
		if (!all->id)
			return ;
		fork_loop(all);
		while (i < all->cmd_len)
		{
			ft_exit_status(all, i);
			i++;
		}
	}
}

// printf("EXITCODE: %d\n", g_exit_status);
// printf("SIGNAL: %d\n", WIFSIGNALED(status));
// printf("EXITED: %d\n", WIFEXITED(status));
// printf("SIG: %d\n", WTERMSIG(status));
// printf("STATUS: %d\n", WEXITSTATUS(status));
