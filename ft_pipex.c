/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:43:37 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/11 05:09:36 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
char	**ft_findpath(char **env);
int		ft_runcmd(char *cmd, char **env, int infd, int outfd);

int	main(int argc, char **argv, char **env)
{
	char	buf;
	int		fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		pid;

	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0775);
	pipe(fd);
	pid = fork();
	if (pid == 0) //child process
	{
		close(fd[0]);
		ft_runcmd(argv[2], env, infile_fd, fd[1]);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		ft_runcmd(argv[3], env, fd[0], outfile_fd);
	}
	close(outfile_fd);
	//////////////////////
	// if(argc < 5)
	// 	perror("The program should be used like this \"./pipex infile cmd1 cmd2 ... outfile\"");
	// else
	// {
	// 	if (pipe(fd) == -1)
	// 	{
	// 		perror("Error at pipe");
	// 		exit(1);
	// 	}
	// 	pid = fork();
	// 	if (pid == -1)
	// 	{
	// 		perror("Error at fork");
	// 		exit(1);
	// 	}
	// 	else
	// 	{
	// 		if (pid == 0)// child process
	// 		{
	// 			close(fd[0]);
	// 			dup2(fd[1], 1);
	// 			ft_runcmd(argv[2], env);
	// 			// ft_runcmd("echo hey", env);
	// 			close(fd[1]);
	// 		}
	// 		else // parent process
	// 		{
	// 			wait(NULL);
	// 			close(fd[1]);
	// 			read(fd[0], &buf, 100);
	// 			write(1, &buf, 100);
	// 			close(fd[0]);
	// 			// ft_runcmd(ft_strjoin(argv[3], argv[1]), env);
	// 		}
	// 	}
	// }
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

int	ft_runcmd(char *cmd, char *env[], int infd, int outfd)
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
			dup2(infd, 0);
			dup2(outfd, 1);
			if (execve(bin_path, cd, env) == -1)
				exit(1);
		}
		else
			i++;
	}
	return (0);
}
