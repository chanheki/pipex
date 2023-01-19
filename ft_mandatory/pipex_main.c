
#include "../includes/pipex.h"

int main(int argc, char **argv, char **envp)
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
		process_handler(argv, envp, fd, CHILD_PROCESS); // child logic
	if (waitpid(pid, NULL, 0) == -1)
		error_exitor("waitpid error");
	process_handler(argv, envp, fd, PARENT_PROCESS); // parent logic
	return (0);
}
