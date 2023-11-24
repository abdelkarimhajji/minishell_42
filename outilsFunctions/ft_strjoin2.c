/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:16:56 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/10 20:28:43 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		j;
	int		count;
	char	*p;
	int		len_s1;
	int		len_s2;

	j = 0;
	count = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 == 0 && len_s2 == 0)
		return (0);
	p = malloc(len_s1 + len_s2 + 2);
	if (!p)
		return (0);
	while (count < len_s1)
	{
		p[count] = s1[count];
		count++;
	}
	p[count++] = '=';
	while (count < (len_s1 + len_s2) + 1)
		p[count++] = s2[j++];
	p[count] = '\0';
	return (p);
}
