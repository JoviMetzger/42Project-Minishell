/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 16:38:38 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/07/01 16:07:55 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_unset(char **input, char **envp)
{
    int i;
    int j;
    int key_len;
    
    if (input[1] != NULL) 
    {
        i = 0;
        j = 0;
        key_len = ft_strlen(input[1]);
        while (envp[i] != NULL) 
        {
            if (ft_strncmp(envp[i], input[1], key_len) == 0 && envp[i][key_len] == '=') 
                free(envp[i]);
            else 
                envp[j++] = envp[i];
            i++;
        }
        envp[j] = NULL;
    }
}



// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
    
//     // Seting an new environment variable whit ft_export"
//     char *export_input[] = 
//     {
//         "export",
//         "VAR2=anothervalue",
//         NULL
//     };
//     ft_export(export_input, envp);
//     printf("\n");

//     printf("\n\n");
//     ft_env(envp); // Print the updated environment variables

//     printf("\n\nTEST\n\n");
//     // Test ft_unset() with an existing environment variable
//     char *unset_input[] = {
//         "unset",
//         "VAR2",
//         NULL
//     };
//     ft_unset(unset_input, envp);
//     printf("\n");

//     // Print the updated environment variables
//     printf("\n\n");
//     ft_env(envp);

//     return (0);
// }


// void ft_export(char **input, char **envp)
// {
//     char *key_value;
//     char *key;
//     char *value;
//     int i;
//     int j;
    
//     if (input[1] != NULL) 
//     {
//         key_value = input[1];
//         key = (char *)malloc(sizeof(char) * (ft_strlen(key_value) + 1));
//         value = NULL;

//         i = 0;
//         while (key_value[i] != '=' && key_value[i] != '\0') 
//         {
//             key[i] = key_value[i];
//             i++;
//         }
//         key[i] = '\0';
//         if (key_value[i] == '=') 
//             value = &key_value[i + 1];

//         j = 0;
//         while (envp[j] != NULL) 
//         {
//             if (ft_strncmp(envp[j], key, ft_strlen(key)) == 0 && envp[j][ft_strlen(key)] == '=') 
//             {
//                 free(envp[j]);
//                 envp[j] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
//                 ft_strcpy(envp[j], key);
//                 ft_strcat(envp[j], "=");
//                 ft_strcat(envp[j], value);
//                 break ;
//             }
//             j++;
//         }

//         if (envp[j] == NULL) 
//         {
//             envp[j] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
//             ft_strcpy(envp[j], key);
//             ft_strcat(envp[j], "=");
//             ft_strcat(envp[j], value);
//             envp[j + 1] = NULL;
//         }
//         free(key);
//     } 
//     else 
//     {
//         i = 0;
//         while (envp[i] != NULL) 
//         {
//             printf("%s\n", envp[i]);
//             i++;
//         }
//     }
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