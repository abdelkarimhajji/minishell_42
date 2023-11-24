/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listFiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:43:44 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/15 20:14:13 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file	*lst_new_file(char *ptr, int mode)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node)
		return (0);
	node->name = ft_strdup(ptr);
	node->mode = mode;
	node->next = NULL;
	return (node);
}

t_file	*lst_last_file(t_file *last)
{
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	add_back_front_file(t_file **haedLex, t_file *new_list)
{
	t_file	*node;

	if (*haedLex == NULL)
	{
		*haedLex = new_list;
		(*haedLex)->next = NULL;
		return ;
	}
	node = lst_last_file(*haedLex);
	node->next = new_list;
}

void	newlst_add_front_back_file(t_file **headLex, char *ptr, int mode)
{
	t_file	*new_list;

	new_list = lst_new_file(ptr, mode);
	add_back_front_file(headLex, new_list);
}
