/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellPart3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:15:11 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 20:04:41 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command2(t_cmd *command)
{
	int	i;

	i = 0;
	while (command->args[i])
	{
		free(command->args[i]);
		command->args[i] = NULL;
		i++;
	}
	free(command->args);
}

void	free_command(t_cmd *command)
{
	t_cmd	*command2;
	t_file	*file;
	t_file	*file2;

	while (command)
	{
		command2 = command;
		file = command->file;
		if (command->cmd != NULL)
			free(command->cmd);
		free_command2(command);
		while (file != NULL)
		{
			file2 = file;
			file = file->next;
			free(file2->name);
			free(file2);
		}
		command = command->next;
		free(command2);
	}
}

void	free_headlex(t_listLex **headLex)
{
	t_listLex	*tmp;

	while (*headLex != NULL)
	{
		tmp = (*headLex);
		*headLex = (*headLex)->next;
		free((tmp)->content);
		free(tmp);
	}
}
