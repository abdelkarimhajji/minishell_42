/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:08:14 by nachab            #+#    #+#             */
/*   Updated: 2023/06/15 20:07:30 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_parent_builtin(t_cmd *cmd)
{
	if (ft_strcmp("cd", cmd->cmd) == 0)
		return (SUCCESS);
	if (ft_strcmp("export", cmd->cmd) == 0)
		return (SUCCESS);
	if (ft_strcmp("unset", cmd->cmd) == 0)
		return (SUCCESS);
	if (ft_strcmp("exit", cmd->cmd) == 0)
		return (SUCCESS);
	return (ERROR);
}

int	exec_parent_builtin(t_shell *shell)
{
	if (ft_strcmp("cd", shell->cmds->cmd) == 0)
		return (cd(shell));
	if (ft_strcmp("export", shell->cmds->cmd) == 0
		&& shell->cmds->args[1] != NULL)
		return (my_export(shell, 0));
	if (ft_strcmp("unset", shell->cmds->cmd) == 0)
		return (my_unset(shell));
	if (ft_strcmp("exit", shell->cmds->cmd) == 0)
		ft_exit(shell);
	return (ERROR);
}
