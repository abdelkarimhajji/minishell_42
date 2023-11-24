/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizComands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:03:15 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:35:22 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	organiz_comand_if_else(t_listLex **tmp, t_minishell *data, char **ptr,
		t_shell *shell)
{
	if ((*tmp)->type == '"' || (*tmp)->type == '\'')
	{
		if ((*tmp)->next != NULL && (((*tmp)->type == '"'
					&& (*tmp)->next->type == '"') || ((*tmp)->type == '\''
					&& (*tmp)->next->type == '\'')))
		{
			*ptr = malloc(1);
			**ptr = '\0';
		}
		if (organiz_dobl_sing(tmp, data, ptr, shell) == 1)
			return (1);
	}
	else if ((*tmp)->type != ' ' && (*tmp)->type != '\t'
		&& (*tmp)->type != '|' && (*tmp)->type != '<'
		&& (*tmp)->type != '>' && (*tmp)->type != 'H'
		&& (*tmp)->type != 'D')
	{
		if (organiz_else(tmp, data, ptr, shell) == 1)
			return (1);
	}
	return (0);
}

void	organiz_comand_if_three(t_listLex *tmp, t_minishell *data, t_cmd **tmp2,
		char **ptr)
{
	if (tmp->type == '|')
	{
		(*tmp2)->args[data->j] = NULL;
		data->j = 0;
		(*tmp2)->pipe = 1;
		newlst_add_front_back_comand(tmp2);
		(*tmp2) = (*tmp2)->next;
		(*tmp2)->args = ft_calloc((leng_args(tmp) + 1), sizeof(char *));
		(*tmp2)->pipe = 1;
		data->valid = 0;
		ptr = NULL;
	}
}

int	organiz_comands(t_listLex **headLex, t_minishell *data, t_cmd **command,
		t_shell *shell)
{
	t_listLex	*tmp;
	t_cmd		*tmp2;
	char		*ptr;
	int			i;

	data->begnext = 0;
	data->begprev = 1;
	int_struct_inmbg(data, &ptr);
	if ((*headLex) == NULL)
		return (1);
	int_struct_comand(headLex, command, &tmp, &tmp2);
	while (tmp)
	{
		if (organiz_comand_if_else(&tmp, data, &ptr, shell) == 1)
			return (1);
		organiz_comand_f(&ptr, tmp2, data, tmp);
		organiz_comand_if_two(tmp, data);
		organiz_comand_if_three(tmp, data, &tmp2, &ptr);
		tmp = tmp->next;
	}
	tmp2->args[data->j] = NULL;
	i = 0;
	tmp2 = *command;
	return (0);
}
// int i = 0;
//     tmp2 = *command;

//     int k;
//     k = 0;
//     while (tmp2)
//     {
//         printf("piiiiiipe %d\n", tmp2->pipe);
//         file = tmp2->file;
//         printf("comand : %s,\n", tmp2->cmd);
//         i = 0;
//         while (tmp2->args[i])
//         {
//             printf("args : %s,\n", tmp2->args[i]);
//            i++;
//         }
//         while (file)
//         {
//             // printf("---> k %d\n", k);
//             printf("file : %s, mode %d\n", file->name, file->mode);
//             file = file->next;
//         }
//         // // k++;
//         tmp2 = tmp2->next;
//     }