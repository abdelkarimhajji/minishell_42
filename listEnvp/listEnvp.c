/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listEnvp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:03:01 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 19:39:25 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_list	*lst_new(char *en)
{
	t_list	*node;
	char	**dptr;
	int		i;

	i = 0;
	dptr = ft_split(en, '=');
	node = malloc(sizeof(t_list));
	if (!node)
	{
		while (dptr[i])
			free(dptr[i++]);
		return (free(dptr), NULL);
	}
	node->var = ft_strdup(dptr[0]);
	if (ft_strchr(en, '=') != NULL)
		node->value = ft_strdup(ft_strchr(en, '='));
	else
		node->value = ft_calloc(1, 1);
	while (dptr[i])
		free(dptr[i++]);
	free(dptr);
	if (check_equal(en) == 1)
		node->valid = 1;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstlast(t_list *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	ft_lstadd_back(t_list **head, t_list *new_list)
{
	t_list	*node;

	if (*head == NULL)
	{
		*head = new_list;
		(*head)->next = NULL;
		return ;
	}
	node = ft_lstlast(*head);
	node->next = new_list;
	new_list->next = NULL;
}

void	newlist_and_add(t_list **head, char **en)
{
	int		i;
	t_list	*new_list;

	i = 0;
	while (en[i])
	{
		new_list = lst_new(en[i]);
		ft_lstadd_back(head, new_list);
		i++;
	}
}
