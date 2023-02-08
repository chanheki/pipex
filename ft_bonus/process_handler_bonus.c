/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:25:51 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/08 11:25:22 by chanheki         ###   ########.fr       */
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
		if (dup2(info->fd[FD_WRITE], STDOUT_FILENO) < 0)
			error_exitor("dup2 fd write error");
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
		execute(argv, envp);
	}
	else
	{
		if (dup2(info->fd[FD_READ], STDIN_FILENO) < 0)
			error_exitor("dup2 fd read error");
		if (close(info->fd[FD_WRITE]) < 0)
			error_exitor("close fd write error");
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
		waitpid(pid, NULL, WNOWAIT);
	}
}

void	last_process(t_info *info, char *argv, char **envp)
{
	pid_t	pid;

	if (pipe(info->fd) == -1)
		error_exitor("pipe error");
	pid = fork();
	if (pid == -1)
		error_exitor("pid error");
	if (pid == 0)
	{
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
		if (dup2(info->outfile, STDOUT_FILENO) < 0)
			error_exitor("dup2 fd outfile error");
		execute(argv, envp);
	}
	else
	{
		if (close(info->fd[FD_WRITE]) < 0)
			error_exitor("close fd write error");
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
		waitpid(pid, NULL, WNOWAIT);
	}
	if (info->status == HERE_DOC)
		unlink(info->argv[1]);
}
