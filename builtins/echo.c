/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:16:30 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 17:46:04 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(char *arg)
{
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (ERROR);
		arg++;
	}
	return (SUCCESS);
}

int	echo(char **args)
{
	int	newline;

	newline = 1;
	args++;
	while (*args != NULL && ft_strncmp(*args, "-n", 2) == 0)
	{
		if (check_option(*args) == ERROR)
			break ;
		args++;
		newline = 0;
	}
	while (*args != NULL)
	{
		printf("%s", *args);
		if (*(args + 1) != NULL)
			printf(" ");
		args++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
