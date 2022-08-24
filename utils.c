/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 04:07:40 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/25 04:58:13 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_bin_path(char *cmd, char **paths);
void	runcmd(char *bin_path, char **cd, int dupped_fd, int infd);

void	ft_pipex(int argc, char **argv, char **paths, int i)
{
	int	fd[2];
	int	pid;
	char	*bin_path;
	char	**args;

	if (pipe(fd) != 0)
		ft_err("Error at pipe\n");
	pid = fork();
	if (pid < 0)
		ft_err("Error at fork\n");
	else if (pid == 0)
	{
		args = ft_split(argv[i], ' ');
		bin_path = find_bin_path(args[0], paths);
		runcmd(bin_path, args, fd[1], 1);
	}
		// ft_runcmd(argv[i], paths, fd[1], 1);
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		if (++i < argc - 2)
			ft_pipex(argc, argv, paths, i);
		else
		{
			args = ft_split(argv[i], ' ');
			bin_path = find_bin_path(args[0], paths);
			runcmd(bin_path, args, ft_open_file(argv[argc - 1], OUTFILE), 1);
		}
			// ft_runcmd(argv[i], paths, ft_open_file(argv[argc - 1], OUTFILE), 1);
	}
}

int	ft_open_file(char *filename, int mode)
{
	int	file_fd;

	if (mode == INFILE)
	{
		file_fd = open(filename, O_RDONLY);
		if (file_fd < 0)
			ft_err("Input file does not exist\n");
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
			return(ft_split(env[i], ':'));

		}
		else
			i++;
	}
	ft_err("Environment path not found\n");
	return (NULL);
}

// void	ft_runcmd(char *cmd, char **paths, int dupped_fd, int infd)
// {
// 	char	**cd;
// 	char	*bin_path;
// 	int		i;

// 	cd = ft_split(cmd, ' ');
// 	i = 0;
// 	while (paths[i] != NULL)
// 	{
// 		bin_path = ft_strjoin(paths[i], ft_strjoin("/", cd[0]));
// 		if (access(bin_path, X_OK | R_OK | F_OK) == 0)
// 			runcmd(bin_path, cd, dupped_fd, infd);
// 		else
// 			i++;
// 	}
// 	ft_err("Command not found\n");
// }

char	*find_bin_path(char *cmd, char **paths)
{
	// char	**cd;
	char	*bin_path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		bin_path = ft_strjoin(paths[i], ft_strjoin("/", cmd));
		if (access(bin_path, X_OK | R_OK | F_OK) == 0)
			return (bin_path);
		else
			i++;
	}
	ft_err("Command not found\n");
	return (NULL);
}

void	ft_err(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

void	runcmd(char *bin_path, char **cd, int dupped_fd, int infd)
{
	dup2(dupped_fd, infd);
	if (execve(bin_path, cd, NULL) == -1)
		exit(1);
}