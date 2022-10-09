/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:55:09 by saksoy            #+#    #+#             */
/*   Updated: 2022/10/09 03:55:10 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_filesize(t_redirection *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (!ft_strcmp(lst->redir, "<") || !ft_strcmp(lst->redir, ">")
			|| !ft_strcmp(lst->redir, ">>"))
			i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

/*char	**ft_strdup_multi(char **s1)
{
	char	**dest;
	int		lines;
	int		i;

	i = -1;
	lines = ft_matrix_size(s1);
	dest = malloc(lines * (sizeof(char *) + 1));
	while (++i < lines)
		dest[i] = ft_strdup(s1[i]);
	dest[i] = 0;
	return (dest);
}
*/
int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
		{
			if (str1[i] < str2[i])
				return (-1);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_space_cntrl(const char *str)
{
	int	i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
