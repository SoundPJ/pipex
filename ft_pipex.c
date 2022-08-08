/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:43:37 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/09 00:44:36 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
char	**ft_findpath(char *env[]);
int		ft_runcmd(char *cmd, char *env[]);

int	main(int argc, char *argv[], char *env[])
{
	char	buf;
	int		fd[2];
	int		pid;

	if(argc < 5)
		perror("The program should be used like this \"./pipex infile cmd1 cmd2 ... outfile\"");
	else
	{
	}
		if (pipe(fd) == -1)
		{
			perror("Error at pipe");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Error at fork");
			exit(1);
		}
		else
		{
			if (pid == 0)// child process
			{
				dup2(fd[1], 1);
				ft_runcmd(argv[2], env);
			}
			else // parent process
			{
				wait(NULL);
				// read(fd[0], &buf, 1);
				ft_runcmd(ft_strjoin(argv[3], argv[1]), env);
				// write(1, &buf , 1);
				// write(1, "b", 1);
			}
		}
	return (0);
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
	return (NULL);
}

int	ft_runcmd(char *cmd, char *env[])
{
	char	**paths;
	char	*bin_path;
	char	**cd;
	int		i;

	paths = ft_findpath(env);
	if (paths == NULL)
		exit(1);
	cd = ft_split(cmd, ' ');
	i = 0;
	while (paths[i] != NULL)
	{
		bin_path = ft_strjoin(paths[i], ft_strjoin("/", cd[0]));
		if (access(bin_path, X_OK) == 0)
		{
			if (execve(bin_path, cd, env) == -1)
				exit(1);
		}
		else
			i++;
	}
	return (0);
}
