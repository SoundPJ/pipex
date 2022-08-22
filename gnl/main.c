#include "get_next_line.h"
#include "libft.h"

int	main(int ac, char **av)
{
	char			*limiter;
	char			*line; 
	char			*input_s;

	limiter = ft_strjoin(av[2], "\n");
	line = get_next_line(0);
	input_s = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	ft_strlcpy(input_s, line, ft_strlen(line));
	input_s = ft_strjoin(input_s, "\n");
	while (ft_strncmp(line, av[2], ft_strlen(av[2])))
	{
		line = get_next_line(0);
		input_s = ft_strjoin(input_s, line);
	}
	
	printf("%s", input_s);
	return (0);
}
