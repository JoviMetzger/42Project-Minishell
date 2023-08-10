/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 10:51:55 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/09 15:46:55 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* add_redirection();
 *	- Parameters:
 *	  - t_data *all: the main data struct;
 *
 *	- Add redirection tokens from the 'all->token' linked list to 
 *	  the corresponding commands in the 'all->cmd' linked list.
 *	- The function loops through the 'all->token' list and identifies 
 *	  the redirection tokens (INFILE, OUTFILE, APPFILE, DELIMI). 
 *		- For each redirection token, it creates a copy of the token 
 *		  and adds it to the 'redi' linked list of the current command node.
 *	- The 'redi' linked list holds the redirection tokens associated 
 *	  with each command node, allowing easy access to redirection information 
 *	  when executing the command later.
 */
void	add_redirection(t_data *all)
{
	t_token	*curr;
	t_cmd	*cmd;

	if (!all->cmd || !all->token)
		return ;
	curr = all->token;
	cmd = all->cmd;
	cmd->redi = NULL;
	while (cmd != NULL && curr != NULL)
	{
		if (curr->type == INFILE || curr->type == OUTFILE 
			|| curr->type == APPFILE || curr->type == DELIMI)
			add_token_end(&cmd->redi, copy_token(curr));
		else if (curr->type == PIPE)
			cmd = cmd->next;
		curr = curr->next;
	}
}

/* do_redirection();
 *	- Parameters:
 *	  - t_cmd *cmd: the command node whose redirections need to be executed;
 *	  - t_data *all: the main data struct;
 *	  - char **envp: the environment variables array;
 *
 *	- Execute the redirections for a command in the 'all->cmd' linked list.
 *	- The function loops through the 'cmd->redi' linked list, 
 *	  which holds the redirection tokens associated with the current command.
 *	- For each redirection token, it calls the appropriate function 
 *	  (redi_in, redi_out, redi_app, redi_here_doc) 
 *	  to perform the actual redirection based on the token type.
 */
void	do_redirection(t_cmd *cmd, t_data *all, char **envp)
{
	t_token	*redi;

	redi = cmd->redi;
	while (redi)
	{
		if (redi->type == INFILE)
			redi_in(cmd, redi);
		else if (redi->type == OUTFILE)
			redi_out(cmd, redi);
		else if (redi->type == APPFILE)
			redi_app(cmd, redi);
		else if (redi->type == DELIMI)
			redi_here_doc(cmd, redi, all, envp);
		if (!redi->next)
			return ;
		redi = redi->next;
	}
}

/* redi_in();
 *	- Parameters:
 *	  - t_token *redi: the input file redirection token;
 *
 *	- Perform input file redirection using the 'redi' token.
 *	- The function opens the input file specified in the 'redi->str' field using:
 *		- O_RDONLY: opened in read-only mode.
 *	- If the file cannot be opened, it calls the print_error() to display 
 *	  an error message and terminates the program.
 *	- The function then duplicates the file descriptor 'file' to 
 *	  the standard input (0) using 'protect_dup2'.
 *	- Finally, it closes the file descriptor 'file'.
 */
void	redi_in(t_cmd *cmd, t_token *redi)
{
	int	file;

	file = open(redi->str, O_RDONLY);
	if (file < 0)
		print_error(redi->str, 1);
	cmd->fd_in = file;
}

/* redi_out();
 *	- Parameters:
 *	  - t_token *redi: the output file redirection token;
 *
 *	- Perform output file redirection using the 'redi' token.
 *	- The function opens the output file specified in the 'redi->str' field using:
 *		- O_WRONLY: opened in write-only mode,
 *		- O_CREAT: create the file if it does not already exist,
 *		- O_TRUNC: if the file already has content, that content will be removed, 
 *		  and the file will be emptied,
 *		- 0777: file permission mode used when creating a new file 
 *		  with the O_CREAT flag.
 *	- If the file cannot be opened, it calls print_error() to display an 
 *	  error message and terminates the program.
 *	- The function then duplicates the file descriptor 'file' to 
 *	  the standard output (1) using 'protect_dup2'.
 *	- Finally, it closes the file descriptor 'file'.
 */
void	redi_out(t_cmd *cmd, t_token *redi)
{
	int	file;

	file = open(redi->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0)
		print_error(redi->str, 1);
	cmd->fd_out = file;
}

/* redi_app();
 *	- Parameters:
 *	  - t_token *redi: the file redirection token;
 *
 * 	- Perform append file redirection using the 'redi' token.
 *	- The function opens the output file specified in the 'redi->str' field using:
 *		- O_WRONLY: opened in write-only mode,
 *		- O_APPEND: "append mode", any data written to the file will 
 *		  be appended to the end of the file, 
 *		  rather than overwriting the existing content,
 *		- O_CREAT: create the file if it does not already exist,
 *		- 0777: file permission mode used when creating a 
 *		  new file with the O_CREAT flag.
 *	- If the file cannot be opened, it calls print_error() to display an 
 *	  error message and terminates the program.
 *	- The function then duplicates the file descriptor 'file' to 
 *	  the standard output (1) using 'protect_dup2'.
 *	- Finally, it closes the file descriptor 'file'.
 */
void	redi_app(t_cmd *cmd, t_token *redi)
{
	int	file;

	file = open(redi->str, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (file < 0)
		print_error(redi->str, 1);
	cmd->fd_out = file;
}
