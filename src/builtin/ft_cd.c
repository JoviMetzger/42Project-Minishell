/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:37:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/28 16:23:46 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// chdir();
//  used to change the current working directory of the calling process.
void ft_cd(char *path)
{
    const char *home;
    int result;
    
    if (path == NULL)
    {
        home = getenv("HOME");
        if (home != NULL)
            chdir(home);
    }
    else
    {
        result = chdir(path);
        if (result != 0)
            perror("cd");
    }
}

// // ---MAIN-------------

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char cwd[256]; 
    
//     printf("%s\n", getcwd(cwd, sizeof(cwd)));
//     ft_cd("path"); 
//     printf("%s\n", getcwd(cwd, sizeof(cwd))); 
//     return 0;
// }