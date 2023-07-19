/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 12:31:04 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/19 11:00:51 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long long int	ft_atoll(const char *str)
{
	unsigned long long int	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
     while ((*str == ' ') || (*str == '\f')
		|| (*str == '\n') || (*str == '\r')
		|| (*str == '\t') || (*str == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i += 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i += 1;
	}
	return (result * sign);
}

int static ft_argc(char **input)
{
    int len;
    
    len = 0;
    while (input[len])
        len++;
    return (len);
}

int ft_is_digit(char *str) 
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-' && str[i] != '+')
            return (1);
        i++;
    }
    return (0);
}

bool	is_long_int(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (false);
	if (ft_strcmp("-9223372036854775808", str) == 0)
		return (true);
	out = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (false);
		out = out * 10 + c;
		str += 1;
	}
	return (true);
}

int determine_exit_code(char **str)
{
	int exit_code;
	long long int is_long;
	
	exit_code = 0;
	if (ft_is_digit(str[1]) == 0)
	{
		if (is_long_int(str[1]))
		{
			is_long = ft_atoll(str[1]);
			if (is_long >= LLONG_MIN && is_long <= LLONG_MAX)
				exit_code = ft_atoll(str[1]);
			else
				exit_code = 255;
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR_FILENO);
			exit_code = 255;
		}
	}
	else 
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	return (exit_code);	
}

int	ft_exit(char **input, t_data *data)
{	
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (ft_argc(input) > 2)
	{
		data->status = EXIT_FAILURE;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	}
	else if (ft_argc(input) == 2)
	{
		data->status = determine_exit_code(input);
	}
	else
		data->status = EXIT_SUCCESS;
	exit(data->status);
}