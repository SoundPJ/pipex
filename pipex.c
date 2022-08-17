/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/18 03:03:53 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_findpath(char **env);
void	ft_runcmd(char *cmd, char **env);
int		ft_open_infile(char *infile);
void		first_cmd(int argc, char **argv, char **env, int i);

int	main(int argc, char **argv, char **env)
{
	// int	ncmd = 1;
	// int	tmp_fd;
	// char	buf;
	// int	piped_fd[2];
	// pipe(piped_fd);
	// int	pid = fork();
	// if (pid == 0)
	// {
	// 	write(piped_fd[1], 'a', 1);
	// 	close(piped_fd[0]);
	// 	close(piped_fd[1]);
	// }
	// else
	// {
	// 	wait(NULL);
	// 	close(piped_fd[1]);
	// 	read(piped_fd[0], &buf, 1);
	// 	printf("%c\n", buf);
	// }
	// (void)argc;

	first_cmd(argc, argv, env, 2);

	return (0);
}

void	first_cmd(int argc, char **argv, char **env, int i)
{
	int	fd[2];
	pipe(fd);
	int	pid = fork();

	if (pid == 0)
	{
		if (i == 2)
			dup2(open(argv[1], O_RDONLY), 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		ft_runcmd(argv[i], env);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		i++;
		dup2(fd[0], 0);
		close(fd[0]);
		if (i < argc - 2)
			first_cmd(argc, argv, env, i);
		else
		{
			dup2(open(argv[argc - 1], O_WRONLY | O_CREAT, 0775), 1);
			ft_runcmd(argv[i], env);
		}
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
