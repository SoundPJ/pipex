/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/25 05:10:20 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*here_doc(char **av);

int	main(int argc, char **argv, char **env)
{
	int	hd_fd[2];
	char **paths;

	if (argc < 5)
		ft_err("Not enough arguments\n");
	else
	{
		paths = ft_findpath(env);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			if (pipe(hd_fd) != 0)
			{
				ft_free(paths);
				ft_err("Error at pipe\n");
			}
			ft_putstr_fd(here_doc(argv), hd_fd[1]);
			dup2(hd_fd[0], 0);
			close(hd_fd[0]);
			close(hd_fd[1]);
			ft_pipex(argc, argv, paths, 3);
		}
		else
		{
			dup2(ft_open_file(argv[1], INFILE), 0);
			ft_pipex(argc, argv, paths, 2);
		}
	}
	ft_free(paths);
	return (0);
}

char	*here_doc(char **av)
{
	char	*limiter;
	char	*line;
	char	*input_s;
	char	*tmp_input_s;

	limiter = ft_strjoin(av[2], "\n");
	write(1, ">", 1);
	line = get_next_line(0);
	input_s = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (ft_strncmp(line, limiter, ft_strlen(av[2])))
	{
		write(1, ">", 1);
		tmp_input_s = input_s;
		input_s = ft_strjoin(input_s, line);
		free(tmp_input_s);
		line = get_next_line(0);
	}
	free(limiter);
	return (input_s);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		free(str[i]);
	free(str);
}
