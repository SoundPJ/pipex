/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/23 23:09:18 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char **av, int *hd_fd);

int	main(int argc, char **argv, char **env)
{
	int	hd_fd[2];

	if (argc < 5)
	{
		write(1, "Not enough arguments\n", 22);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			pipe(hd_fd);
			here_doc(argv, hd_fd);
			printf("DONE HD\n");
			dup2(hd_fd[0], 0);
			ft_pipex(argc, argv, env, 3);
			close(hd_fd[0]);
			close(hd_fd[1]);
		}
		else
		{
			dup2(ft_open_file(argv[1], INFILE), 0);
			ft_pipex(argc, argv, env, 2);
		}
	}
	return (0);
}

void	here_doc(char **av, int *hd_fd)
{
	char	*limiter;
	char	*line;
	char	*input_s;

	limiter = ft_strjoin(av[2], "\n");
	line = get_next_line(0);
	input_s = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	ft_strlcpy(input_s, line, ft_strlen(line));
	input_s = ft_strjoin(input_s, "\n");
	while (ft_strncmp(line, limiter, ft_strlen(av[2])))
	{
		printf("line: %s\t av[2]: %s\n", line, av[2]);
		line = get_next_line(0);
		input_s = ft_strjoin(input_s, line);
	}
	// printf("%s", input_s);
	ft_putstr_fd(input_s, hd_fd[1]);
}
