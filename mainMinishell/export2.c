/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:47:49 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 20:12:52 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_exist(t_list *var, char *arg)
{
	while (var)
	{
		if (ft_strcmp(var->var, arg) == 0)
			return (0);
		var = var->next;
	}
	return (1);
}

int	update_value_var(t_list **var, char *arg, char *ar0)
{
	t_list	*tmp;

	tmp = *var;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, ar0) == 0)
		{
			if (ft_strchr(arg, '=') != NULL)
			{
				free(tmp->value);
				tmp->value = ft_strdup(ft_strchr(arg, '='));
			}
			if (check_equal(arg) == 1)
				tmp->valid = 1;
			else
				tmp->valid = 0;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_var(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && (!(arg[0] >= 'a' && arg[0] <= 'z') && !(arg[0] >= 'A'
					&& arg[0] <= 'Z') && arg[0] != '_'))
			return (1);
		else if (i != 0 && (!(arg[i] >= 'a' && arg[i] <= 'z') && !(arg[i] >= 'A'
					&& arg[i] <= 'Z') && !(arg[i] >= '0' && arg[i] <= '9')
				&& arg[i] != '_'))
			return (1);
		i++;
	}
	if (arg[i] == '=' && arg[i + 1] == '=')
		return (1);
	return (0);
}

void	rmove_var_top(t_list **var, t_list **tmp)
{
	*var = (*tmp)->next;
	free((*tmp)->var);
	free((*tmp)->value);
	free((*tmp));
	(*tmp) = *var;
}

void	rmove_var_last(t_list **tmp2, t_list **tmp)
{
	while ((*tmp2)->next->next != NULL)
		(*tmp2) = (*tmp2)->next;
	free((*tmp2)->next->var);
	free((*tmp2)->next->value);
	free((*tmp2)->next);
	(*tmp2)->next = NULL;
	*tmp = NULL;
}
