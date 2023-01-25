/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:25:51 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/19 23:34:47 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	process_child(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile < 0)
		error_exitor("infile error");
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execute(argv[2], envp);
}

// static void	process_parent(char **argv, char **envp, int *fd)
// {
// 	int	outfile;

// 	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (outfile < 0)
// 		error_exitor("outfile error");
// 	close(fd[1]);
// 	dup2(fd[0], STDIN_FILENO);
// 	dup2(outfile, STDOUT_FILENO);
// 	execute(argv[3], envp);
// }

void	process_handler_bonus(char **argv, char **envp, int *fd, int count)
{
	(void) count;
	process_child(argv, envp, fd);
}
