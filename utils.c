/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:59:33 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/10 14:24:13 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path(char **environ)
{
	int		i;
	char 	*arr;

	i = 0;
	while (ft_strnstr(environ[i], "PATH", 4) == NULL && environ[i] != '\0')
		i++;
	if (environ[i] == '\0')
		exit(WRONG_PATH);
	arr = ft_split(environ[i], ':');
	i = 0;
	while (arr[i] != '\0')


}	
