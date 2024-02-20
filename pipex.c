/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:50:40 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/20 15:23:21 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

extern char	**environ;

void	error_exit(char *str, int status)
{
	ft_putstr_fd("pipex: ", 2);
	perror(str);
	exit(status);
}

void	left_cmd(char **argv, char **environ, int fd[])
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0444);
	if (infile == -1)
		error_exit(argv[1], 127);
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("", 127);
	close(fd[0]);
	close(fd[1]);
	execute(argv[2], environ);
}

void	right_cmd(char **argv, char **environ, int fd[])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		error_exit(argv[4], 127);
	if (dup2(outfile, STDOUT_FILENO) == -1 || dup2(fd[0], STDIN_FILENO) == -1)
		error_exit("", 127);
	close(fd[1]);
	close(fd[0]);
	execute(argv[3], environ);
}

int	parent_process(char **environ, char **argv)
{
	int		pipefd[2];
	pid_t	cpid1;
	pid_t	cpid2;
	int		status;

	if (pipe(pipefd) < 0)
		error_exit("", 127);
	cpid1 = fork();
	if (cpid1 < 0)
		error_exit("", 127);
	if (cpid1 == 0)
		left_cmd(argv, environ, pipefd);
	cpid2 = fork();
	if (cpid2 < 0)
		error_exit("", 127);
	if (cpid2 == 0)
		right_cmd(argv, environ, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	if (waitpid(cpid1, NULL, 0) == -1 || waitpid(cpid2, &status, 0) == -1)
		error_exit("", 127);
	return (WEXITSTATUS(status));
}

int	main(int argc, char *argv[])
{
	if (!environ[0])
	{
		ft_putstr_fd("Environment variable is empty", 2);
		return (1);
	}
	if (argc == 5)
		return (parent_process(environ, argv));
	else
	{
		ft_putstr_fd("Wrong number of arguments", 2);
		return (2);
	}
	return (0);
}
