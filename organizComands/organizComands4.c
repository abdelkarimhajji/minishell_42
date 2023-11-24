/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizComands4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:28:49 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:38:36 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	organiz_dobl_singif_two_null(t_listLex **headLex, t_minishell *data,
	char **ptr, t_shell *shell)
{
	if ((*headLex)->content[0] == '$' && data->valid5 == 1
		&& (*headLex)->state != '1' && (((*headLex)->content[1] >= 'a'
				&& (*headLex)->content[1] <= 'z')
			|| ((*headLex)->content[1] >= 'A'
				&& (*headLex)->content[1] <= 'Z')))
	{
		if (organiz_dobl_singif_two_null_one(headLex, data, ptr, shell) == 1)
			return (1);
	}
	else
		*ptr = ft_strjoin(*ptr, (*headLex)->content);
	return (0);
}

int	organiz_dobl_singif_two(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	if ((*headLex)->next != NULL)
		(*headLex) = (*headLex)->next;
	while ((*headLex)->next && (*headLex)->type != ' '
		&& (*headLex)->type != '\t'
		&& (*headLex)->type != '<' && (*headLex)->type != '>'
		&& (*headLex)->type != 'H' && (*headLex)->type != 'D'
		&& (*headLex)->type != '|')
	{
		if (organiz_dobl_singif_two_one(headLex, data, ptr, shell) == 1)
			return (1);
		if ((*headLex)->next == NULL)
			break ;
		(*headLex) = (*headLex)->next;
	}
	if ((*headLex)->next == NULL && (*headLex)->type != '\''
		&& (*headLex)->type != '"' && (*headLex)->type != ' '
		&& (*headLex)->type != '\t')
	{
		if (organiz_dobl_singif_two_null(headLex, data, ptr, shell) == 1)
			return (1);
	}
	return (0);
}

int	organiz_dobl_sing(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	if ((*headLex)->type == '"')
	{
		if (organiz_dobl_singif(headLex, data, ptr, shell) == 1)
			return (1);
	}
	if ((*headLex)->type == '\'')
	{
		if (organiz_dobl_singif_two(headLex, data, ptr, shell) == 1)
			return (1);
	}
	return (0);
}

int	organiz_else_one_one_one(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	if ((*headLex)->next == NULL)
		data->begnext = -1;
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
	else if (data->pguist == 0)
	{
		shell->exit_status = 1;
		printf("enbeguist\n");
		return (1);
	}
	return (0);
}

int	organiz_else_one_one(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	if ((*headLex)->content[0] == '$' && (*headLex)->state != '1'
		&& (((*headLex)->content[1] >= 'a' && (*headLex)->content[1] <= 'z'
				&& data->valid5 == 1) || ((*headLex)->content[1] >= 'A'
				&& (*headLex)->content[1] <= 'Z')))
	{
		if (organiz_else_one_one_one(headLex, data, ptr, shell) == 1)
			return (1);
		(*headLex) = (*headLex)->next;
	}
	else
	{
		*ptr = ft_strjoin(*ptr, (*headLex)->content);
		(*headLex) = (*headLex)->next;
	}
	return (0);
}
