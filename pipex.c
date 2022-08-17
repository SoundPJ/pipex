/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/18 03:31:42 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_findpath(char **env);
void	ft_runcmd(char *cmd, char **env);
void	first_cmd(int argc, char **argv, char **env, int i);
int		ft_open_file(char *filename, int mode);

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		write(1, "Not enough arguments\n", 22);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(ft_open_file(argv[1], INFILE), 0);
		first_cmd(argc, argv, env, 2);
	}
	return (0);
}

void	first_cmd(int argc, char **argv, char **env, int i)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		ft_runcmd(argv[i], env);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		if (++i < argc - 2)
			first_cmd(argc, argv, env, i);
		else
		{
			dup2(ft_open_file(argv[argc - 1], OUTFILE), 1);
			ft_runcmd(argv[i], env);
		}
	}
}

int	ft_open_file(char *filename, int mode)
{
	int	file_fd;

	if (mode == INFILE)
	{
		file_fd = open(filename, O_RDONLY);
		if (file_fd < 0)
		{
			perror("Input file does not exist");
			exit(EXIT_FAILURE);
		}
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
	perror ("Environment path not found");
	exit (EXIT_FAILURE);
}

void	ft_runcmd(char *cmd, char **env)
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
			if (execve(bin_path, cd, env) == -1)
				exit(1);
		}
		else
			i++;
	}
	perror("Command not found");
	exit (EXIT_FAILURE);
}
