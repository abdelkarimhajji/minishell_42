/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outilLexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:46:41 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:08:07 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_state(char *ptr, int state)
{
	int	i;

	i = 0;
	if (state == 1)
		return ('2');
	else if (state == 2)
		return ('1');
	else
		return ('0');
	if (ptr[0] == '"' && ptr[1] == '\0')
		return ('0');
	else if (ptr[0] == '\'' && ptr[1] == '\0')
		return ('0');
	else if (ptr[0] == ' ' && ptr[1] == '\0')
		return ('0');
	return (0);
}

int	return_type_two(char *ptr, int i, int state)
{
	if (ptr[i] == ' ' && ptr[i + 1] == '\0')
		return (' ');
	else if (ptr[i] == '\t' && ptr[i + 1] == '\0')
		return ('\t');
	else if (ptr[i] == '|' && ptr[i + 1] == '\0')
		return ('|');
	else if (ptr[i] == '<' && ptr[i + 1] == '\0')
		return ('<');
	else if (ptr[i] == '>' && ptr[i + 1] == '\0')
		return ('>');
	else if (ptr[i] == '>' && ptr[i + 1] == '>' && ptr[i + 2] == '\0')
		return ('D');
	else if (ptr[i] == '<' && ptr[i + 1] == '<' && ptr[i + 2] == '\0')
		return ('H');
	if (state == 0)
		return ('W');
	return (0);
}

int	return_type(char *ptr, int state)
{
	int	i;

	i = 0;
	if (ptr[0] == '$' && ((ptr[1] >= 'a' && ptr[1] <= 'z') || (ptr[1] >= 'A'
				&& ptr[1] <= 'Z') || ptr[1] == '_'))
		return ('V');
	while (ptr[i])
	{
		if (state == 1 || state == 2)
			return ('W');
		if (ptr[i] == '"' && ptr[i + 1] == '\0')
			return ('"');
		else if (ptr[i] == '$' && ptr[i + 1] == '?' && ptr[i + 2] == '\0')
			return ('E');
		else if (ptr[i] == '\'' && ptr[i + 1] == '\0')
			return ('\'');
		else
		{
			if (return_type_two(ptr, i, state) != 0)
				return (return_type_two(ptr, i, state));
		}
		i++;
	}
	return (0);
}
