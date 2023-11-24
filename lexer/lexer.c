/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 01:03:18 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:06:43 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_conditions_two(t_minishell *data, t_listLex **headLex, int *i)
{
	if (check_ptri_si(data, *i) == 1 && *i > 0 && data->ptr_input[*i - 1] == 2)
		lexer_else_if_five(data, headLex, i);
	else if (data->ptr_input[*i] == '>' && data->ptr_input[*i + 1] != '>')
		lexer_else_if_six(headLex);
	else if (data->ptr_input[*i] == '<' && data->ptr_input[*i + 1] != '<')
		lexer_else_if_seven(headLex);
	else if (data->ptr_input[*i] == '<' && data->ptr_input[*i + 1] == '<')
		lexer_else_if_eight(headLex, i);
	else if (data->ptr_input[*i] == '>' && data->ptr_input[*i + 1] == '>')
		lexer_else_if_nine(headLex, i);
	else if (data->ptr_input[*i] == '$' && data->ptr_input[*i + 1] == '?')
		lexer_else_if_ten(headLex, i);
	else
		general_ptr(data, headLex, i);
}

void	lexer_conditions(t_minishell *data, t_listLex **headLex, int *i)
{
	int	valid;

	valid = 0;
	if (data->ptr_input[*i] == 1)
	{
		valid = 1;
		lexer_if(headLex);
	}
	else if (data->ptr_input[*i] == 2)
		lexer_else_if(headLex);
	else if (data->ptr_input[*i] == ' ')
		lexer_else_if_two(headLex);
	else if (data->ptr_input[*i] == '\t')
		lexer_else_if_tab(headLex);
	else if (data->ptr_input[*i] == '|')
		lexer_else_if_three(headLex);
	else if (check_ptri_d(data, *i) == 1 && *i > 0 && data->ptr_input[*i
			- 1] == 1)
	{
		valid = 0;
		lexer_else_if_for(data, headLex, i);
	}
	else
		lexer_conditions_two(data, headLex, i);
}

void	lexer(t_minishell *data, t_listLex **headLex)
{
	int	i;

	i = 0;
	update_ptr_input(data);
	while (data->ptr_input[i])
	{
		lexer_conditions(data, headLex, &i);
		i++;
	}
}
