/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/04 11:29:31 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* quote_check();
 *	- Check if all quotes in the input string are properly closed.
 *	- The function uses two variables, 'd_quo' and 's_quo', 
 *	  to keep track of the count of double quotes and single quotes.
 *	- It iterates through the input, incrementing the count for each 
 *	  encountered single or double quote.
 *	- If the count of single quotes(s_quo) or double quotes(d_quo) is not even,
 *		the function exits the program with an error message.
 *	- Otherwise, it returns 0, indicating that all quotes are balanced.
 */
int	quote_check(char *str)
{
	int	i;
	int	d_quo;
	int	s_quo;

	i = 0;
	d_quo = 0;
	s_quo = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'')
			i = quote_count(str, i, &s_quo, '\'');
		if (str[i] == '\"')
			i = quote_count(str, i, &d_quo, '\"');
		i++;
	}
	if (s_quo % 2 != 0 || d_quo % 2 != 0)
	{
		printf("unclosed quote error \n");
		exit (1);
	}
	return (0);
}

/* quote_count();
 *	- Parameters:
 *		- char *str: The input string to count quotes in;
 *		- int i: index in the input string to begin counting quotes;
 *		- int *quo_nb: the variable that stores the count of quotes;
 *		- char quo: The quote character to count( '\'' or '\"');
 *
 *	- The function starts at index 'i' 
 *	  and increments the count of the quote ('quo_nb') by 1.
 *	- It then iterates through the input string from index 'i' 
 *	  and looks for the next occurrence of the quote character 'quo'.
 *	- Each time it finds a quote, 
 *	  it increments the count of the quote ('quo_nb') by 1.
 *	- When it reaches the closing quote,
 *	  it breaks out of the loop and returns the updated index 'i', 
 *	  pointing to the position just after the closing quote.
 */
int	quote_count(char *str, int i, int *quo_nb, char quo)
{
	*quo_nb += 1;
	i++;
	while (str[i])
	{
		if (str[i] == quo)
		{
			*quo_nb += 1;
			break ;
		}
		i++;
	}
	return (i);
}
