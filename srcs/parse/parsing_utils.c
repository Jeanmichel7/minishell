/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:58:50 by ydumaine          #+#    #+#             */
/*   Updated: 2023/09/01 23:27:35 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_omit_part2(char c, unsigned int omit)
{
	if (c == 39 && omit == 1)
		return (1);
	if (c == 34 && omit == 2)
		return (2);
	return (omit);
}

int	ft_omit_quote_apostrophe(char c, unsigned int omit,
unsigned int *i, int keep_quotes)
{
	if (c == 34 && omit == 1)
	{
		if (keep_quotes == 0 && i != NULL)
			(*i)++;
		return (0);
	}
	if (c == 39 && omit == 2)
	{
		if (keep_quotes == 0 && i != NULL)
			(*i)++;
		return (0);
	}
	if (c == 34 && omit == 0)
	{
		if (keep_quotes == 0 && i != NULL)
			(*i)++;
		return (1);
	}
	if (c == 39 && omit == 0)
	{
		if (keep_quotes == 0 && i != NULL)
			(*i)++;
		return (2);
	}
	return (ft_omit_part2(c, omit));
}

int	ft_check_scope(char *temp, unsigned int *i, unsigned int *u)
{
	(*u)++;
	if (temp[++(*i)] == '|')
		return (-1);
	while (temp[(*i)] == ' ')
		(*i)++;
	if (temp[(*i)] == '|')
		return (-1);
	return (0);
}

int	ft_ycheck_pipe(char *temp)
{
	unsigned int	i;
	unsigned int	u;
	unsigned int	omit;

	i = 0;
	u = 0;
	omit = 0;
	if (temp[0] == '|')
		return (-1);
	while (temp[i])
	{
		omit = ft_omit_quote_apostrophe(temp[i], omit, &i, 1);
		if (temp[i] == '|' && omit == 0)
		{
			if (ft_check_scope(temp, &i, &u) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (u);
}

int	ft_retrieve_string(int omit, t_data *data, char *ptr)
{
	int	i;

	i = -1;
	ptr = readline(">");
	if (ptr == NULL)
		return (ft_sub_retrieve_string(omit, ptr));
	while (ptr[++i])
		omit = ft_omit_quote_apostrophe(ptr[i], omit, NULL, 1);
	if (omit != 0)
		data->temp = ft_strjoin_andadd_rt(data->temp, ptr);
	else
		data->temp = ft_strjoin(data->temp, ptr);
	free(ptr);
	if (data->temp == NULL)
		return (ERROR_MEMORY);
	return (omit);
}
