/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:11:23 by nachab            #+#    #+#             */
/*   Updated: 2023/05/16 15:11:23 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_exec(char *path)
{
	struct stat	file;

	if (stat(path, &file) == 0)
	{
		if (S_ISREG(file.st_mode) && (file.st_mode & S_IXUSR))
			return (SUCCESS);
		errno = EACCES;
		return (PERMISSION_ERR);
	}
	return (CMD_NOT_FOUND);
}

int	check_with_path(t_cmd *cmd)
{
	int	status;

	status = check_if_exec(cmd->cmd);
	if (status == SUCCESS)
	{
		cmd->path = ft_strdup(cmd->cmd);
		return (SUCCESS);
	}
	return (status);
}

void	concat_path(t_cmd *cmd, char *path, char *env)
{
	ft_strcpy(path, env);
	ft_strcat(path, "/");
	ft_strcat(path, cmd->cmd);
}

int	search_path_var(t_cmd *cmd, char **env)
{
	int		status;
	char	path[1024];

	while (*env)
	{
		concat_path(cmd, path, *env);
		status = check_if_exec(path);
		if (status == PERMISSION_ERR)
		{
			return (status);
		}
		else if (status == SUCCESS)
		{
			cmd->path = ft_strdup(path);
			return (SUCCESS);
		}
		env++;
	}
	return (CMD_NOT_FOUND);
}

int	get_cmd_path(t_cmd *cmd, char *path_variable)
{
	int		status;
	char	**env;

	if (*(cmd->cmd) == '\0')
		return (CMD_NOT_FOUND);
	if (ft_strchr2(cmd->cmd, '/') != NULL)
	{
		status = check_with_path(cmd);
		if (status != SUCCESS)
			return (status);
		return (SUCCESS);
	}
	else
	{
		if (!path_variable)
			return (CMD_NOT_FOUND);
		env = ft_split(path_variable, ':');
		status = search_path_var(cmd, env);
		free_str_array(env);
		if (status == SUCCESS)
			return (SUCCESS);
	}
	return (status);
}
