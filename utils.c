/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:59:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/19 16:37:44 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

static char	**split_quotes(char **cmd)
{
	char	**arr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	arr = malloc(sizeof(char *) * (get_number_words(s, c, d) + 1));
	if (!arr)
		return (0);
	while (cmd[++i])
	{
		if (ft_strchr(cmd[i], 39) != 0)


		else
			arr[++j] == ft_strdup(cmd[i]);
	}
	ft_free_array(cmd);
	return (arr);
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
	if (arr == 0)
		error_exit("");
	cmd = ft_strjoin("/", cmd);
	if (cmd == 0)
		error_exit("");
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
	ft_free_array(arr);
	return (path);
}

void	execute(char *str, char **environ)
{
	char	**cmd;
	char	*path;
	
	cmd = ft_split(str, ' ');
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
