/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizComands5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:01:16 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:38:49 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	organiz_else_one(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	if ((*headLex)->type == '"' || (*headLex)->type == '\'')
	{
		if ((*headLex)->next != NULL)
			(*headLex) = (*headLex)->next;
	}
	else
	{
		if (organiz_else_one_one(headLex, data, ptr, shell) == 1)
			return (1);
	}
	return (0);
}

int	organiz_else_two(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	if ((*headLex)->content[0] == '$' && data->valid5 == 1
		&& (((*headLex)->content[1] >= 'a' && (*headLex)->content[1] <= 'z')
			|| ((*headLex)->content[1] >= 'A'
				&& (*headLex)->content[1] <= 'Z')))
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
				return (free(*ptr), 1);
		}
		else if (data->pguist == 0)
		{
			shell->exit_status = 1;
			return (printf("enbeguist\n"), 1);
		}
	}
	else
		*ptr = ft_strjoin(*ptr, (*headLex)->content);
	return (0);
}

int	organiz_else(t_listLex **headLex, t_minishell *data, char **ptr,
		t_shell *shell)
{
	while ((*headLex)->next && (*headLex)->type != ' '
		&& (*headLex)->type != '\t'
		&& (*headLex)->type != '|' && ((*headLex)->type != '>')
		&& (*headLex)->type != '<' && (*headLex)->type != 'H'
		&& (*headLex)->type != 'D')
	{
		if (organiz_else_one(headLex, data, ptr, shell) == 1)
			return (1);
	}
	if ((*headLex)->next == NULL && (*headLex)->type != '|'
		&& (*headLex)->type != '"' && (*headLex)->type != ' '
		&& (*headLex)->type != '\t'
		&& (*headLex)->type != '\'' && (*headLex)->type != '<'
		&& (*headLex)->type != '>' && (*headLex)->type != 'H'
		&& (*headLex)->type != 'D')
	{
		if (organiz_else_two(headLex, data, ptr, shell) == 1)
			return (1);
	}
	return (0);
}

int	len_list(t_list *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	**get_arre_envs(t_list *head)
{
	int		i;
	char	**ptr;

	i = len_list(head);
	ptr = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (head)
	{
		if (!head->value)
			ptr[i] = ft_strdup(head->var);
		else
			ptr[i] = ft_strjoin2(head->var, head->value);
		i++;
		head = head->next;
	}
	ptr[i] = NULL;
	return (ptr);
}
