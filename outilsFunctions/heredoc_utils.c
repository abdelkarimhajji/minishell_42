/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:57:25 by nachab            #+#    #+#             */
/*   Updated: 2023/06/19 16:03:55 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *line)
{
	int		i;
	char	*no_quotes;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			break ;
		i++;
	}
	if (i == 0)
		return (NULL);
	no_quotes = malloc(sizeof(char) * i + 1);
	i = 0;
	while (line[i] && line[i] != '\'' && line[i] != '"')
	{
		no_quotes[i] = line[i];
		i++;
	}
	no_quotes[i] = '\0';
	return (no_quotes);
}

void	handle_quotes(char *line, int *pipe, t_list *vars)
{
	char	*no_quotes;
	t_list	*node;

	while (*line && (*line == '\'' || *line == '"'))
	{
		write(pipe[1], line, 1);
		line++;
	}
	no_quotes = remove_quotes(line);
	if (no_quotes != NULL)
	{
		node = get_node(vars, no_quotes);
		if (node != NULL)
			write(pipe[1], node->value, ft_strlen(node->value));
		while (*line)
		{
			if (*line == '\'' || *line == '"')
				write(pipe[1], line, 1);
			line++;
		}
		free(no_quotes);
	}
}

int	expand_herdc_var(t_shell *shell, char *input, int *pipe)
{
	char	**env;
	char	**temp;
	t_list	*node;

	env = ft_split(input, '$');
	temp = env;
	while (*env)
	{
		if (ft_strchr(*env, '\'') != NULL || ft_strchr(*env, '"'))
			handle_quotes(*env, pipe, *(shell->var));
		else if (**env == '?')
			ft_putnbr_fd(shell->exit_status, pipe[1]);
		else
		{
			node = get_node(*(shell->var), *env);
			if (node != NULL)
				write(pipe[1], node->value, ft_strlen(node->value));
		}
		env++;
	}
	free_str_array(temp);
	return (0);
}

int	handle_input(t_shell *shell, char *input, int *fds, char *delim)
{
	if (input == NULL)
		return (1);
	else if (ft_strcmp(input, delim) == 0)
	{
		free(input);
		return (1);
	}
	else if (ft_strchr(input, '$') != NULL && !g_info.hrdc_quotes)
		expand_herdc_var(shell, input, fds);
	else
		write(fds[1], input, ft_strlen(input));
	write(fds[1], "\n", 1);
	return (0);
}
