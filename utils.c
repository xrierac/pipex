/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:59:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/20 15:07:00 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

//This functions checks for a quoted string and if it exists it replaces empty 
//spaces with quotes so ft_split can operate normally 
static char	check_quotes(char *str)
{
	int		i;
	char	c;

	i = -1;
	c = ' ';
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			c = str[i];
			if (ft_strchr(str + i + 1, c))
			{
				str[i] = ' ';
				while (str[++i] != c)
					if (str[i] == ' ')
						str[i] = c;
				str[i] = ' ';
			}
		}
	}
	return (c);
}

static char	**get_cmd(char *str)
{
	char	**cmd;
	int		i;
	int		j;
	char	c;

	c = check_quotes(str);
	cmd = ft_split(str, ' ');
	if (cmd == 0)
		return (0);
	if (c != ' ')
	{
		i = -1;
		while (cmd[++i])
		{
			j = -1;
			while (cmd[i][++j])
				if (cmd[i][j] == c)
					cmd[i][j] = ' ';
		}
	}
	return (cmd);
}

static char	*check_environ(char **environ)
{
	int	i;

	i = 0;
	while (ft_strnstr(environ[i], "PATH", 4) == 0 && environ[i] != '\0')
		i++;
	if (environ[i] == '\0')
		return (0);
	return (environ[i]);
}

char	*get_path(char **environ, char *cmd)
{
	int		i;
	char	**arr;
	char	*path;

	arr = ft_split(check_environ(environ) + 5, ':');
	cmd = ft_strjoin("/", cmd);
	if (arr == 0 || cmd == 0)
		error_exit("", 127);
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
		error_exit("", 127);
	if (access(cmd[0], F_OK) != 0)
		path = get_path(environ, cmd[0]);
	else
		path = cmd[0];
	if (path == 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		ft_free_array(cmd);
		exit(127);
	}
	if (execve(path, cmd, environ) == -1)
		error_exit(cmd[0], 127);
}
