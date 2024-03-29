/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:50:06 by ydumaine          #+#    #+#             */
/*   Updated: 2023/09/01 23:24:49 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_extract_line(char *ptr, char **str, char *pattern)
{
	int	pattern_found;

	pattern_found = 0;
	ptr = readline(">");
	if (ptr == NULL)
		return (2);
	pattern_found = ft_search_pattern(ptr, pattern);
	if (pattern_found != 0)
	{
		free (ptr);
		return (pattern_found);
	}
	if (pattern_found == 0)
		*str = ft_strjoin_andadd_rt(*str, ptr);
	else
		*str = ft_strjoin(*str, ptr);
	free(ptr);
	if (*str == 0)
		return (0);
	return (pattern_found);
}

/*
int	ft_update_file(char *str, t_file **files, int total, int rd)
{
	t_file	*new_file;

	new_file = ft_calloc(total + 1, sizeof(t_file));
	if (new_file == NULL)
		return (ERROR_MEMORY);
	if (*files != NULL)
		ft_memcpy(new_file, *files, (sizeof(t_file) * (total)));
	if (total != 0)
	{
		new_file[total - 1].fd = -1;
		new_file[total - 1].type = rd;
		new_file[total - 1].name = str;
	}
	new_file[total].fd = -1;
	*files = new_file;
	return (0);
}
*/

int	ft_update_file(char *str, t_file **files, int total, int rd)
{
	t_file	*new_file;

	new_file = ft_calloc(total + 1, sizeof(t_file));
	if (new_file == NULL)
		return (ERROR_MEMORY);
	if (*files != NULL)
		ft_memcpy(new_file, *files, (sizeof(t_file) * (total)));
	free(*files);
	if (total != 0)
	{
		new_file[total - 1].fd = -1;
		new_file[total - 1].type = rd;
		new_file[total - 1].name = str;
	}
	new_file[total].fd = -1;
	*files = new_file;
	return (0);
}

int	ft_search_pattern(char *str, char *pattern)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	if (str[i] == pattern[i])
	{
		while (str[i] == pattern[i])
		{
			if (pattern[i] == '\0')
				return (1);
			i++;
		}
	}
	return (0);
}

int	print_and_rv(char *str)
{
	write (2, "minishell: syntax error near unexpected token `", 47);
	write (2, str, ft_strlen(str));
	write (2, "'\n", 2);
	return (258);
}

int	ft_print_error(int rd)
{
	if (rd == -2)
		return (print_and_rv(">"));
	if (rd == -1)
		return (print_and_rv("<"));
	if (rd == -3)
		return (print_and_rv(">>"));
	if (rd == -4)
		return (print_and_rv("<<"));
	if (rd == -5)
		return (print_and_rv("new_line"));
	return (1);
}
