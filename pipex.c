/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/08/18 04:09:10 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		write(1, "Not enough arguments\n", 22);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(ft_open_file(argv[1], INFILE), 0);
		ft_pipex(argc, argv, env, 2);
	}
	return (0);
}
