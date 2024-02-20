/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:59:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/20 12:31:33 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

static int	check_quotes(char *str, int c)
{
	int	i;
	int	p;

	i = -1;
	p = 0;
	while (str[++i])
	{
		if (str[i] == c && ft_strchr(str + i + 1, c) != 0)
		{
			str[i] = ' ';
			p = c;
			while (str[++i] != c)
			{
				if (str[i] == ' ')
					str[i] = c;
			}
			str[i] = ' ';
		}
	}
	return (p);
}

static char	**get_cmd(char *str)
{
	char	**cmd;
	int		i;
	int		j;

	check_quotes(str, 39);
	check_quotes(str, 34);
	cmd = ft_split(str, ' ');
	if (cmd == 0)
		return (0);
	if (ft_strchr(str, 39) != 0 || ft_strchr(str, 34) != 0)
	{
		i = -1;
		while (cmd[++i])
		{
			j = -1;
			while (cmd[i][++j])
				if (cmd[i][j] == 39 || cmd[i][j] == 34)
					cmd[i][j] = ' ';
		}
	}
	return (cmd);
}

char	*get_path(char **environ, char *cmd)
{
	int		i;
	char	**arr;
	char	*path;

	i = 0;
	while (ft_strnstr(environ[i], "PATH", 4) == 0 && environ[i] != '\0')
		i++;
	if (environ[i] == '\0')
		return (0);
	arr = ft_split(environ[i] + 5, ':');
	cmd = ft_strjoin("/", cmd);
	if (arr == 0 || cmd == 0)
		error_exit("");
	i = -1;
	while (arr[++i])
	{
		path = ft_strjoin(arr[i], cmd);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
	}
	if (arr[i] == 0)
		path = 0;
	free(cmd);
	ft_free_array(arr);
	return (path);
}

void	execute(char *str, char **environ)
{
	char	**cmd;
	char	*path;

	cmd = get_cmd(str);
	if (cmd == 0)
		error_exit("");
	path = get_path(environ, cmd[0]);
	if (path == 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		ft_free_array(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, environ) == -1)
		error_exit(cmd[0]);
}
