/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:11:04 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/15 21:00:56 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_ptr_input_two(t_minishell *data, int *i)
{
	data->ptr_input[*i] = 2;
	while (data->ptr_input[*i] && data->ptr_input[*i] != '\'')
	{
		if (data->ptr_input[*i] == ' ')
			data->ptr_input[*i] = 3;
		(*i)++;
	}
	if (data->ptr_input[*i] == '\'')
		data->ptr_input[*i] = 2;
}

void	update_ptr_input(t_minishell *data)
{
	int	i;

	i = 0;
	while (data->ptr_input[i])
	{
		if (data->ptr_input[i] == '"')
		{
			data->ptr_input[i] = 1;
			while (data->ptr_input[i] && data->ptr_input[i] != '"')
			{
				if (data->ptr_input[i] == ' ')
					data->ptr_input[i] = 3;
				i++;
			}
			if (data->ptr_input[i] == '"')
				data->ptr_input[i] = 1;
		}
		else if (data->ptr_input[i] == '\'')
			update_ptr_input_two(data, &i);
		i++;
	}
}

int	len_word_doblex(int i, t_minishell *data)
{
	int	j;

	j = 0;
	while (data->ptr_input[i] && data->ptr_input[i] != ' '
		&& data->ptr_input[i] != 1)
	{
		j++;
		i++;
	}
	return (j);
}

void	if_doble_cot(t_minishell *data, int *i, t_listLex **headLex)
{
	char	*ptr;
	int		j;

	j = 0;
	ptr = malloc((len_word_doblex(*i, data) + 1) * sizeof(char));
	while (data->ptr_input[*i] && data->ptr_input[*i] != 2
		&& data->ptr_input[*i] != ' ' && data->ptr_input[*i] != 1
		&& data->ptr_input[*i + 1] != '$' && ((data->ptr_input[*i] >= 'a'
				&& data->ptr_input[*i] <= 'z') || (data->ptr_input[*i] >= 'A'
				&& data->ptr_input[*i] <= 'Z') || (data->ptr_input[*i] >= '0'
				&& data->ptr_input[*i] <= '9') || data->ptr_input[*i] == '$'))
	{
		if (data->ptr_input[*i] == 3)
			data->ptr_input[*i] = ' ';
		ptr[j] = data->ptr_input[*i];
		*i = *i + 1;
		j++;
	}
	ptr[j] = '\0';
	*i = *i - 1;
	newlst_add_front_back(ptr, headLex, 1);
	free(ptr);
}

void	else_doble_cot(t_minishell *data, int *i, t_listLex **headLex)
{
	int		j;
	char	*ptr;

	j = 0;
	ptr = malloc(len_word_doblex(*i, data) + 1);
	while (data->ptr_input[*i] && data->ptr_input[*i] != ' '
		&& data->ptr_input[*i] != '$' && data->ptr_input[*i] != 1
		&& data->ptr_input[*i] != 2)
	{
		if (data->ptr_input[*i] == 3)
			data->ptr_input[*i] = ' ';
		if (data->ptr_input[*i] == 4)
			data->ptr_input[*i] = '$';
		ptr[j] = data->ptr_input[*i];
		*i = *i + 1;
		j++;
	}
	ptr[j] = '\0';
	*i = *i - 1;
	newlst_add_front_back(ptr, headLex, 1);
	free(ptr);
}
