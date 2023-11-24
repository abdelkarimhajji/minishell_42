/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizComands6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:06:29 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 16:39:50 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	organiz_comandvalid2(t_cmd *tmp2, char **ptr, t_minishell *data)
{
	newlst_add_front_back_file(&tmp2->file, *ptr, READ);
	data->pguist = 1;
	data->valid2 = 1;
}

void	organiz_comandvalid3(t_cmd *tmp2, char **ptr, t_minishell *data)
{
	newlst_add_front_back_file(&tmp2->file, *ptr, CREATE);
	data->pguist = 1;
	data->valid3 = 1;
}

void	organiz_comandvalid4(t_cmd *tmp2, char **ptr, t_minishell *data)
{
	newlst_add_front_back_file(&tmp2->file, *ptr, APPEND);
	data->pguist = 1;
	data->valid4 = 1;
}

void	organiz_comandvalid5(t_cmd *tmp2, char **ptr,
	t_minishell *data, t_listLex	*tmp)
{
	newlst_add_front_back_file(&tmp2->file, *ptr, HEREDOC);
	data->pguist = 1;
	data->valid5 = 1;
	if (tmp->type == '"' || tmp->type == '\'' || tmp->prev->type == '"')
		g_info.hrdc_quotes = 1;
}

void	organiz_comandvalid(t_cmd *tmp2, char **ptr, t_minishell *data)
{
	tmp2->cmd = ft_strdup(*ptr);
	tmp2->args[data->j] = ft_strdup(*ptr);
	data->j++;
	data->valid = 1;
}
