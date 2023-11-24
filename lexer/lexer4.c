/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:17:44 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:04:37 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_and_return(t_minishell *data, int i)
{
	if (data->ptr_input[i + 1] == '$' && data->ptr_input[i]
		&& data->ptr_input[i] != 2 && data->ptr_input[i] != ' '
		&& data->ptr_input[i] != 1 && ((data->ptr_input[i] >= 'a'
				&& data->ptr_input[i] <= 'z') || (data->ptr_input[i] >= 'A'
				&& data->ptr_input[i] <= 'Z') || (data->ptr_input[i] >= '0'
				&& data->ptr_input[i] <= '9') || data->ptr_input[i] == '$'))
		return (1);
	return (0);
}

void	get_var_gen_three(t_minishell *data, int *i,
		char **ptr)
{
	while (data->ptr_input[*i] && data->ptr_input[*i] != 2
		&& data->ptr_input[*i] != ' ' && data->ptr_input[*i] != 1
		&& ((data->ptr_input[*i] >= 'a' && data->ptr_input[*i] <= 'z')
			|| (data->ptr_input[*i] >= 'A' && data->ptr_input[*i] <= 'Z')
			|| (data->ptr_input[*i] >= '0' && data->ptr_input[*i] <= '9')
			|| data->ptr_input[*i] == '$' || data->ptr_input[*i] == '_'))
	{
		if (data->ptr_input[*i] == 3)
			data->ptr_input[*i] = ' ';
		(*ptr)[data->count] = data->ptr_input[*i];
		*i = *i + 1;
		data->count++;
		if (check_and_return(data, *i) == 1)
		{
			(*ptr)[data->count++] = data->ptr_input[*i];
			*i = *i + 1;
			break ;
		}
	}
}

void	get_var_gen(t_minishell *data, t_listLex **headLex, int *i)
{
	char	*ptr;

	data->count = 0;
	ptr = malloc((len_word_lex(*i, data) + 1) * sizeof(char));
	get_var_gen_three(data, i, &ptr);
	ptr[data->count] = '\0';
	*i = *i - 1;
	newlst_add_front_back(ptr, headLex, 0);
	free(ptr);
}

void	general_ptr_two(t_minishell *data, char **ptr, int *i, int *j)
{
	while (data->ptr_input[*i] && data->ptr_input[*i] != 2
		&& data->ptr_input[*i] != ' ' && data->ptr_input[*i] != 1
		&& data->ptr_input[*i] != '$' && data->ptr_input[*i] != '|'
		&& data->ptr_input[*i] != '<' && data->ptr_input[*i] != '>')
	{
		if (data->ptr_input[*i] == 3)
			data->ptr_input[*i] = ' ';
		(*ptr)[*j] = data->ptr_input[*i];
		*i = *i + 1;
		*j = *j + 1;
	}
}

void	general_ptr(t_minishell	*data, t_listLex	**headLex, int *i)
{
	int		j;
	char	*ptr;

	j = 0;
	if (data->ptr_input[*i] == '$')
		get_var_gen(data, headLex, i);
	else
	{
		ptr = malloc((len_word_lex(*i, data) + 1) * sizeof(char));
		general_ptr_two(data, &ptr, i, &j);
		ptr[j] = '\0';
		if (data->ptr_input[*i] == 2 || data->ptr_input[*i] == 1
			|| data->ptr_input[*i] == ' ' || data->ptr_input[*i] == '$'
			|| data->ptr_input[*i] == '|' || data->ptr_input[*i] == '<'
			|| data->ptr_input[*i] == '>' || data->ptr_input[*i] == '\0')
			*i = *i - 1;
		newlst_add_front_back(ptr, headLex, 0);
		free(ptr);
	}
}
