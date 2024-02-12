/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:50:40 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/12 12:12:17 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

extern char	**environ;

void	left_cmd(char **argv, char **environ, int pipefd[])
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 00444);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipefd[1], STDOUT_FILENO);
	execute(argv[2], environ);
}

void	right_cmd(char **argv, char **environ, int pipefd[])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00222);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipefd[0], STDIN_FILENO);
	execute(argv[3], environ);
}

int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	cpid;

	if (argc != 5)
		return (0);
	pipe(pipefd);
	cpid = fork();
	if (cpid == 0)
		left_cmd(argv, environ, pipefd);
	else if (cpid == -1)
		perror("Error");
	else
	{
		wait(&cpid);
		right_cmd(argv, environ, pipefd);
	}	
	return (0);
}
