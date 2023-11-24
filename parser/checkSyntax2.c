/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkSyntax2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:16:37 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 16:39:09 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_pipe_two_two(t_minishell *data, t_listLex *headLex,
		int *valid3, int *valid2)
{
	data->i++;
	*valid3 = 0;
	while (headLex->next)
	{
		if (headLex->type == 'W' || headLex->type == '>' || headLex->type == '>'
			|| headLex->type == 'H' || headLex->type == 'D'
			|| headLex->type == 'V' || headLex->type == '"'
			|| headLex->type == '\'')
			*valid2 = 0;
		if (headLex->next->type == '|')
			return (1);
		headLex = headLex->next;
	}
	if (headLex->type == 'W' || headLex->type == 'V' || headLex->type == '"'
		|| headLex->type == '\'')
		*valid2 = 0;
	return (0);
}

void	check_syntax_pipe_two(int *valid3, t_minishell *data, int *valid2,
		t_listLex **headLex)
{
	data->i++;
	*valid3 = 0;
	while ((*headLex)->next)
	{
		if ((*headLex)->type == 'W' || (*headLex)->type == '>'
			|| (*headLex)->type == '>' || (*headLex)->type == 'H'
			|| (*headLex)->type == 'D' || (*headLex)->type == 'V'
			|| (*headLex)->type == '"' || (*headLex)->type == '\'')
			*valid2 = 0;
		if ((*headLex)->next->type == '|')
			break ;
		(*headLex) = (*headLex)->next;
	}
}

int	check_syntax_pipe_three(t_shell *shell, int *valid3, int *valid,
		int *valid2)
{
	if (*valid3 == 0 && (*valid == 1 || *valid2 == 1))
	{
		shell->exit_status = 258;
		return (ft_putstr_fd("syntax error : |\n", 2), 1);
	}
	if (*valid3 == 0)
	{
		*valid3 = 1;
		*valid2 = 1;
	}
	return (0);
}

int	check_syntax_pipe(t_minishell *data, t_listLex *headLex, t_shell *shell)
{
	int	valid;
	int	valid2;
	int	valid3;

	valid3 = 1;
	valid2 = 1;
	valid = 1;
	data->i = 1;
	while (headLex)
	{
		if (headLex->type == 'W' || headLex->type == 'V' || headLex->type == '"'
			|| headLex->type == '\'')
			valid = 0;
		else if (headLex->type == '|')
		{
			check_syntax_pipe_two(&valid3, data, &valid2, &headLex);
			if (headLex->type == 'W' || headLex->type == 'V'
				|| headLex->type == '"' || headLex->type == '\'')
				valid2 = 0;
		}
		if (check_syntax_pipe_three(shell, &valid3, &valid, &valid2) == 1)
			return (1);
		headLex = headLex->next;
	}
	return (0);
}

void	check_syntax_redirction_two(t_listLex *headLex,
									char *ch,
									int *valid3,
									int *valid2)
{
	if (headLex->type == '<')
		*ch = '<';
	else if (headLex->type == '>')
		*ch = '>';
	else if (headLex->type == 'H')
		*ch = 'H';
	else if (headLex->type == 'D')
		*ch = 'D';
	*valid3 = 0;
	while (headLex->next)
	{
		if (headLex->type == 'W' || headLex->type == 'V' || headLex->type == '"'
			|| headLex->type == '\'')
			*valid2 = 0;
		if (headLex->next->type == '<' || headLex->next->type == '>')
			break ;
		headLex = headLex->next;
	}
	if (headLex->type == 'W' || headLex->type == 'V' || headLex->type == '"'
		|| headLex->type == '\'')
		*valid2 = 0;
}
