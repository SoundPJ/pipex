/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:43:37 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/07 08:10:39 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
char	**ft_findpath(char *env[]);

int	main(int argv, char *argc[], char *env[])
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
	
	char	**paths = ft_findpath(env);
	int	i = 0;

	// char *cmd = "/bin/cat";
	char *cmd = "cat";
	char *binPath;
	char *arg[] = {cmd, "test", NULL};
	char envp[] = {0};
	// while(paths[i] != NULL)
	// {
	// 	binPath = ft_strjoin(paths[i],cmd);
	// 	if (access(binPath, W_OK))
	// 		if (execve(binPath, arg, env) == -1)
	// 			printf("error");
	// 	else
	// 		i++;
	// }

	if (access("/trash/cat", X_OK) == 0)
		printf("OK\n");
	else
		printf("NOOO\n");
	// 	ft_putendl_fd(path[i++], 1);
			
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
