/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:59:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/16 14:54:34 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

static char	**check_quotes(char *cmd)
{
	char	*s;

	s = ft_strchr(cmd, 'c');
	if (s != 0)
	{
		
	}
}
static char	**free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
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
	i = -1;
	while (arr[++i])
	{
		path = ft_strjoin(arr[i], cmd);
		if (access(path, F_OK) == -1)
			free(path);
		else
			break ;
	}
	if (arr[i] == 0)
		path = 0;
	free(cmd);
	free_memory(arr);
	return (path);
}

void	execute(char *str, char **environ)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(str, ' ');
	path = get_path(environ, cmd[0]);
	if (path == 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		free_memory(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, environ) == -1)
		error_exit(cmd[0]);
}
