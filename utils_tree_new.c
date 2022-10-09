/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:53:26 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 17:13:46 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parserda çift tırnak içinde boşluk varsa tırnak kaldırma
int	is_redir(char *str)
{
	int			i;
	static char	*redir_types[5] = {">>", "<<", ">", "<", 0};

	i = -1;
	while (redir_types[++i])
	{
		if (ft_strncmp(str, redir_types[i], ft_strlen(redir_types[i])) == 0)
			return (ft_strlen(redir_types[i]));
	}
	return (0);
}

char	*ft_str_clearspace2(const char *str)
{
	int		i;
	char	*ret;
	char	*tmp;

	ret = ft_calloc(1, sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			tmp = ft_substr(str, i, parser_quote_endidx(&str[i + 1], '"') + 2);
			i += ft_strlen(tmp);
			ret = ft_free_strjoin(ret, tmp);
		}
		else
		{
			tmp = ft_substr(str, i, 1);
			ret = ft_free_strjoin(ret, tmp);
			i += (str[i] != ' ') + ft_str_clearspace_end(&str[i]);
		}
		free(tmp);
	}
	return (ret);
}

int	use_is_redir(char **cmd, int *idx, char **type, int *check_redir)
{
	if (*check_redir == 1)
		return (-1);
	*type = ft_substr(cmd[0], *idx, is_redir(&(cmd[0][*idx])));
	ft_memset(&cmd[0][*idx], ' ', ft_strlen(*type));
	*idx += ft_strlen(*type);
	*check_redir = 1;
	return (0);
}

void	use_is_arg(char **cmd, int *idx, char **arg, int *check_redir)
{
	if (cmd[0][*idx] == '"' || cmd[0][*idx] == '\'')
	{
		*arg = ft_substr(cmd[0], *idx, \
						ft_get_chrindex(&cmd[0][*idx + 1], cmd[0][*idx]) + 1);
	}
	else
	{
		*arg = ft_substr(cmd[0], *idx, \
						ft_get_chrindex(&cmd[0][*idx + 1], ' ') + 1);
	}
	ft_memset(&cmd[0][*idx], ' ', ft_strlen(*arg));
	*idx += ft_strlen(*arg);
	*check_redir = 2;
}

void	build_tree_w_pipe(t_syntax_tree *tree, char **arg_commands, int pipe)
{
	int	i;

	i = 0;
	while (pipe)
	{
		tree->left = build_exec(arg_commands[i]);
		tree->left->prev = tree;
		i++;
		pipe--;
		if (pipe)
		{
			tree->right = new_s_syntax_tree(PIPE);
			tree->right->prev = tree;
		}
		else
		{
			tree->right = build_exec(arg_commands[i]);
			tree->right->prev = tree;
		}
		tree = tree->right;
	}
}

t_syntax_tree	*new_tree(t_arg *args)
{
	t_syntax_tree	*tree;
	int				pipe_count;

	pipe_count = args->cmd_count -1;
	printf("pipe_count = %d\n", pipe_count);
	if (!pipe_count)
		tree = build_exec(args->arg_commands[0]);
	else
	{
		tree = new_s_syntax_tree(PIPE);
		build_tree_w_pipe(tree, args->arg_commands, pipe_count);
	}
	return (tree);
}
