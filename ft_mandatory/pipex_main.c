/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:56:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/19 22:54:59 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (argc != 5)
		error_exitor("It must take 4 arguments\n");
	if (pipe(fd) == -1)
		error_exitor("pipe error");
	pid = fork();
	if (pid < 0)
		error_exitor("fork error");
	if (pid == 0)
		process_handler(argv, envp, fd, CHILD_PROCESS);
	if (waitpid(pid, NULL, 0) == -1)
		error_exitor("waitpid error");
	process_handler(argv, envp, fd, PARENT_PROCESS);
	return (0);
}
