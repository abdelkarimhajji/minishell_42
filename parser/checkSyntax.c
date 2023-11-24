/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkSyntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:55:49 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:13:48 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dobl_cot_two(t_listLex **headLex, int *i, int *valid, int *valid2)
{
	*valid = 0;
	if ((*headLex)->next != NULL)
	{
		(*i)++;
		*headLex = (*headLex)->next;
	}
	while ((*headLex)->next && (*headLex)->type != '"')
	{
		(*i)++;
		*headLex = (*headLex)->next;
	}
	if ((*headLex)->type == '"' && *i > 0)
		*valid2 = 0;
	return (*valid == 1 || *valid2 == 1);
}

int	check_dobl_cot_three(t_listLex **headLex,
							int *i,
							int *valid,
							int *valid2)
{
	*valid = 0;
	if ((*headLex)->next != NULL)
	{
		(*i)++;
		*headLex = (*headLex)->next;
	}
	while ((*headLex)->next && (*headLex)->type != '\'')
	{
		(*i)++;
		*headLex = (*headLex)->next;
	}
	if ((*headLex)->type == '\'' && *i > 0)
		*valid2 = 0;
	return (*valid == 1 || *valid2 == 1);
}

int	check_dobl_cot(t_listLex *headLex, t_shell *shell)
{
	int	valid;
	int	valid2;
	int	i;

	while (headLex)
	{
		valid2 = 1;
		valid = 1;
		i = 0;
		if (headLex->type == '"'
			&& check_dobl_cot_two(&headLex, &i, &valid, &valid2) == 1)
		{
			shell->exit_status = 258;
			return (ft_putstr_fd("syntax error near unexpected token \"\n", 2),
				1);
		}
		else if (headLex->type == '\''
			&& check_dobl_cot_three(&headLex, &i, &valid, &valid2) == 1)
			return (shell->exit_status = 258,
				ft_putstr_fd("syntax error near unexpected token \'\n", 2), 1);
		headLex = headLex->next;
	}
	return (0);
}

int	check_syntax(t_minishell *data, t_listLex **headLex, t_shell *shell)
{
	if (check_dobl_cot(*headLex, shell) == 0)
	{
		if (check_syntax_redirction(*headLex, shell) == 0)
		{
			if (check_syntax_pipe(data, *headLex, shell) == 0)
				return (0);
			return (1);
		}
		return (1);
	}
	return (1);
}
