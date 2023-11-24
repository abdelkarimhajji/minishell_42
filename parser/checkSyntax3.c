/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkSyntax3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:20:14 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:13:21 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_redirction_three(int *valid3,
									int *valid2,
									char *ch,
									t_shell *shell)
{
	if (*valid3 == 0 && *valid2 == 1)
	{
		if (*ch == 'D')
			perror("syntax error >>");
		else if (*ch == 'H')
			perror("syntax error <<");
		else
			printf("syntax error %c\n", *ch);
		shell->exit_status = 258;
		return (1);
	}
	return (0);
}

int	check_syntax_redirction(t_listLex *headLex, t_shell *shell)
{
	int		valid;
	int		valid2;
	int		valid3;
	char	ch;

	while (headLex)
	{
		valid3 = 1;
		valid2 = 1;
		valid = 1;
		if (headLex->type == '<' || headLex->type == '>' || headLex->type == 'H'
			|| headLex->type == 'D')
			check_syntax_redirction_two(headLex, &ch, &valid3, &valid2);
		if (check_syntax_redirction_three(&valid3, &valid2, &ch, shell) == 1)
			return (1);
		if (valid3 == 0)
		{
			valid3 = 1;
			valid2 = 1;
		}
		headLex = headLex->next;
	}
	return (0);
}
