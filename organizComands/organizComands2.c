/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizComands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:20:21 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 17:04:42 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	leng_args(t_listLex *tmp)
{
	int	i;

	i = 0;
	if (tmp->type == '|')
		tmp = tmp->next;
	while (tmp && tmp->type != '|')
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	check_beguist(char state, char *ptr, t_listLex *headLex, t_shell *shell)
{
	int	i;

	i = 0;
	if (state == '0')
	{
		while (ptr[i])
		{
			if (((ptr[i] == ' ' || ptr[i] == '\t') && ptr[i + 1] != '\0'
					&& ptr[i + 1] != ' ' && ptr[i + 1] != '\t'))
				return (shell->exit_status = 1,
					printf("ambiguous redirect\n"), 1);
			i++;
		}
		if (headLex->next != NULL && (headLex->next->type == 'V'
				|| headLex->next->type == '"' || headLex->next->type == '\''
				|| headLex->next->type == 'W'))
		{
			if (ptr[i - 1] == ' ' || ptr[i - 1] == '\t')
				return (shell->exit_status = 1,
					printf("ambiguous redirect\n"), 1);
		}
	}
	return (0);
}

int	organiz_dobl_singif_one_one(t_listLex **headLex, t_minishell *data,
	char **ptr, t_shell *shell)
{
	if ((*headLex)->next == NULL)
		data->begnext = -1;
	if ((*headLex)->prev != (*headLex) && (*headLex)->prev->type != ' '
		&& (*headLex)->prev->type != '\t')
		data->begprev = 0;
	*ptr = ft_strjoin(*ptr, get_value_var(*shell->var, (*headLex)->content,
				(*headLex)->state, data));
	if (data->pguist == 0 && *ptr != NULL)
	{
		if (check_beguist((*headLex)->state, get_value_var(*shell->var,
					(*headLex)->content, (*headLex)->state, data), *headLex,
				shell) == 1)
		{
			free(*ptr);
			return (1);
		}
	}
	return (0);
}

int	organiz_dobl_singif_one(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	while ((*headLex)->next && (*headLex)->type != '"'
		&& (*headLex)->type != '\'' && (*headLex)->type != '<'
		&& (*headLex)->type != '>' && (*headLex)->type != '|'
		&& (*headLex)->type != 'D' && (*headLex)->type != 'H')
	{
		if ((*headLex)->content[0] == '$' && data->valid5 == 1
			&& (*headLex)->state != '1' && (((*headLex)->content[1] >= 'a'
					&& (*headLex)->content[1] <= 'z')
				|| ((*headLex)->content[1] >= 'A'
					&& (*headLex)->content[1] <= 'Z')))
		{
			if (organiz_dobl_singif_one_one(headLex, data, ptr, shell) == 1)
				return (1);
		}
		else
			*ptr = ft_strjoin(*ptr, (*headLex)->content);
		(*headLex) = (*headLex)->next;
	}
	return (0);
}

int	organiz_dobl_singif_null_one(t_listLex **headLex, t_minishell *data,
	char **ptr, t_shell *shell)
{
	if ((*headLex)->next == NULL)
		data->begnext = -1;
	if ((*headLex)->prev != (*headLex) && (*headLex)->prev->type != ' '
		&& (*headLex)->prev->type != '\t')
		data->begprev = 0;
	*ptr = ft_strjoin(*ptr, get_value_var(*shell->var, (*headLex)->content,
				(*headLex)->state, data));
	if (data->pguist == 0 && *ptr != NULL)
	{
		if (check_beguist((*headLex)->state,
				get_value_var(*shell->var, (*headLex)->content,
					(*headLex)->state, data),*headLex, shell) == 1)
		{
			free(*ptr);
			return (1);
		}
	}
	else if (data->pguist == 0)
		return (shell->exit_status = 1, printf("ambiguous redirect\n"), 1);
	return (0);
}
