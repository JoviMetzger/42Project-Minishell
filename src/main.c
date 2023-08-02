/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 09:45:12 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/08/02 12:13:41 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* first_check();
 *	- This function checks if the program is run without any 
 *	  command-line arguments (only ./minishell).
 */
static void	first_check(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		printf(RED "!" RESET " This program does not accept arguments" \
				RED "!\n" RESET);
		exit(0);
	}
}

/* main();
 *	- Parameters:
 *		- int argc: the argument count;
 *		- char **argv: the argument value;
 *		- char **envp: the environment;
 *
 *	- The main function is the entry point of the minishell program.
 *	- It first checks if the provided argument count 'argc' is correct 
 *	  using first_check().
 *	- The original environment variables are assigned to 'envp'.
 *	- The 'env' struct is initialized by splitting the environment variables 
 *	  into name and value pairs using init_env().
 *	- The 'status' variable is initialized to 0, as the initial exit status 
 *	  is set to 0.
 *	- The program enters a while loop that keeps running until 
 *	  the program is exited.
 *	- In each iteration:
 *		- The 'prompt' is assigned the custom prompt (minishel ➔ ) 
 *		  string using display_prompt().
 *		- The program handles the SIGQUIT or SIGINT (ctr-\, ctr-C) signal 
 *		  using handle_signal(1).
 *		- The user input is obtained using readline() with 
 *		  the custom prompt 'prompt'.
 *		- If the input is NULL (EOF), the program exits (ctr-D).
 *		- If the input is not empty, the command is added to 
 *		  the history using add_history(), allowing the user to use arrow keys 
 *		  to access previous commands.
 *		- The actual execution of the command is done in ft_commands().
 *	- The main function returns 0 to indicate successful execution.
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	all;
	char	*prompt;

	first_check(argc, argv);
	all.envp = envp;
	all.env = init_env(envp);
	all.status = 0;
	while (1)
	{
		prompt = display_prompt();
		handle_signal(1, &all);
		all.input = readline(prompt);
		ft_free(prompt);
		if (all.input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (all.input[0] != '\0')
			add_history(all.input);
		ft_commands(all.envp, &all);
		free(all.input);
	}
	return (0);
}
