/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizComands7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:10:17 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:40:00 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_arr_envs(char **ptr)
{
	int		i;
	char	**darr;

	i = 0;
	while (ptr[i])
		i++;
	darr = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (ptr[i])
	{
		darr[i] = ft_strdup(ptr[i]);
		i++;
	}
	darr[i] = NULL;
	return (darr);
}

void	int_struct_inmbg(t_minishell *data, char **ptr)
{
	data->pguist = 1;
	data->valid = 0;
	data->valid2 = 1;
	data->valid3 = 1;
	data->valid4 = 1;
	data->valid5 = 1;
	data->j = 0;
	*ptr = NULL;
}

void	organiz_comand_f(char **ptr, t_cmd *tmp2,
	t_minishell *data, t_listLex	*tmp)
{
	if (*ptr != NULL)
	{
		if (data->valid2 == 0)
			organiz_comandvalid2(tmp2, ptr, data);
		else if (data->valid3 == 0)
			organiz_comandvalid3(tmp2, ptr, data);
		else if (data->valid4 == 0)
			organiz_comandvalid4(tmp2, ptr, data);
		else if (data->valid5 == 0)
			organiz_comandvalid5(tmp2, ptr, data, tmp);
		else if (data->valid == 0)
			organiz_comandvalid(tmp2, ptr, data);
		else
		{
			tmp2->args[data->j] = ft_strdup(*ptr);
			data->j++;
		}
		free(*ptr);
		*ptr = NULL;
	}
}

void	organiz_comand_if_two(t_listLex *tmp, t_minishell *data)
{
	if (tmp->type == '<' || tmp->type == '>' || tmp->type == 'H'
		|| tmp->type == 'D')
	{
		if (tmp->type == '<')
			data->valid2 = 0;
		if (tmp->type == '>')
			data->valid3 = 0;
		if (tmp->type == 'D')
			data->valid4 = 0;
		if (tmp->type == 'H')
			data->valid5 = 0;
		data->pguist = 0;
	}
}

void	int_struct_comand(t_listLex **headLex, t_cmd **command, t_listLex **tmp,
		t_cmd **tmp2)
{
	*tmp = *headLex;
	newlst_add_front_back_comand(command);
	*tmp2 = *command;
	(*tmp2)->args = ft_calloc((leng_args(*tmp) + 1), sizeof(char *));
}
