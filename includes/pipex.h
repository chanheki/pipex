
#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum e_status
{
	CHILD_PROCESS = 0,
	PARENT_PROCESS = 1,
}	t_status;

/* process handler */
void	process_handler(char **argv, char **envp, int *fd, t_status status);

/* utils */
void	error_exitor(char *error_msg);
char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);

#endif