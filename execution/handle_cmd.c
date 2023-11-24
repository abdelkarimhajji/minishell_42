/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:15:03 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 18:30:36 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reinit_global(t_general_info *info)
{
	info->proc_running = 0;
	info->hrdc_state = 0;
	info->hrdc_child = 0;
	info->hrdc_exit = 0;
	info->hrdc_quotes = 0;
}

int	get_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
	{
		return (WEXITSTATUS(exit_status));
	}
	else if (WIFSIGNALED(exit_status))
	{
		return (WTERMSIG(exit_status) + 128);
	}
	return (1);
}

int	handle_cmd(t_shell *shell)
{
	if (shell->cmds->pipe == 1)
		exec_pipes(shell);
	else
		single_cmd(shell);
	reinit_global(&g_info);
	return (0);
}
