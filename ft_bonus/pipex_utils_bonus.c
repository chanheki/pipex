/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:54:18 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/01 20:18:50 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex_init(t_info *info, int argc, char **argv, char **envp)
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
	info->pid = -1;
	info->fd[0] = -1;
	info->fd[1] = -1;
	info->infile = -1;
	info->outfile = -1;
	info->argv_index = 2;
}

t_input	pipex_validator(t_info *info)
{
	if (info->argc < 5)
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\033[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp(info->argv[1], "here_doc", 8))
	{
		if (info->argc < 6)
		{
			ft_putstr_fd("\033[31mError: here_doc arguments error\n\033[0m", 2);
			ft_putstr_fd("    ./pipex \"here_doc\" ", 1);
			ft_putstr_fd("<LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
			exit(EXIT_FAILURE);
		}
		return (HERE_DOC);
	}
	return (INFILE);
}

void	here_doc(const char *limiter, t_info *info)
{
	char	*line;

	info->argv_index = 3;
	if (pipe(info->fd) == -1)
		error_exitor("here_doc pipe error");
	info->pid = fork();
	if (info->pid == 0)
	{
		close(info->fd[0]);
		line = get_next_line(0);
		while (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(EXIT_SUCCESS);
			write(info->fd[1], line, ft_strlen(line));
			line = get_next_line(0);
		}
		free(line);
	}
	else
	{
		close(info->fd[1]);
		dup2(info->fd[0], STDIN_FILENO);
		waitpid(info->pid, NULL, WNOHANG);
	}
}

int	file_checker(char *argv, t_input i)
{
	int	file;

	file = 0;
	if (i == HERE_DOC)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == OUTFILE)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == INFILE)
		file = open(argv, O_WRONLY, 0777);
	if (file == -1)
		error_exitor("file check error");
	return (file);
}
