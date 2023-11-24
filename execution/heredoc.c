/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:26:13 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 16:03:06 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_heredoc(t_shell *shell, int *fds, t_file *file)
{
	char	*input;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input = readline("> ");
		if (handle_input(shell, input, fds, file->name) == 1)
			break ;
		free(input);
	}
	exit (0);
}

int	init_heredoc(t_shell *shell, t_file *file)
{
	int	fds[2];

	if (pipe(fds) != 0)
		return (-1);
	g_info.hrdc_state = 1;
	g_info.hrdc_child = fork();
	if (g_info.hrdc_child == 0)
		child_heredoc(shell, fds, file);
	waitpid(g_info.hrdc_child, &g_info.hrdc_exit, 0);
	close(fds[1]);
	if (WIFSIGNALED(g_info.hrdc_exit))
	{
		g_info.hrdc_exit = EXIT_FAILURE;
		shell->exit_status = 1;
		close(fds[0]);
		return (ERROR);
	}
	g_info.hrdc_state = 0;
	return (fds[0]);
}
