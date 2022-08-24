/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:20 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/18 20:11:30 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define INFILE		0
# define OUTFILE	1

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

char	**ft_findpath(char **env);
void	ft_runcmd(char *cmd, char **env, int dupped_fd, int infd);
void	ft_pipex(int argc, char **argv, char **env, int i);
void	ft_err(char *err_msg);
int		ft_open_file(char *filename, int mode);

#endif
