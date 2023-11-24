/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:55:18 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 17:01:19 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (len == 0 || (size_t)start >= (size_t)ft_strlen(s))
	{
		p = malloc(1);
		p[0] = '\0';
		return (p);
	}
	p = malloc(len + 1);
	if (!p)
		return (0);
	while (s[start] && j < len)
		p[j++] = s[start++];
	p[j] = '\0';
	return (p);
}
