/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:39:24 by ahajji            #+#    #+#             */
/*   Updated: 2023/05/31 15:28:41 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long	lenint(long n)
{
	long	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	n2;
	long	count;
	char	*p;

	n2 = n;
	count = lenint(n2);
	p = malloc((count + 1) * sizeof(char));
	if (!p)
		return (0);
	if (n < 0)
	{
		n2 = n2 * -1;
		p[0] = '-';
	}
	p[count] = '\0';
	count--;
	if (n == 0)
		p[count] = '0';
	while (n2 > 0)
	{
		p[count] = (n2 % 10) + 48;
		n2 /= 10;
		count--;
	}
	return (p);
}
