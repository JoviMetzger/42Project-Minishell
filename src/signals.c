/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:48:39 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/06 12:59:28 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// (ctrl-C)
void handle_sig_c(int signal)
{
    (void)signal;
    display_prompt();
}

// (ctrl-\)   
void handle_sig_nothing(int signal)
{
    (void)signal;
    return ;
}

// (ctrl-D)
void handle_sig_d(int signal)
{
    (void)signal;
    printf("\n");
    exit(0);
}

void ft_signal_handler()
{ 
    signal(SIGINT, handle_sig_c);
    signal(SIGQUIT, handle_sig_nothing);
}