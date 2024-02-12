/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:50:40 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/12 14:48:10 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

extern char	**environ;

void	left_cmd(char **argv, char **environ, int pipefd[])
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0444);
	if (infile == -1)
		exit(EXIT_FAILURE);
	dup2(infile, STDIN_FILENO);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	execute(argv[2], environ);
}

void	right_cmd(char **argv, char **environ, int pipefd[])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	execute(argv[3], environ);
}

int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	cpid;

	if (argc == 5)
	{
		pipe(pipefd);
		cpid = fork();
		if (cpid == 0)
			left_cmd(argv, environ, pipefd);
		if (cpid == -1)
			perror("\033[31mError");
		if (wait(&cpid) == -1)
		{
			perror("\033[31mError\033[m.");
			return (-1);
		}
		right_cmd(argv, environ, pipefd)
	};
	return (0);
}
