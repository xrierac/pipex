/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:22:27 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/20 14:35:51 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

void	left_cmd(char **argv, char **environ, int pipefd[]);
void	right_cmd(char **argv, char **environ, int pipefd[]);
char	*get_path(char **environ, char *cmd);
void	execute(char *str, char **environ);
void	error_exit(char *str, int status);
#endif
