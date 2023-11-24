/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:46:35 by nachab            #+#    #+#             */
/*   Updated: 2023/06/14 18:34:45 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_message(char *not_num_error, char *message)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	if (not_num_error != NULL)
		ft_putstr_fd(not_num_error, 2);
	ft_putstr_fd(message, 2);
}

int	exit_with_value(t_shell *shell)
{
	unsigned char	exit_status;

	if (valid_number(shell->cmds->args[1]) == ERROR)
	{
		exit_message(shell->cmds->args[1], ": numeric argument required\n");
		free_shell_struct(shell);
		exit(255);
	}
	else
	{
		exit_status = ft_atoi(shell->cmds->args[1]);
		if (shell->cmds->args[2] != NULL)
		{
			exit_message(NULL, "exit: too many arguments\n");
			return (ERROR);
		}
		else
		{
			printf("exit\n");
			free_shell_struct(shell);
			exit(exit_status);
		}
	}
	return (SUCCESS);
}

int	ft_exit(t_shell *shell)
{
	if (shell->cmds->args[1] != NULL)
	{
		if (exit_with_value(shell) == ERROR)
			return (ERROR);
	}
	else
	{
		free_shell_struct(shell);
		printf("exit\n");
		exit(shell->exit_status);
	}
	return (ERROR);
}
