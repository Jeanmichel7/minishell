/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:01:24 by jrasser           #+#    #+#             */
/*   Updated: 2022/06/21 02:28:53 by jrasser          ###   ########.fr       */
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
