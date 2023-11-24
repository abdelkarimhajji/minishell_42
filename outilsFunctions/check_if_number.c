/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:26:42 by nachab            #+#    #+#             */
/*   Updated: 2023/06/16 16:20:36 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	valid_number(char *arr)
{
	while (*arr == ' ' || *arr == '\t')
		arr++;
	if (*arr == '+' || *arr == '-')
		arr++;
	if (*arr == '\0')
		return (-1);
	while (*arr != '\0')
	{
		if (ft_isdigit(*arr) != 1 && *arr != ' ' && *arr != '\t')
			return (ERROR);
		arr++;
	}
	return (SUCCESS);
}

int	ft_atoi(char *nb)
{
	long	result;
	int		i;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	while (nb[i] == ' ')
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			sign *= -1;
		i++;
	}
	while (nb[i] && ft_isdigit(nb[i]) == 1)
	{
		result = result * 10;
		result = result + (nb[i] - 48);
		i++;
	}
	return (result * sign);
}
