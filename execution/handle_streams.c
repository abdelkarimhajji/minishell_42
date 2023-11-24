/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_streams.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:11:26 by nachab            #+#    #+#             */
/*   Updated: 2023/06/17 19:21:32 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_infile(t_shell *shell, t_file *file)
{
	if (file->mode == HEREDOC)
	{
		if (shell->cmds->in != 0)
			close(shell->cmds->in);
		shell->cmds->in = init_heredoc(shell, file);
		if (shell->cmds->in < 0)
			return (ERROR);
	}
	else if (file->mode == READ)
	{
		if (shell->cmds->in != 0)
			close(shell->cmds->in);
		shell->cmds->in = open(file->name, O_RDONLY, 0644);
		if (shell->cmds->in < 0)
		{
			perror(file->name);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	open_outfile(t_shell *shell, t_file *file)
{
	if (file->mode == CREATE)
	{
		if (shell->cmds->out != 1)
			close(shell->cmds->out);
		shell->cmds->out = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (shell->cmds->out < 0)
		{
			perror(file->name);
			return (ERROR);
		}
	}
	else if (file->mode == APPEND)
	{
		if (shell->cmds->out != 1)
			close(shell->cmds->out);
		shell->cmds->out = open(file->name, O_CREAT | O_WRONLY | O_APPEND,
				0644);
		if (shell->cmds->out < 0)
		{
			perror(file->name);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	init_streams(t_shell *shell)
{
	t_file	*file;

	file = shell->cmds->file;
	shell->cmds->in = STDIN_FILENO;
	shell->cmds->out = STDOUT_FILENO;
	while (file != NULL)
	{
		if (file->mode == HEREDOC || file->mode == READ)
		{
			if (open_infile(shell, file) == ERROR)
				return (ERROR);
			shell->exit_status = SUCCESS;
		}
		else if (file->mode == CREATE || file->mode == APPEND)
		{
			if (open_outfile(shell, file) == ERROR)
				return (ERROR);
			shell->exit_status = SUCCESS;
		}
		file = file->next;
	}
	return (SUCCESS);
}

void	dup_redir(t_cmd *cmd, int *fds, int in_pipe)
{
	if (cmd->in != 0)
		dup2(cmd->in, STDIN_FILENO);
	else
		dup2(in_pipe, STDIN_FILENO);
	if (cmd->out != 1)
		dup2(cmd->out, STDOUT_FILENO);
	else if (cmd->next != NULL)
		dup2(fds[1], STDOUT_FILENO);
}

void	close_streams(t_cmd *cmd)
{
	if (cmd->in != 0)
		close(cmd->in);
	if (cmd->out != 1)
		close(cmd->out);
}
