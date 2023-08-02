/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenized.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:37:57 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 22:09:39 by jmetzger      ########   odam.nl         */
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

/* tokenized();
 *	- Parameters:
 *		- t_data *all: the main data struct;
 *		- char **envp: The environment variables;
 *
 *	- Tokenize the input string, handle quotes, 
 *	  and assign appropriate token types.
 *	- The function starts with quote_check() to ensure that all quotes in 
 *	  the input string are properly balanced. 
 *		- If there is any unclosed quote, the function exits with an error.
 *	- split_token() to tokenize the input string based on spaces 
 *	  and special characters. 
 *		- This function creates a linked list of tokens.
 *	- 'all->input' is updated with the result of token_to_str(),
 *	  which converts the linked list of tokens back into a single string.
 *	- split_again_token(), splits the input string based on spaces 
 *	  and special characters.
 *	- It iterates through each token in the token linked list and checks if 
 *	  it contains a dollar sign '$' indicating a variable expansion. 
 *		- If so, dollar_split() handles variable expansion and swap_val() 
 *		  to replace the variable with its value.
 *	- ft_assign_to_enum() assigns each token to an appropriate token type 
 *	  based on its value and position in the input string.
 */
void	tokenized(t_data *all, char **envp)
{
	t_token		*curr;
	t_token		*to_tmp;
	char		*tmp;

	tmp = NULL;
	to_tmp = NULL;
	if (quote_check(all->input) == 1)
		exit (1);
	all->token = split_token(all->input);
	all->input = token_to_str(&all->token);
	all->token = split_again_token(all->input);
	curr = all->token;
	while (curr != NULL)
	{
		if (curr->str && have_dollar(curr->str) && curr->type != SQUO)
		{
			to_tmp = dollar_split(curr->str);
			swap_val(&to_tmp, envp, all);
			tmp = curr->str;
			curr->str = token_to_str(&to_tmp);
		}
		ft_assign_to_enum(curr);
		curr = curr->next;
	}
}
