/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:25:51 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/07 15:41:39 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	process_child(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_exitor("infile error");
	if (dup2(infile, STDIN_FILENO) < 0)
		error_exitor("dup stdin error");
	if (dup2(fd[FD_WRITE], STDOUT_FILENO) < 0)
		error_exitor("dup stdout error");
	if (close(fd[FD_READ]) < 0)
		error_exitor("close error");
	execute(argv[2], envp);
}

static void	process_parent(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error_exitor("outfile error");
	if (dup2(fd[FD_READ], STDIN_FILENO) < 0)
		error_exitor("dup stdin fd error");
	if (dup2(outfile, STDOUT_FILENO) < 0)
		error_exitor("dup stdout fd error");
	if (close(fd[FD_WRITE]) < 0)
		error_exitor("close error");
	execute(argv[3], envp);
}

void	process_handler(char **argv, char **envp, int *fd, t_status status)
{
	if (status == CHILD_PROCESS)
		process_child(argv, envp, fd);
	if (status == PARENT_PROCESS)
		process_parent(argv, envp, fd);
}
