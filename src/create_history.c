/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_history.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:06:01 by yizhang       #+#    #+#                 */
/*   Updated: 2023/06/06 15:54:47 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*create_newnode(char *str)
{
	t_history *newnode;


	newnode = malloc(sizeof(t_history));
	if (!newnode)
		return (NULL);
	newnode->oneline = str;
	newnode->index = 1;
	newnode->next = NULL;
	return (newnode);
}

void	create_history(char *str, t_history **data)
{
	t_history	*tmp;
	int			i;

	tmp = *data;
	i = 2;
	if (!tmp)
	{
		*data = create_newnode(str);
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp  = tmp->next;
		i++;
	}
	tmp->next = create_newnode(str);
	tmp->next->index = i;
}

int	printf_history(t_history *data)
{
	t_history *tmp;

	tmp = data;
	while (tmp->next != NULL)
	{
		printf("    %i  %s\n",tmp->index, tmp->oneline);
		tmp = tmp->next;
	}
	return (0);
}

// this is the test for this funtion
/* int main (void)
{
	t_history *data;
	
	data = NULL;
	//data=create_newnode("char *str");
	create_history("safaaafh", &data);
	create_history("sss", &data);
	create_history("ccc", &data);
	create_history("cccdd", &data);
	create_history("safdkfh", &data);
	printf_history(data);
	return (0);
} */