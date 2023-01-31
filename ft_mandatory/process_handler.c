/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:25:51 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/31 17:12:17 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	process_child(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile < 0)
		error_exitor("infile error");
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

static void	process_parent(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
		error_exitor("outfile error");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

void	process_handler(char **argv, char **envp, int *fd, t_status status)
{
	if (status == CHILD_PROCESS)
		process_child(argv, envp, fd);
	if (status == PARENT_PROCESS)
		process_parent(argv, envp, fd);
}
