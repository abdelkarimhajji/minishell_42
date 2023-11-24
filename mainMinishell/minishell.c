/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:29:35 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 20:15:09 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_prompt2(char **ptr_input, t_minishell *data, t_listLex **headLex)
{
	g_info.hrdc_quotes = 0;
	history(*ptr_input);
	data->ptr_input = *ptr_input;
	lexer(data, headLex);
}

void	ctrl_d(t_shell *shell, t_listLex **headLex)
{
	free_shell_struct(shell);
	free_headlex(headLex);
	exit(shell->exit_status);
}

int	my_prompt(t_minishell *data, t_listLex **headLex, t_list **head)
{
	char	*ptr_input;
	t_cmd	*command;
	t_shell	shell;

	command = NULL;
	int_struct_shell(&shell, head);
	while (1)
	{
		ptr_input = readline("\033[0;32mminishell> \033[0m");
		if (ptr_input == NULL)
			ctrl_d(&shell, headLex);
		my_prompt2(&ptr_input, data, headLex);
		if (check_syntax(data, headLex, &shell) == 0)
		{
			expand_variable(headLex, head, data, shell);
			if (organiz_comands(headLex, data, &command, &shell) == 0)
			{
				shell.cmds = command;
				handle_cmd(&shell);
			}
		}
		all_free(&shell, &command, headLex, &ptr_input);
	}
	return (1);
}

int	main(int ac, char **av, char **en)
{
	t_minishell	data;
	t_list		*head;
	t_listLex	*headlex;

	head = NULL;
	headlex = NULL;
	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	newlist_and_add(&head, en);
	if (my_prompt(&data, &headlex, &head) == 0)
	{
		free_list(&head);
		return (0);
	}
	return (0);
}
