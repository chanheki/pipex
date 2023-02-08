/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:54:05 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/07 20:02:19 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

/* mandatory */
typedef enum e_status
{
	PARENT_PROCESS = 1,
	CHILD_PROCESS = 0
}	t_status;

/* pipe fd */
typedef enum e_pipefd
{
	FD_READ = 0,
	FD_WRITE = 1
}	t_pipefd;

/* process handler */
void	process_handler(char **argv, char **envp, int *fd, t_status status);

/* utils */
void	error_exitor(char *error_msg);
char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);

/* bonus */

typedef enum e_input
{
	ERROR = 0,
	HERE_DOC = 1,
	INFILE = 2,
	OUTFILE = 3
}	t_input;

typedef struct s_info
{
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		fd[2];
	int		infile;
	int		outfile;
	int		argv_index;
	t_input	status;
}	t_info;

/* pipex init */
void	pipex_init(t_info *info, int argc, char **argv, char **envp);
t_input	pipex_validator(t_info *info);

/* process handler bonus */
void	process_handler_bonus(char **argv, char **envp, int *fd, int count);

/* utils bonus */
// void	here_doc(const char *limiter, t_info *info);
void	here_doc(t_info *info);
int		file_checker(char *argv, t_input i);
void	execute_process(t_info *info, char *argv, char **envp);
void	last_process(t_info *info, char *argv, char **envp);

#endif