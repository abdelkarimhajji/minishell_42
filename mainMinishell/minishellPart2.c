/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellPart2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:56:01 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/16 16:55:32 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spaces(char *ptr_input)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (ptr_input[i])
	{
		if (ptr_input[i] == ' ')
			j++;
		i++;
	}
	if (i == j)
		return (0);
	return (1);
}

void	history(char *ptr_input)
{
	if (ft_strlen(ptr_input) > 0 && check_spaces(ptr_input))
		add_history(ptr_input);
}

char	*get_var(t_list *head, char *var)
{
	while (head)
	{
		if (ft_strcmp(var, head->var) == 0)
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (NULL);
}

void	int_struct_shell(t_shell *shell, t_list **head)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		shell->curr_dir = ft_strdup(cwd);
	else
		perror("Error ");
	shell->env = get_arre_envs(*head);
	shell->cmds = NULL;
	shell->path = get_var(*head, "PATH");
	shell->var = head;
	shell->exit_status = 0;
}
