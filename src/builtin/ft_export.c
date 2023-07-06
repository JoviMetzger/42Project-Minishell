/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:11 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/06 10:48:31 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_export(char **input, char **envp)
{
    char *key_value;
    char *key;
    char *value;
    int i;
    int j;
    
    if (input[1] != NULL) 
    {
        key_value = input[1];
        key = (char *)malloc(sizeof(char) * (ft_strlen(key_value) + 1));
        value = NULL;

        i = 0;
        while (key_value[i] != '=' && key_value[i] != '\0') 
        {
            key[i] = key_value[i];
            i++;
        }
        key[i] = '\0';
        if (key_value[i] == '=') 
            value = &key_value[i + 1];

        j = 0;
        while (envp[j] != NULL) 
        {
            if (ft_strncmp(envp[j], key, ft_strlen(key)) == 0 && envp[j][ft_strlen(key)] == '=') 
            {
                free(envp[j]);
                envp[j] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
                ft_strcpy(envp[j], key);
                ft_strcat(envp[j], "=");
                ft_strcat(envp[j], value);
                break ;
            }
            j++;
        }

        if (envp[j] == NULL) 
        {
            envp[j] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
            ft_strcpy(envp[j], key);
            ft_strcat(envp[j], "=");
            ft_strcat(envp[j], value);
            envp[j + 1] = NULL;
        }
        free(key);
    } 
    else 
    {
        i = 0;
        while (envp[i] != NULL) 
        {
            printf("declare -x %s\n", envp[i]);
            i++;
        }
    }
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
    
//     ft_env(envp); // Print the environment variables
//     printf("\n\n");
    
//     // Test ft_export() with a new environment variable
//     char *export_input[] = {
//         "export",
//         "VAR1=newvalue",
//         NULL
//     };
//     ft_export(export_input, envp);
//     printf("\n");

//     // Test ft_export() with another new environment variable
//     char *export_input2[] = 
//     {
//         "export",
//         "VAR2=anothervalue",
//         NULL
//     };
//     printf("Testing ft_export() with another new environment variable:\n");
//     ft_export(export_input2, envp);
//     printf("\n");
    
//     // Print the updated environment variables
//     printf("\n\n");
//     ft_env(envp);
//     return (0);
// }

// char	*ft_strcat(char *dest, char *src)
// {
// 	int	i;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	while (dest[i] != '\0')
// 	{
// 		i++;
// 	}
// 	while (src[k] != '\0')
// 	{
// 		dest[i + k] = src[k];
// 		k++;
// 	}
// 	dest[i + k] = '\0';
// 	return (dest);
// }

// char	*ft_strcpy(char *dest, char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// int	ft_strncmp(const char *str1, const char *str2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((str1[i] != '\0' || str2[i] != '\0') && (i < n))
// 	{
// 		if (str1[i] == str2[i])
// 			i++;
// 		else if (str1[i] > str2[i])
// 			return (1);
// 		else
// 			return (-1);
// 	}
// 	return (0);
// }

// void ft_env(char **envp)
// {
//    int i;

//    i = 0;
//    while (envp[i] != NULL)
//    {
//       printf("%s\n", envp[i]);
//       i++;
//    }
// }