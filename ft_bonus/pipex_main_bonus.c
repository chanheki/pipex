/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:56:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/01 20:49:16 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	pipex_init(&info, argc, argv, envp);
	if (pipex_validator(&info) == HERE_DOC)
	{
		info.outfile = file_checker(info.argv[argc - 1], HERE_DOC);
		here_doc(info.argv[2], &info);
	}
	else
	{
		info.infile = file_checker(info.argv[1], INFILE);
		info.outfile = file_checker(info.argv[argc - 1], OUTFILE);
		dup2(info.infile, STDIN_FILENO);
	}
	while (info.argv_index < argc - 2)
		execute_process(&info, argv[info.argv_index++], envp);
	dup2(info.outfile, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
	return (0);
}
