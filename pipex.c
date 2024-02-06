/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:50:40 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/06 16:08:28 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	cpid;


	if (access(argv[1], F_OK) == -1)
		ft_printf("File %s not found", argv[1]);
	cpid = fork();
	return (0);
}
