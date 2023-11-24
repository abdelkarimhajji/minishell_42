/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:36:10 by nachab            #+#    #+#             */
/*   Updated: 2023/06/16 16:22:41 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_strjoin(char const *s1, char const *s2)
{
	char	*pt;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	size = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	pt = (char *)malloc(size * sizeof(char));
	if (pt == 0)
		return (0);
	while (s1[i] != '\0')
	{
		pt[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		pt[i++] = s2[j++];
	pt[i] = '\0';
	return (pt);
}
