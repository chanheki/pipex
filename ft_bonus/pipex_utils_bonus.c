
#include "../includes/pipex.h"

void pipex_init(t_info *info, int argc, char **argv, char **envp)
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
	info->fd[0] = -1;
	info->fd[1] = -1;
	info->pid = -1;
}

void pipex_validator(t_info *info)
{
	if (!ft_strncmp(info->argv[1], "here_doc", 8))
	{
		if (info->argc < 6)
		{
			ft_putstr_fd("\033[31mError: here_doc arguments error\n\033[0m", 2);
			ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
			exit(EXIT_FAILURE);
		}
		here_doc(info->argv[2], info);
	}
	if (info->argc < 5)
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\033[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	here_doc(const char *limiter, t_info *info)
{
	char *line;

	if (pipe(info->fd) == -1)
		error_exitor("here_doc pipe error");
	info->pid = fork();
	if (info->pid == 0)
	{
		close(info->fd[0]);
		while (get_next_line(line))
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(EXIT_SUCCESS);
			write(info->fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(info->fd[1]);
		dup2(info->fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
