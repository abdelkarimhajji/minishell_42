/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:34:01 by nachab            #+#    #+#             */
/*   Updated: 2023/06/15 14:46:06 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	int	fd = open("test.txt", O_WRONLY);
	ft_putchar_fd('w', fd);
	return (0);
}*/
