/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:59:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/12 12:12:23 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

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
		free_memory(cmd);
		perror("Error");
	}
	execve(path, cmd, environ);
}
