/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:22:30 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 15:23:04 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_node(t_list *list, char *val)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->var, val) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	update_char_env(t_shell *shell, char *path)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strnstr(shell->env[i], "PWD", ft_strlen("PWD")) != NULL)
		{
			free(shell->env[i]);
			shell->env[i] = my_strjoin("PWD=", path);
		}
		else if (ft_strnstr(shell->env[i], "OLDPWD",
				ft_strlen("OLDPWD")) != NULL)
		{
			free(shell->env[i]);
			shell->env[i] = my_strjoin("OLDPWD=", shell->curr_dir);
		}
		i++;
	}
}

void	update_list_env(t_shell *shell, char *path)
{
	t_list	*curr_dir;
	t_list	*old_dir;

	curr_dir = get_node(*(shell->var), "PWD");
	old_dir = get_node(*(shell->var), "OLDPWD");
	if (curr_dir != NULL)
	{
		free(curr_dir->value);
		curr_dir->value = ft_strdup(path);
	}
	if (old_dir != NULL)
	{
		free(old_dir->value);
		old_dir->value = ft_strdup(shell->curr_dir);
	}
}

void	update_env(t_shell *shell, char *path)
{
	update_char_env(shell, path);
	update_list_env(shell, path);
	free(shell->curr_dir);
	shell->curr_dir = ft_strdup(path);
}
