/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:05 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:57:28 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rmove_var_behind(t_list **tmp, t_list **tmp3, t_list **tmp2)
{
	(*tmp3) = (*tmp)->next;
	while ((*tmp2)->next != *tmp)
		(*tmp2) = (*tmp2)->next;
	(*tmp2)->next = (*tmp3);
	free((*tmp)->var);
	free((*tmp)->value);
	free(*tmp);
	(*tmp) = (*tmp2);
}

void	rmove_var(t_list **var, char *arg)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*tmp3;

	tmp = *var;
	tmp2 = *var;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, arg) == 0)
		{
			if (tmp == *var)
				rmove_var_top(var, &tmp);
			else if (tmp->next == NULL)
				rmove_var_last(&tmp2, &tmp);
			else
				rmove_var_behind(&tmp, &tmp3, &tmp2);
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
}

int	print_export(t_shell *shell)
{
	t_list	*tmp;

	tmp = *shell->var;
	while (tmp)
	{
		printf("declare -x %s", tmp->var);
		if (tmp->valid == 1 && tmp->value[0] == '\0')
			printf("=\"\"");
		if (tmp->value != NULL && tmp->value[0])
			printf("=\"%s\"\n", tmp->value);
		else
			printf("\n");
		tmp = tmp->next;
	}
	return (0);
}

void	add_export_exist(t_shell *shell, char **arr, int i)
{
	int	j;

	if (check_if_exist(*shell->var, arr[0]) == 1)
	{
		add_to_istvar(shell->var, shell->cmds->args[i]);
		j = 0;
		while (shell->env[j])
			free(shell->env[j++]);
		free(shell->env);
		shell->env = get_arre_envs(*shell->var);
		free(shell->path);
		shell->path = get_var(*shell->var, "PATH");
	}
	else
	{
		update_value_var(shell->var, shell->cmds->args[i], arr[0]);
		j = 0;
		while (shell->env[j])
			free(shell->env[j++]);
		free(shell->env);
		shell->env = get_arre_envs(*shell->var);
		free(shell->path);
		shell->path = get_var(*shell->var, "PATH");
	}
}
