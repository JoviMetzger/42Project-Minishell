/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protection.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 12:54:21 by yizhang       #+#    #+#                 */
/*   Updated: 2023/08/02 12:22:03 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* protect_waitpid();
 *	- Parameters:
 *	  - pid_t id: Process ID to wait for;
 *	  - int *status: Pointer to the integer where the status 
 *		information will be stored;
 *	  - int options: Options for waitpid() function;
 *
 *	- Wrapper function to call waitpid() with error handling
 *	- If waitpid() returns -1 (error), 
 *	  it calls print_error() to display the error message.
 */
void	protect_waitpid(pid_t id, int *status, int options)
{
	if (waitpid(id, status, options) == -1)
		print_error(NULL, 1);
}

/* protect_dup2();
 *	- Parameters:
 *	  - int file: File descriptor to be duplicated;
 *	  - int file2: File descriptor to become a copy of 'file';
 *
 *	- Wrapper function to call dup2() with error handling
 *	- If dup2() returns -1 (error), it calls print_error() 
 *	  to display the error message.
 */
void	protect_dup2(int file, int file2)
{
	if (dup2(file, file2) == -1)
		print_error(NULL, 1);
}

/* protect_close();
 *	- Parameters:
 *	  - int file: File descriptor to be closed;
 *
 *	- Wrapper function to call close() with error handling
 *	- If close() returns -1 (error), it calls print_error() 
 *	  to display the error message.
 */
void	protect_close(int file)
{
	if (close(file) == -1)
		print_error(NULL, 1);
}

/* protect_write();
 *	- Parameters:
 *	  - int fd: File descriptor to write to;
 *	  - char *buf: Pointer to the buffer containing the data to write;
 *	  - int count: Number of bytes to write;
 *
 *	- Wrapper function to call write() with error handling
 *	- If write() returns -1 (error), it calls print_error() 
 *	  to display the error message.
 */
void	protect_write(int fd, char *buf, int count)
{
	if (write(fd, buf, count) == -1)
		print_error(NULL, 1);
}

/* protect_pipe();
 *	- Parameters:
 *	  - int fd: Array of two integers to store the file descriptors 
 *		for the new pipe;
 *
 *	- Wrapper function to call pipe() with error handling
 *	- If pipe() returns -1 (error), it calls print_error() 
 *	  to display the error message.
 */
void	protect_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		print_error(NULL, 1);
}
