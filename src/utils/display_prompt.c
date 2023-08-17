/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 13:54:49 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/17 05:12:27 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ft_free();
 *	- Frees the memory pointed to by 'ptr' (*ptr).
 *	- Used to deallocate dynamically allocated memory in the program.
 *	- This function is aswell used to free the prompt in the 'main()' function.
 */
void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/* display_prompt();
 *	- Generates the colored prompt string for the minishell.
 *	- First I create the base part of the prompt "minishell"
 *	- Then I apply the "RED" color code to the prompt with ft_strjoin().
 *	- I add the arrow symbol to the colored prompt.
 *	- Last I apply the "RESET" color code, 
 *	  otherwise everything after the first prompt would be red.
 *	- Returns a dynamically allocated string containing the colored prompt.
 */
char	*display_prompt(void)
{
	char	*tmp2;
	char	*tmp;

	tmp2 = ft_strjoin("minishell", RED);
	tmp = ft_strjoin(tmp2, " ➔");
	ft_free(tmp2);
	tmp2 = ft_strjoin(tmp, RESET);
	ft_free(tmp);
	tmp = ft_strjoin(tmp2, "  ");
	ft_free(tmp2);
	return (tmp);
}
