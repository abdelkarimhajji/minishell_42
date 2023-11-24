/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:40:16 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:43:19 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_else_if_eight(t_listLex **headLex, int *i)
{
	char	*ptr;

	ptr = malloc(3);
	ptr[0] = '<';
	ptr[1] = '<';
	ptr[2] = '\0';
	newlst_add_front_back(ptr, headLex, -1);
	free(ptr);
	*i = *i + 1;
}

void	lexer_else_if_nine(t_listLex **headLex, int *i)
{
	char	*ptr;

	ptr = malloc(3);
	ptr[0] = '>';
	ptr[1] = '>';
	ptr[2] = '\0';
	newlst_add_front_back(ptr, headLex, -1);
	free(ptr);
	*i = *i + 1;
}

void	lexer_else_if_ten(t_listLex **headLex, int *i)
{
	char	*ptr;

	ptr = malloc(3);
	ptr[0] = '$';
	ptr[1] = '?';
	ptr[2] = '\0';
	newlst_add_front_back(ptr, headLex, 0);
	free(ptr);
	*i = *i + 1;
}

void	lexer_else_if_tab(t_listLex	**headLex)
{
	char	*ptr;

	ptr = malloc(sizeof(char) + 1);
	ptr[0] = '\t';
	ptr[1] = '\0';
	newlst_add_front_back(ptr, headLex, 0);
	free(ptr);
}
