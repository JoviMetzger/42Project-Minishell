/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 13:55:13 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/06/05 15:00:35 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_history	*create_history()
// {
// 	t_history	*new;

// 	new = (t_history *)malloc(sizeof(t_history));
// 	if (!new)
// 		return (NULL);
// 	new->head = NULL;
// 	new->tail = NULL;
// 	return (new);
// }

// void add_coomand_to_history(t_history *history, const char *input)
// {
//     t_node *new_node = (t_node *)malloc(sizeof(t_node));
//     ft_strcpy(new_node->value, input);
//     new_node->next = NULL;
//     if (history->head == NULL)
//     {
//         history->head = new_node;
//         history->tail = new_node;
//     }
//     else
//     {
//         history->tail->next = new_node;
//         history->tail = new_node;
//     }
// }

// void print_history(t_history *history)
// {
//     t_node *current;
//     int count;
    
//     current = history->head;
//     count = 1;
//     printf("History: \n");
//     while (current != NULL)
//     {
//         printf("%d: %s\n", count, current->value);
//         current = current->next;
//         count++;
//     }
// }

// void free_history(t_history *history)
// {
//     t_node *current;
//     t_node *tmp;

//     current = history->head;
//     while (current != NULL)
//     {
//         tmp = current;
//         current = current->next;
//         free(tmp);
//     }
//     free(history);
// }