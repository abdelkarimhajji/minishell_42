/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:13:11 by ahajji            #+#    #+#             */
/*   Updated: 2023/05/07 19:11:07 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		j;
	char	*p;

	len = ft_strlen(s1) + 1;
	p = malloc(len);
	if (!p)
		return (0);
	j = 0;
	while (s1[j])
	{
		p[j] = s1[j];
		j++;
	}
	p[j] = '\0';
	return (p);
}
