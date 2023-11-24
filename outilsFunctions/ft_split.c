/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:29:28 by ahajji            #+#    #+#             */
/*   Updated: 2023/05/05 23:13:58 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	lenword(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static size_t	lenofword(char const *s, char c, size_t *j)
{
	size_t	i;

	i = 0;
	while (s[*j])
	{
		if ((*j == 0 && s[*j] != c) || (s[*j] != c && s[*j - 1] == c))
		{
			while (s[*j] != c && s[*j])
			{
				i++;
				*j = *j + 1;
			}
			return (i);
		}
		*j = *j + 1;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	k;
	size_t	j;
	size_t	f;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	array = (char **)malloc((lenword(s, c) + 1) * sizeof(char *));
	if (!array)
		return (0);
	while (i < lenword(s, c))
	{
		k = lenofword(s, c, &j);
		f = j - k;
		array[i] = ft_substr(s, f, k);
		i++;
	}
	array[lenword(s, c)] = 0;
	return (array);
}
