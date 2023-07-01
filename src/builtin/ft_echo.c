/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:40 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/01 17:49:29 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int static ft_argc(char **input)
{
    int len;
    
    len = 0;
    while (input[len])
        len++;
    return (len);
}

void ft_echo(char **input)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (ft_argc(input) > 1)
    {
        while (input[i] && ft_strcmp(input[i], "-n") == 0)
        {
            n = 1;
            i++;
        }
        if (input[i])
        {
            printf("%s", input[i]);
            i++;
        }
        while (input[i])
        {
            printf(" %s", input[i]);
            i++;
        }
        if (n == 0)
            printf("\n");
    }
}

// // ---MAIN-------------
// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] != '\0' || s2[i] != '\0')
// 	{
// 		if (s1[i] == s2[i])
// 			i++;
// 		else if (s1[i] > s2[i])
// 			return (1);
// 		else
// 			return (-1);
// 	}
// 	return (0);
// }

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char *input[] = {"echo", "-n", "hello", NULL};
//     ft_echo(input);
//     return (0);
    
// }

