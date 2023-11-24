/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:11:10 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 20:10:53 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str_array(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(arr);
	arr = NULL;
}

void	free_file_struct(t_cmd *cmd)
{
	t_file	*temp;

	while (cmd->file != NULL)
	{
		temp = cmd->file;
		cmd->file = cmd->file->next;
		free(temp->name);
		free(temp);
	}
}

void	free_var_list(t_list **head)
{
	t_list	*temp;
	t_list	*temp2;

	temp = *head;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp2->next;
		free(temp2->var);
		free(temp2->value);
		free(temp2);
	}
	*head = NULL;
}

void	free_shell_struct(t_shell *shell)
{
	if (shell->curr_dir != NULL)
		free(shell->curr_dir);
	shell->curr_dir = NULL;
	if (shell->path != NULL)
		free(shell->path);
	shell->path = NULL;
	free_str_array(shell->env);
	shell->env = NULL;
	free_command(shell->cmds);
	free_var_list(shell->var);
}

void	all_free(t_shell *shell, t_cmd **command, t_listLex **headLex,
		char **ptr_input)
{
	free_command(*command);
	*command = NULL;
	shell->cmds = NULL;
	free_headlex(headLex);
	*headLex = NULL;
	free(*ptr_input);
}
