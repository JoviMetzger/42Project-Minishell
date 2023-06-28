/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 13:06:54 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/24 18:18:44 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_init(t_env *env_list, char **input)
{
    char *output = expand_env_vars(*input, env_list);
    printf("Output: %s\n", output); 
    
}

// void free_env(t_env *env)
// {
    
// }

char *get_env_value(char *arg, t_env *env_list)
{
    t_env *current = env_list;
    while (current != NULL)
    {
        if (ft_strcmp(arg, current->value) == 0)
            return (getenv(arg));
        current = current->next;
    }
    return (NULL);
}

char *expand_env_vars(const char *input, t_env *env_list) 
{
    char *result = NULL;
    char *token = NULL;
    char *rest = NULL;
    const char *delimiters = "$";
    
    token = strtok_r((char *)input, delimiters, &rest);
    
    while (token != NULL) 
    {
        if (token[0] == '\0') 
        {
            token = strtok_r(NULL, delimiters, &rest);
            continue;
        }
        
        if (token[0] == '$') 
        {
            char *env_name = token + 1;  // Skip the '$' character
            char *env_value = get_env_value(env_name, env_list);
            
            if (env_value != NULL) 
            {
                size_t result_len = result ? strlen(result) : 0;
                size_t env_value_len = strlen(env_value);
                
                result = realloc(result, result_len + env_value_len + 1);
                strcat(result, env_value);
            }
        } 
        else 
        {
            size_t result_len = result ? strlen(result) : 0;
            size_t token_len = strlen(token);
            
            result = realloc(result, result_len + token_len + 1);
            strcat(result, token);
        }
        
        token = strtok_r(NULL, delimiters, &rest);
    }
    
    return (result);
}

// // ---------------

// int main() 
// {
//     t_env *env_list = NULL;
    
//     t_env *env_var = malloc(sizeof(t_env));
//     env_var->value = "USER";
//     env_var->next = NULL;
//     env_list = env_var;
    
//     const char *input = "Hello, $USER!";  
//     char *output = expand_env_vars(input, env_list);
    
//     printf("Output: %s\n", output); 
    
//     free(output);
//     free(env_var);
    
//     return 0;
// }