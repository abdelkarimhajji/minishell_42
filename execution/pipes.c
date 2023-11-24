/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:11:31 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 18:02:48 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	child_pipe(t_shell *shell, int *fds, int in_fd)
{
	int	status;

	signal(SIGQUIT, SIG_DFL);
	close(fds[0]);
	dup_redir(shell->cmds, fds, in_fd);
	if (is_child_builtin(shell->cmds) == SUCCESS)
	{
		if (exec_child_builtin(shell) == SUCCESS)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
	status = get_cmd_path(shell->cmds, shell->path);
	if (status != SUCCESS)
	{
		if (status == 126)
			perror(shell->cmds->cmd);
		else
			print_err(shell->cmds->cmd);
		exit(status);
	}
	execve(shell->cmds->path, shell->cmds->args, shell->env);
	exit(EXIT_FAILURE);
}

int	parent_pipe(t_shell *shell, int pid, int *fds, int *old_pipe)
{
	close(fds[1]);
	waitpid(pid, &(shell->exit_status), 0);
	shell->exit_status = get_exit_status(shell->exit_status);
	if (*old_pipe != 0)
		close(*old_pipe);
	*old_pipe = fds[0];
	return (SUCCESS);
}

int	exec_pipe_cmd(t_shell *shell, int *fds, int *old_pipe)
{
	pid_t	pid;

	g_info.proc_running = 1;
	if (is_parent_builtin(shell->cmds) == SUCCESS)
	{
		if (exec_parent_builtin(shell) == SUCCESS)
		{
			shell->exit_status = EXIT_SUCCESS;
			return (SUCCESS);
		}
		if (ft_strcmp(shell->cmds->cmd, "export") != 0)
		{
			shell->exit_status = EXIT_FAILURE;
			return (ERROR);
		}
	}
	pid = fork();
	if (pid == 0)
		child_pipe(shell, fds, *old_pipe);
	else
	{
		close_streams(shell->cmds);
		parent_pipe(shell, pid, fds, old_pipe);
	}
	return (SUCCESS);
}

int	exec_pipes(t_shell *shell)
{
	t_cmd	*cmd;
	int		fds[2];
	int		old_pipe;

	old_pipe = 0;
	cmd = shell->cmds;
	while (shell->cmds != NULL)
	{
		if (init_streams(shell) == ERROR && g_info.hrdc_state != 1)
		{
			shell->exit_status = FILE_NOT_FOUND;
			shell->cmds = shell->cmds->next;
			continue ;
		}
		if (g_info.hrdc_exit == EXIT_FAILURE)
			return (ERROR);
		if (shell->cmds->cmd != NULL)
		{
			pipe(fds);
			exec_pipe_cmd(shell, fds, &old_pipe);
		}
		shell->cmds = shell->cmds->next;
	}
	shell->cmds = cmd;
	return (SUCCESS);
}
