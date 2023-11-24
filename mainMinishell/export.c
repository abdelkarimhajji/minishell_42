/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:03:29 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 17:02:50 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_export(t_shell *shell, int i)
{
	shell->exit_status = 1;
	printf("export: '%s': not a valid identifier\n", shell->cmds->args[i]);
}

int	add_export(t_shell *shell)
{
	int		i;
	int		j;
	char	**arr;

	j = 0;
	i = 1;
	while (shell->cmds->args[i])
	{
		if (check_var(shell->cmds->args[i]) == 0)
		{
			arr = ft_split(shell->cmds->args[i], '=');
			add_export_exist(shell, arr, i);
			j = 0;
			while (arr[j])
			{
				free(arr[j]);
				j++;
			}
			free(arr);
		}
		else
			return (print_error_export(shell, i), 1);
		i++;
	}
	return (0);
}

int	print_env(t_shell *shell)
{
	t_list	*tmp;

	tmp = *shell->var;
	while (tmp)
	{
		if (tmp->valid == 1)
		{
			printf("%s=", tmp->var);
			if (tmp->value != NULL)
				printf("%s\n", tmp->value);
			else
				printf("\n");
		}
		tmp = tmp->next;
	}
	return (0);
}

int	my_unset(t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (shell->cmds->args[i])
	{
		if (check_if_exist(*shell->var, shell->cmds->args[i]) == 0)
		{
			rmove_var(shell->var, shell->cmds->args[i]);
			j = 0;
			while (shell->env[j])
			{
				free(shell->env[j]);
				j++;
			}
			free(shell->env);
			shell->env = get_arre_envs(*shell->var);
			free(shell->path);
			shell->path = get_var(*shell->var, "PATH");
		}
		i++;
	}
	return (0);
}

int	my_export(t_shell *shell, int mode)
{
	if (shell->cmds->cmd && ft_strcmp(shell->cmds->cmd, "export") == 0)
	{
		if (mode == 1)
			print_export(shell);
		else
			if (add_export(shell) == 1)
				return (1);
	}
	return (0);
}
