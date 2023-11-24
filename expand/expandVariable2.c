/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandVariable2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:04:58 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:50:44 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_stb_two(char **ptr2, int *j, char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] != ' ' && ptr[i] != '\t')
		{
			(*ptr2)[*j] = ptr[i];
			*j = *j + 1;
		}
		if (ptr[i] != ' ' && ptr[i] != '\t' && (ptr[i + 1] == ' '
				|| ptr[i + 1] == '\t'))
		{
			(*ptr2)[*j] = ptr[i + 1];
			*j = *j + 1;
			i++;
		}
		i++;
	}
	(*ptr2)[*j] = '\0';
}

void	skip_stb_one(char **ptr2, int *j, char *ptr, int *i)
{
	*i = 0;
	if ((ptr[0] == ' ' || ptr[0] == '\t'))
	{
		if (ptr[0] == ' ')
			*ptr2[*j] = ' ';
		else
			*ptr2[*j] = '\t';
		(*j)++;
	}
}

void	skip_stb_three(char **ptr2, int *j, char *ptr, int i)
{
	if (ptr[i - 1] == ' ')
		*ptr2[(*j)++] = ' ';
	else
		*ptr2[(*j)++] = '\t';
	*ptr2[*j] = '\0';
}

char	*skip_sp_tb(char *ptr, t_minishell *data)
{
	int		i;
	char	*ptr2;
	int		valid;
	int		j;

	valid = 0;
	j = 0;
	i = 0;
	while (ptr[i])
		i++;
	ptr2 = malloc(i + 3);
	if (valid == 0 && data->begprev == 0)
		skip_stb_one(&ptr2, &j, ptr, &i);
	skip_stb_two(&ptr2, &j, ptr);
	if (data->begnext == 0 && i > 0 && j > 0 && (ptr[i - 1] == ' ' || ptr[i
				- 1] == '\t') && (ptr2[j - 1] != ' ' && ptr2[j - 1] != '\t'))
		skip_stb_three(&ptr2, &j, ptr, i);
	else
	{
		if (j > 0 && (ptr2[j - 1] == ' ' || ptr2[j - 1] == '\t')
			&& data->begnext != 0)
			ptr2[j - 1] = '\0';
	}
	free(ptr);
	return (ptr2);
}

char	*get_value_var(t_list *head, char *ptr, char state, t_minishell *data)
{
	char	*str;

	str = ft_strdup(ft_strchr(ptr, '$'));
	while (head)
	{
		if (ft_strcmp(str, head->var) == 0)
		{
			free(str);
			str = ft_strdup(head->value);
			if (state == '0')
				str = skip_sp_tb(str, data);
			return (str);
		}
		head = head->next;
	}
	free(str);
	return (NULL);
}
