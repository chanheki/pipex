/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:54:18 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/07 20:32:49 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex_init(t_info *info, int argc, char **argv, char **envp)
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
	info->pid = -1;
	info->fd[FD_READ] = -1;
	info->fd[FD_WRITE] = -1;
	info->infile = -1;
	info->outfile = -1;
	info->argv_index = 2;
	info->status = ERROR;
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

// static void	here_doc_compare(const char *line, const char *limiter)
// {
// 	if (!ft_strncmp(line, limiter, ft_strlen(limiter))
// 		&& ft_strlen(line) == ft_strlen(limiter) + 1)
// 		exit(EXIT_SUCCESS);
// }

// void	here_doc(const char *limiter, t_info *info)
// {
// 	char	*line;

// 	info->argv_index = 3;
// 	if (pipe(info->fd) == -1)
// 		error_exitor("here_doc pipe error");
// 	info->pid = fork();
// 	if (info->pid == CHILD_PROCESS)
// 	{
// 		close(info->fd[FD_READ]);
// 		line = get_next_line(STDIN_FILENO);
// 		while (line)
// 		{
// 			here_doc_compare(line, limiter);
// 			write(info->fd[FD_WRITE], line, ft_strlen(line));
// 			line = get_next_line(STDIN_FILENO);
// 		}
// 		free(line);
// 	}
// 	else
// 	{
// 		dup2(info->fd[FD_READ], STDIN_FILENO);
// 		close(info->fd[FD_WRITE]);
// 		close(info->fd[FD_READ]);
// 		waitpid(info->pid, NULL, WNOWAIT);
// 	}
// }

void	here_doc(t_info *info)
{
	char	*line;
	char	*limiter;
	int		here_doc_fd;

	info->argv_index = 3;
	here_doc_fd = file_checker(info->argv[1], OUTFILE);
	line = get_next_line(STDIN_FILENO);
	limiter = ft_strjoin(info->argv[2], "\n");
	while (ft_strcmp(line, limiter))
	{
		free(line);
		ft_putstr_fd(line, here_doc_fd);
		line = get_next_line(STDIN_FILENO);
	}
	free(limiter);
	free(line);
	if (close(here_doc_fd) < 0)
		error_exitor("here_doc close error");
}

int	file_checker(char *argv, t_input i)
{
	int	file;

	file = 0;
	if (i == HERE_DOC)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == OUTFILE)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == INFILE)
		file = open(argv, O_RDONLY);
	if (file == -1)
		error_exitor("file check error");
	return (file);
}
