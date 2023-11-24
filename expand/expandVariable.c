/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandVariable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:46:02 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 16:46:09 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable_six(t_listLex **tmp)
{
	free((*tmp)->content);
	(*tmp)->content = ft_strdup(" ");
}

void	expand_variable_seven(t_listLex **headLex, t_listLex **tmp)
{
	if (*tmp == *headLex)
		expand_variable_six(tmp);
	else if ((*tmp)->next == NULL)
		expand_variable_six(tmp);
	else
		expand_variable_six(tmp);
}

void	expand_variable(t_listLex **headLex, t_list **head, t_minishell *data,
		t_shell shell)
{
	t_listLex	*tmp;
	char		*ptr;
	int			valid;

	valid = 1;
	tmp = *headLex;
	while (tmp)
	{
		expand_variable_two(tmp, &ptr, shell);
		expand_variable_three(tmp, &valid);
		if (valid == 1 && tmp->type == 'V' && tmp->state != '1')
		{
			expand_variable_for(tmp, data);
			if (tmp->next == NULL)
				ptr = get_value_var(*head, tmp->content, tmp->state, data);
			else
				ptr = get_value_var(*head, tmp->content, tmp->state, data);
			if (ptr != NULL)
				expand_variable_five(tmp, &ptr);
			else
				expand_variable_seven(headLex, &tmp);
		}
		if (tmp)
			tmp = tmp->next;
	}
}
