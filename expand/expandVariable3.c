/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandVariable3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:13:48 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:48:00 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable_two(t_listLex *tmp, char **ptr, t_shell shell)
{
	if (tmp->type == 'E')
	{
		*ptr = ft_itoa(shell.exit_status);
		if (*ptr != NULL)
		{
			free(tmp->content);
			tmp->content = ft_strdup(*ptr);
			free(*ptr);
		}
	}
}

void	expand_variable_three(t_listLex *tmp, int *valid)
{
	if (tmp->type == '<' || tmp->type == '>' || tmp->type == 'H'
		|| tmp->type == 'D')
		*valid = 0;
	if (tmp->type == '|')
		*valid = 1;
}

void	expand_variable_for(t_listLex *tmp, t_minishell *data)
{
	if (tmp->next == NULL)
		data->begnext = -1;
	if (tmp->prev != tmp && tmp->prev->type != ' ')
		data->begprev = 0;
}

void	expand_variable_five(t_listLex *tmp, char **ptr)
{
	free(tmp->content);
	tmp->content = ft_strdup(*ptr);
	free(*ptr);
}
