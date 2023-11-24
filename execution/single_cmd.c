/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:11:33 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 17:59:15 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	child_process(t_shell *shell)
{
	int	status;

	dup2(shell->cmds->in, STDIN_FILENO);
	dup2(shell->cmds->out, STDOUT_FILENO);
	signal(SIGQUIT, SIG_DFL);
	if (is_child_builtin(shell->cmds) == SUCCESS)
	{
		if (exec_child_builtin(shell) == SUCCESS)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	status = get_cmd_path(shell->cmds, shell->path);
	if (status != SUCCESS)
	{
		if (status == 126)
			perror(shell->cmds->cmd);
		else
		{
			ft_putstr_fd(shell->cmds->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(status);
	}
	execve(shell->cmds->path, shell->cmds->args, shell->env);
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_shell *shell)
{
	pid_t	pid;

	g_info.proc_running = 1;
	if (is_parent_builtin(shell->cmds) == SUCCESS)
	{
		if (exec_parent_builtin(shell) == SUCCESS)
		{
			shell->exit_status = EXIT_SUCCESS;
			return ;
		}
		if (ft_strcmp(shell->cmds->cmd, "export") != 0)
		{
			shell->exit_status = EXIT_FAILURE;
			return ;
		}
	}
	pid = fork();
	if (pid == 0)
		child_process(shell);
	else
	{
		waitpid(pid, &(shell->exit_status), 0);
		shell->exit_status = get_exit_status(shell->exit_status);
		close_streams(shell->cmds);
	}
}

int	single_cmd(t_shell *shell)
{
	if (init_streams(shell) == ERROR && g_info.hrdc_state != 1)
	{
		shell->exit_status = FILE_NOT_FOUND;
		return (ERROR);
	}
	if (g_info.hrdc_exit == EXIT_FAILURE)
	{
		return (ERROR);
	}
	if (shell->cmds->cmd != NULL)
		exec_cmd(shell);
	return (SUCCESS);
}
