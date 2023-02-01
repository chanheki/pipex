/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:25:51 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/01 20:49:15 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_process(t_info *info, char *argv, char **envp)
{
	pid_t	pid;

	if (pipe(info->fd) == -1)
		error_exitor("pipe error");
	pid = fork();
	if (pid == -1)
		error_exitor("pid error");
	if (pid == 0)
	{
		close(info->fd[0]);
		dup2(info->fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(info->fd[1]);
		dup2(info->fd[0], STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
	}
}
