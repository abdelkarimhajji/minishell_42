/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:22:30 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:43:30 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ptri_d(t_minishell *data, int i)
{
	while (data->ptr_input[i] && data->ptr_input[i] != 1)
		i++;
	if (data->ptr_input[i] == 1)
		return (1);
	return (0);
}

int	check_ptri_si(t_minishell *data, int i)
{
	while (data->ptr_input[i] && data->ptr_input[i] != 2)
		i++;
	if (data->ptr_input[i] == 2)
		return (1);
	return (0);
}

void	lexer_if(t_listLex **headLex)
{
	char	*ptr;

	ptr = malloc(sizeof(char) + 1);
	ptr[0] = '"';
	ptr[1] = '\0';
	newlst_add_front_back(ptr, headLex, -1);
	free(ptr);
}

void	lexer_else_if(t_listLex **headLex)
{
	char	*ptr;

	ptr = malloc(sizeof(char) + 1);
	ptr[0] = '\'';
	ptr[1] = '\0';
	newlst_add_front_back(ptr, headLex, -1);
	free(ptr);
}

void	lexer_else_if_two(t_listLex	**headLex)
{
	char	*ptr;

	ptr = malloc(sizeof(char) + 1);
	ptr[0] = ' ';
	ptr[1] = '\0';
	newlst_add_front_back(ptr, headLex, 0);
	free(ptr);
}
