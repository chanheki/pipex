/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:56:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/25 19:52:27 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		i;

	pipex_init(&info, argc, argv, envp);
	if (pipex_validator(&info) == HERE_DOC)
	{
		i = 3;
		info.infile = file_checker(info.argv[argc - 1], HERE_DOC);
		here_doc(info.argv[2], &info);
	}
	else
	{
		i = 2;
		info.outfile = file_checker(info.argv[argc - 1], OUTFILE);
		info.infile = file_checker(info.argv[1], INFILE);
		dup2(info.infile, STDIN_FILENO);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(info.outfile, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
	return (0);
}
