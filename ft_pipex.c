/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:43:37 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/07 18:44:09 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
char	**ft_findpath(char *env[]);
int	ft_runcmd(char *cmd, char *env[]);

int	main(int argc, char *argv[], char *env[])
{
	// int fd[2];
	// int	pid;

	// pipe(fd);
	// pid = fork();
	// if (pid == -1)
	// {
	// 	return 1;
	// }
	// else
	// {
	// 	if (pid != 0)// parent process
	// 	{
	// 		wait(NULL);
	// 		char buf;
			
	// 		read(fd[0], &buf, 1); 
	// 		write(1, &buf , 1);
	// 		write(1, "b", 1);
	// 	}
	// 	else // child process
	// 	{
	// 		dup2(fd[1], 1);
	// 		write(1, "a", 1);
	// 		exit(0);
	// 	}
	// }
	if(argc < 2)
		printf("Input needed!!\n");
	else
		ft_runcmd(argv[1], env);
	return (0);
}

char	**ft_findpath(char *env[])
{
	int 	i = 0;
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
	char	*binPath;
	char	**cd;
	int		i;

	paths = ft_findpath(env);
	cd = ft_split(cmd, ' ');
	i = 0;
	while(paths[i] != NULL)
	{
		binPath = ft_strjoin(paths[i],ft_strjoin("/", cd[0]));
		if (access(binPath, X_OK) == 0)
		{
			if (execve(binPath, cd, env) == -1)
				printf("error");
		}
		else
			i++;
	}
	return (0);
}
