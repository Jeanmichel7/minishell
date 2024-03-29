/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:13:01 by ydumaine          #+#    #+#             */
/*   Updated: 2023/09/01 23:19:51 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_convert_redi(t_data *data)
{
	int	i;
	int	u;
	int	j;

	i = 0;
	while (i <= data->nb_pipe)
	{
		j = 0;
		while (data->inputs[i].cmds && data->inputs[i].cmds[j])
		{
			u = 0;
			while (data->inputs[i].cmds[j][u])
			{
				if (data->inputs[i].cmds[j][u] == -1)
					data->inputs[i].cmds[j][u] = '>';
				if (data->inputs[i].cmds[j][u] == -2)
					data->inputs[i].cmds[j][u] = '<';
				u++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_fulling_input_cmds(char **cmd, char **ptr, int i, t_data *data)
{
	int	error;

	error = 0;
	if (cmd[i] != NULL)
		error = ft_which_redirection_take_on_board(cmd[i]);
	if (error != 0)
		return (error);
	ptr = ft_split_and_omit(cmd[i], ' ', 0);
	if (ptr == NULL)
		return (0);
	if (ptr[0] == NULL)
	{
		free(ptr);
		data->inputs[i].cmds = NULL;
	}
	else
		data->inputs[i].cmds = ptr;
	return (0);
}

int	ft_fulling_inputs_cmds(t_data *data)
{
	int		i;
	char	**cmd;
	char	**ptr;
	int		error;

	error = 0;
	i = 0;
	ptr = NULL;
	cmd = ft_split_and_omit(data->temp, '|', 1);
	if (cmd == NULL)
		return (ERROR_MEMORY);
	i = 0;
	while (i <= data->nb_pipe)
	{
		error = ft_fulling_input_cmds(cmd, ptr, i, data);
		if (error != 0)
			return (error);
		i++;
	}
	return (0);
}

int	ft_if_not_cmd_after_last_pipe(t_data *data)
{
	char	*ptr;
	char	**cmd;
	int		old_error;

	ptr = NULL;
	old_error = g_error_code;
	g_error_code = -2;
	if (data->inputs->cmds != NULL && data->inputs[data->nb_pipe].cmds == NULL )
	{
		ptr = readline(">");
		if (ptr == NULL)
			return (ft_sub_if_not_cmd_after_last_pipe(ptr, old_error));
		g_error_code = old_error;
		if (ptr != NULL)
			ft_which_redirection_take_on_board(ptr);
		cmd = ft_split_and_omit(ptr, ' ', 0);
		free(ptr);
		if (cmd == NULL)
			return (1);
		data->inputs[data->nb_pipe].cmds = cmd;
	}
	g_error_code = old_error;
	return (0);
}

int	ft_yparsing(t_data *data)
{
	int		error;

	data->nb_pipe = ft_ycheck_pipe(data->temp);
	if (data->nb_pipe == -1)
		return (ft_yerror(ERROR_PIPE, data));
	error = ft_if_quotes_not_closes(data);
	if (error != 0)
		return (ft_yerror(error, data));
	if (ft_check_and_replace_var(&data->temp, data->env) == 1)
		return (ft_yerror(ERROR_MEMORY, data));
	ft_create_inputs(data);
	error = ft_fulling_inputs_cmds(data);
	if (error != 0)
		return (ft_yerror(error, data));
	error = ft_if_not_cmd_after_last_pipe(data);
	if (error != 0)
		return (ft_yerror(error, data));
	error = ft_parse_redirection(data);
	if (error != 0)
		return (ft_yerror(error, data));
	if (data->inputs == NULL)
		return (ft_yerror(5, data));
	ft_convert_redi(data);
	return (0);
}
