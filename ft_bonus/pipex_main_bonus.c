/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:56:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/19 23:32:41 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		count;

	pipex_init(&info, argc, argv, envp);
	pipex_validator(&info);
	count = 1;
	while (count != argc)
	{
		if (pipe(info.fd) == -1)
			error_exitor("pipe error");
		info.pid = fork();
		if (info.pid < 0)
			error_exitor("fork error");
		if (info.pid == 0)
			process_handler_bonus(argv, envp, info.fd, count);
		if (waitpid(info.pid, NULL, 0) == -1)
			error_exitor("waitpid error");
		count ++;
	}
	process_handler_bonus(argv, envp, info.fd, count);
	return (0);
}
