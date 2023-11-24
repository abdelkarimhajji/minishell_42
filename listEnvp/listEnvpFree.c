/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listEnvpFree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:29:25 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/15 21:08:01 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_list **head)
{
	while (*head != NULL)
	{
		free((*head)->var);
		free((*head)->value);
		free(*head);
		*head = (*head)->next;
	}
}

void	add_to_istvar(t_list **head, char *tmp)
{
	t_list	*new_list;

	new_list = lst_new(tmp);
	ft_lstadd_back(head, new_list);
}
