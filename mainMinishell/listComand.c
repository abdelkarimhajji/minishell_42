/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listComand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:35:50 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/15 20:13:32 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*lst_new_comand(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->env = NULL;
	node->path = NULL;
	node->pipe = 0;
	node->cmd = NULL;
	node->args = NULL;
	node->file = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*lst_last_comand(t_cmd *last)
{
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	add_back_front_comand(t_cmd **haedLex, t_cmd *new_list)
{
	t_cmd	*node;

	if (*haedLex == NULL)
	{
		*haedLex = new_list;
		(*haedLex)->next = NULL;
		return ;
	}
	node = lst_last_comand(*haedLex);
	node->next = new_list;
}

void	newlst_add_front_back_comand(t_cmd **headLex)
{
	t_cmd	*new_list;

	new_list = lst_new_comand();
	add_back_front_comand(headLex, new_list);
}
