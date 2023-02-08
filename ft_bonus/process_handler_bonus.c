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
	if (pipe(info->fd) == -1)
		error_exitor("pipe error");
	info->pid = fork();
	if (info->pid == -1)
		error_exitor("info->pid error");
	if (info->pid == 0)
	{
		if (dup2(info->fd[FD_WRITE], STDOUT_FILENO) < 0)
			error_exitor("dup2 fd write error");
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
		execute(argv, envp);
	}
	else
	{
		waitpid(info->pid, NULL, WNOHANG);
		if (dup2(info->fd[FD_READ], STDIN_FILENO) < 0)
			error_exitor("dup2 fd read error");
		if (close(info->fd[FD_WRITE]) < 0)
			error_exitor("close fd write error");
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
	}
}

void	last_process(t_info *info, int index, char **envp)
{
	if (pipe(info->fd) == -1)
		error_exitor("pipe error");
	info->pid = fork();
	if (info->pid == -1)
		error_exitor("info->pid error");
	if (info->pid == 0)
	{
		if (dup2(info->outfile, STDOUT_FILENO) < 0)
			error_exitor("dup2 fd outfile error");
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
		execute(info->argv[index], envp);
	}
	else
	{
		waitpid(info->pid, NULL, WNOHANG);
		if (close(info->fd[FD_WRITE]) < 0)
			error_exitor("close fd write error");
		if (close(info->fd[FD_READ]) < 0)
			error_exitor("close fd read error");
	}
	if (info->status == HERE_DOC)
		unlink(info->argv[1]);
}
