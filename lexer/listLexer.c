/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listLexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:32:01 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:42:13 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_listLex	*lst_new_lex(char *ptr, int state)
{
	t_listLex	*node;

	node = malloc(sizeof(t_listLex));
	if (!node)
		return (0);
	node->content = ft_strdup(ptr);
	node->type = return_type(ptr, state);
	node->state = return_state(ptr, state);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_listLex	*lst_last_lex(t_listLex *last)
{
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	add_back_front(t_listLex **haedLex, t_listLex *new_list)
{
	t_listLex	*node;

	if (*haedLex == NULL)
	{
		*haedLex = new_list;
		(*haedLex)->next = NULL;
		(*haedLex)->prev = new_list;
		return ;
	}
	(*haedLex)->prev = *haedLex;
	node = lst_last_lex(*haedLex);
	node->next = new_list;
	new_list->prev = node;
}

void	newlst_add_front_back(char *part_input, t_listLex **headLex, int satate)
{
	t_listLex	*new_list;

	new_list = lst_new_lex(part_input, satate);
	add_back_front(headLex, new_list);
}
