/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:43:37 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/06 23:21:05 by pjerddee         ###   ########.fr       */
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
	char	**path = ft_findpath(env);
	int	i = 0;
	while(path[i] != NULL)
		ft_putendl_fd(path[i++], 1);
	return (0);
}

char	**ft_findpath(char *env[])
{
	int 	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_split(env[i], ':'));
		else
			i++;
	}
	return (NULL);
}
