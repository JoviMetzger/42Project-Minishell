/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 10:48:39 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 11:04:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_status;
static void new_line(int signal)
{
    g_status = 128 + signal;
    rl_on_new_line();
}

static void restore_prompt(int signal)
{
    g_status = 128 + signal;
    ft_putchar_fd('\n', STDOUT_FILENO);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void signals_wait()
{
    signal(SIGINT, restore_prompt);
    signal(SIGQUIT, SIG_IGN);
}

void signals_run()
{
    signal(SIGINT, new_line);
    signal(SIGQUIT, new_line);
}

// static void new_line(int signal, int *status)
// {
//     *status = 128 + signal;
//     rl_on_new_line();
// }

// static void restore_prompt(int signal, int *status)
// {
//     *status = 128 + signal;
//     ft_putchar_fd('\n', STDOUT_FILENO);
//     rl_replace_line("", 0);
//     rl_on_new_line();
//     rl_redisplay();
// }

// void signals_wait(int *status)
// {
//     signal(SIGINT, (void (*)(int))restore_prompt);
//     signal(SIGQUIT, SIG_IGN);
//     *status = 0;
// }

// void signals_run(int *status)
// {
//     signal(SIGINT, (void (*)(int))new_line);
//     signal(SIGQUIT, (void (*)(int))new_line);
//     *status = 0;
// }