/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:08:56 by nachab            #+#    #+#             */
/*   Updated: 2023/06/15 20:07:30 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_child_builtin(t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->cmd) == 0)
		return (SUCCESS);
	if (ft_strcmp("pwd", cmd->cmd) == 0)
		return (SUCCESS);
	if (ft_strcmp("export", cmd->cmd) == 0)
		return (SUCCESS);
	if (ft_strcmp("env", cmd->cmd) == 0)
		return (SUCCESS);
	return (ERROR);
}

int	exec_child_builtin(t_shell *shell)
{
	if (ft_strcmp("echo", shell->cmds->cmd) == 0)
		return (echo(shell->cmds->args));
	if (ft_strcmp("pwd", shell->cmds->cmd) == 0)
		return (pwd(shell));
	if (ft_strcmp("export", shell->cmds->cmd) == 0
		&& shell->cmds->args[1] == NULL)
		return (my_export(shell, 1));
	if (ft_strcmp("env", shell->cmds->cmd) == 0)
		return (print_env(shell));
	return (ERROR);
}
