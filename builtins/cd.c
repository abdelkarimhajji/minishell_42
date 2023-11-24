/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:49:55 by nachab            #+#    #+#             */
/*   Updated: 2023/06/16 16:43:44 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_path(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		perror("cd");
	else
	{
		if (S_ISDIR(st.st_mode) != 0)
		{
			if (access(path, X_OK) == -1)
			{
				perror("cd");
				return (ERROR);
			}
			else
				return (SUCCESS);
		}
	}
	return (ERROR);
}

int	cd_with_path(t_shell *shell)
{
	char	path[1024];

	if (check_valid_path(shell->cmds->args[1]) == SUCCESS)
	{
		if (chdir(shell->cmds->args[1]) != SUCCESS)
		{
			perror("Couldn't execute cd");
			return (ERROR);
		}
		else
		{
			if (getcwd(path, sizeof(path)) != NULL)
				update_env(shell, path);
			else
			{
				perror("Couldn't retrieve current directory");
				return (ERROR);
			}
		}
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int	cd_home(t_shell *shell)
{
	char	*home;

	home = get_value_var(*(shell->var), "$HOME", 0, NULL);
	if (!home)
		return (ERROR);
	if (check_valid_path(home) == SUCCESS)
	{
		if (chdir(home) != SUCCESS)
		{
			free(home);
			perror("cd");
			return (ERROR);
		}
		else
			update_env(shell, home);
	}
	else
	{
		free(home);
		return (ERROR);
	}
	free(home);
	return (SUCCESS);
}

int	cd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	if (shell->cmds->pipe == 1)
		return (SUCCESS);
	if (cmd->args[1] != NULL)
	{
		if (cd_with_path(shell) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (cd_home(shell) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
