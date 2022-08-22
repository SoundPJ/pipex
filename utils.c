/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 04:07:40 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/18 04:28:06 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(int argc, char **argv, char **env, int i)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) != 0)
		ft_err("Error at pipe");
	pid = fork();
	if (pid < 0)
		ft_err("Error at fork");
	else if (pid == 0)
		ft_runcmd(argv[i], env, fd[1], 1);
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		if (++i < argc - 2)
			ft_pipex(argc, argv, env, i);
		else
			ft_runcmd(argv[i], env, ft_open_file(argv[argc - 1], OUTFILE), 1);
	}
}

int	ft_open_file(char *filename, int mode)
{
	int	file_fd;

	if (mode == INFILE)
	{
		file_fd = open(filename, O_RDONLY);
		if (file_fd < 0)
			ft_err("Input file does not exist");
		return (file_fd);
	}
	else
		return (open(filename, O_WRONLY | O_CREAT, 0775));
}

char	**ft_findpath(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			env[i] = env[i] + 5;
			return (ft_split(env[i], ':'));
		}
		else
			i++;
	}
	ft_err("Environment path not found");
}

void	ft_runcmd(char *cmd, char **env, int dupped_fd, int infd)
{
	char	**paths;
	char	**cd;
	char	*bin_path;
	int		i;

	paths = ft_findpath(env);
	cd = ft_split(cmd, ' ');
	i = 0;
	while (paths[i] != NULL)
	{
		bin_path = ft_strjoin(paths[i], ft_strjoin("/", cd[0]));
		if (access(bin_path, X_OK | R_OK | F_OK) == 0)
		{
			dup2(dupped_fd, infd);
			if (execve(bin_path, cd, env) == -1)
				exit(1);
		}
		else
			i++;
	}
	ft_err("Command not found");
}

void	ft_err(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
