/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:56:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/02/07 20:26:37 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	pipex_init(&info, argc, argv, envp);
	info.status = pipex_validator(&info);
	if (info.status == HERE_DOC)
	{
		here_doc(&info);
		process_input_output(&info, HERE_DOC);
	}
	else if (info.status == INFILE)
		process_input_output(&info, OUTFILE);
	else
		error_exitor("status error");
	while (info.argv_index < argc - 2)
		execute_process(&info, info.argv[info.argv_index++], envp);
	last_process(&info, info.argc - 2, envp);
	return (0);
}
