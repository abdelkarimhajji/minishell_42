/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:13:09 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:01:46 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dobule_cot_ptr(t_minishell *data, t_listLex **headLex, int *i)
{
	char	*ptr;

	while (data->ptr_input[*i] && data->ptr_input[*i] != 1
		&& data->ptr_input[*i] != 2)
	{
		if (data->ptr_input[*i] == '$' && data->ptr_input[*i + 1] == '?')
		{
			ptr = malloc(3);
			ptr[0] = '$';
			ptr[1] = '?';
			ptr[2] = '\0';
			newlst_add_front_back(ptr, headLex, 0);
			free(ptr);
			*i = *i + 1;
		}
		else if (data->ptr_input[*i] == '$')
			if_doble_cot(data, i, headLex);
		else
			else_doble_cot(data, i, headLex);
		*i = *i + 1;
	}
	if (data->ptr_input[*i] == 1 || data->ptr_input[*i] == 2)
		*i = *i - 1;
}

int	len_sengle_cot(t_minishell *data, int i)
{
	int	j;

	j = 0;
	while (data->ptr_input[i] && data->ptr_input[i] != 2
		&& data->ptr_input[i] != ' ')
	{
		j++;
		i++;
	}
	return (j);
}

void	sengle_cot_ptr(t_minishell *data, t_listLex **headLex, int *i)
{
	char	*ptr;
	int		j;

	j = len_sengle_cot(data, *i);
	ptr = malloc(j + 1);
	j = 0;
	while (data->ptr_input[*i] && data->ptr_input[*i] != 2
		&& data->ptr_input[*i] != ' ' && data->ptr_input[*i] != 1)
	{
		if (data->ptr_input[*i] == 3)
			data->ptr_input[*i] = ' ';
		ptr[j] = data->ptr_input[*i];
		*i = *i + 1;
		j++;
	}
	ptr[j] = '\0';
	if (data->ptr_input[*i] == 2 || data->ptr_input[*i] == 1)
		*i = *i - 1;
	newlst_add_front_back(ptr, headLex, 2);
	free(ptr);
}

int	len_word_lex(int i, t_minishell *data)
{
	int	j;

	j = 0;
	while (data->ptr_input[i])
	{
		j++;
		i++;
	}
	return (j);
}

int	get_var_gen_two(t_minishell *data, int *i, char **ptr)
{
	if (data->ptr_input[*i] == 3)
		data->ptr_input[*i] = ' ';
	*ptr[data->count] = data->ptr_input[*i];
	*i = *i + 1;
	data->count++;
	if (data->ptr_input[*i + 1] == '$' && data->ptr_input[*i]
		&& data->ptr_input[*i] != 2 && data->ptr_input[*i] != ' '
		&& data->ptr_input[*i] != 1 && ((data->ptr_input[*i] >= 'a'
				&& data->ptr_input[*i] <= 'z') || (data->ptr_input[*i] >= 'A'
				&& data->ptr_input[*i] <= 'Z') || (data->ptr_input[*i] >= '0'
				&& data->ptr_input[*i] <= '9') || data->ptr_input[*i] == '$'))
	{
		*ptr[data->count] = data->ptr_input[*i];
		data->count++;
		*i = *i + 1;
		return (1);
	}
	return (0);
}
