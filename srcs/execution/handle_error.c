/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:01:24 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/24 20:01:39 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_errputstr(char *str, int stop, int code, t_data *data)
{
	(void)data;
	if (str)
	{
		write(2, str, ft_strlen(str));
		if (stop)
			exit(code);
	}
}

int	ft_check_cmd_waiting(t_data *data, int i)
{
	if (i == data->nb_pipe)
	{
		if (ft_strncmp(data->inputs[i].cmds[0], "cat", 3) == 0
			&& data->inputs[i].cmds[1] == NULL)
		{
			g_error_code = -1;
			return (1);
		}
		if (ft_strncmp(data->inputs[i].cmds[0], "grep", 4) == 0
			&& data->inputs[i].cmds[2] == NULL)
		{
			g_error_code = -1;
			return (1);
		}
	}
	return (0);
}
