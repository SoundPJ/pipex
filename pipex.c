/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/14 23:23:35 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_findpath(char **env);
void	ft_runcmd(char *cmd, char **env, int infd, int outfd);
int		ft_open_infile(char *infile);

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		pid;

	if (argc < 5)
	{
		write(2, "Wrong Usage: ./pipex <infile> <cmd1> <cmd2> ... <outfile>\n", 58);
		exit(EXIT_FAILURE);
	}
	else
	{
		infile_fd = ft_open_infile(argv[1]);
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0775);
		if (pipe(fd) < 0)
		{
			perror("Error at pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Error at fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			close(fd[0]);
			ft_runcmd(argv[2], env, infile_fd, fd[1]);
		}
		else
		{
			close(fd[1]);
			close(infile_fd);
			wait(NULL);
			ft_runcmd(argv[3], env, fd[0], 1);
		}
		return (0);
	}
}

int	ft_open_infile(char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
	{
		perror("Input file does not exist");
		exit(EXIT_FAILURE);
	}
	return (infile_fd);
}

char	**ft_findpath(char *env[])
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

void	ft_runcmd(char *cmd, char *env[], int infd, int outfd)
{
	char	**paths;
	char	*bin_path;
	char	**cd;
	int		i;

	paths = ft_findpath(env);
	cd = ft_split(cmd, ' ');
	i = 0;
	while (paths[i] != NULL)
	{
		bin_path = ft_strjoin(paths[i], ft_strjoin("/", cd[0]));
		if (access(bin_path, X_OK) == 0)
		{
			dup2(infd, 0);
			dup2(outfd, 1);
			if (execve(bin_path, cd, env) == -1)
				exit(1);
		}
		else
			i++;
	}
	perror("Command not found");
	exit (EXIT_FAILURE);
}
