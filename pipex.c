/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:50:40 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/10 13:42:21 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

extern char **environ;
int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	cpid;

	cpid = fork();
	if (cpid == 0)

	else if (cpid == -1)

	else

//	if (argc != 5)
//		perror("Wrong number of arguments");
	if (argc == 5)
	{
		if (access(argv[1], F_OK) == -1)
			perror("Error");
		execve(

	}
//	cpid = fork();
	return (0);
}
