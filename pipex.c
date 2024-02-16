/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:50:40 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/16 16:46:07 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

extern char	**environ;

void	error_exit(char *str)
{
	ft_putstr_fd("pipex: ", 2);
	perror(str);
	exit(EXIT_FAILURE);
}

void	left_cmd(char **argv, char **environ, int pipefd[])
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0444);
	if (infile == -1)
		error_exit(argv[1]);
	dup2(infile, STDIN_FILENO);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	execute(argv[2], environ);
}

void	right_cmd(char **argv, char **environ, int pipefd[])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		error_exit(argv[4]);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	execute(argv[3], environ);
}

int	main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	cpid;

	if (!environ[0])
		return (write(2, "Empty environment variable\n", 27));
	if (argc == 5)
	{
		if (pipe(pipefd) == -1)
			error_exit("pipe()");
		cpid = fork();
		if (cpid == 0)
			left_cmd(argv, environ, pipefd);
		if (cpid == -1)
			error_exit("fork()");
		if (cpid > 0)
		{
			cpid = fork();
			if (cpid == 0)
				right_cmd(argv, environ, pipefd);
		}
	}
	else
		return (write(2, "Wrong number of arguments\n", 27));
	return (0);
}
