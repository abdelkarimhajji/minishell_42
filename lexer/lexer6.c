/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:24:39 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:10:55 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_else_if_three(t_listLex **headLex)
{
	char	*ptr;

	ptr = malloc(sizeof(char) + 1);
	ptr[0] = '|';
	ptr[1] = '\0';
	newlst_add_front_back(ptr, headLex, -1);
	free(ptr);
}

void	lexer_else_if_for(t_minishell *data, t_listLex **headLex, int *i)
{
	char	*ptr;

	data->ptr_input[*i - 1] = '"';
	dobule_cot_ptr(data, headLex, i);
	if (data->ptr_input[*i + 1] == 1)
	{
		data->ptr_input[*i + 1] = '"';
		ptr = malloc(sizeof(char) + 1);
		ptr[0] = '"';
		ptr[1] = '\0';
		newlst_add_front_back(ptr, headLex, -1);
		free(ptr);
		*i = *i + 1;
	}
}

void	lexer_else_if_five(t_minishell *data, t_listLex **headLex, int *i)
{
	char	*ptr;

	data->ptr_input[*i - 1] = '\'';
	sengle_cot_ptr(data, headLex, i);
	if (data->ptr_input[*i + 1] == 2)
	{
		data->ptr_input[*i + 1] = '\'';
		ptr = malloc(sizeof(char) + 1);
		ptr[0] = '\'';
		ptr[1] = '\0';
		newlst_add_front_back(ptr, headLex, -1);
		free(ptr);
		*i = *i + 1;
	}
}

void	lexer_else_if_six(t_listLex **headLex)
{
	char	*ptr;

	ptr = malloc(sizeof(char) + 1);
	ptr[0] = '>';
	ptr[1] = '\0';
	newlst_add_front_back(ptr, headLex, -1);
	free(ptr);
}

void	lexer_else_if_seven(t_listLex	**headLex)
{
	char	*ptr;

	ptr = malloc(sizeof(char) + 1);
	ptr[0] = '<';
	ptr[1] = '\0';
	newlst_add_front_back(ptr, headLex, -1);
	free(ptr);
}
