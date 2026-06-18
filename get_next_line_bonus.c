/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:42:07 by chgomez           #+#    #+#             */
/*   Updated: 2025/07/23 19:45:05 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

static char	*append_buffer(char *basin_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(basin_buffer, read_buffer);
	free(basin_buffer);
	return (temp);
}

static char	*read_from_file(char *basin_buffer, int fd)
{
	int		bytes_read;
	char	*cup_buffer;

	cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (cup_buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(cup_buffer), NULL);
		cup_buffer[bytes_read] = '\0';
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (ft_strchr(basin_buffer, '\n'))
			break ;
	}
	free(cup_buffer);
	return (basin_buffer);
}

static char	*extract_line(char *basin_buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (basin_buffer[i] == '\0')
		return (NULL);
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
	{
		line[i] = basin_buffer[i];
		i++;
	}
	if (basin_buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*obtain_remaining(char *basin_buffer)
{
	int		i;
	int		n;
	char	*new_basin_buffer;

	i = 0;
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
		i++;
	if (basin_buffer[i] == '\0')
		return (free(basin_buffer), NULL);
	new_basin_buffer = ft_calloc(ft_strlen(basin_buffer) - i + 1, sizeof(char));
	i++;
	n = 0;
	while (basin_buffer[i] != '\0')
		new_basin_buffer[n++] = basin_buffer[i++];
	return (free(basin_buffer), new_basin_buffer);
}

char	*get_next_line(int fd)
{
	static char	*basin_buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (basin_buffer[fd] == NULL)
		basin_buffer[fd] = ft_calloc(1, sizeof(char));
	if (ft_strchr(basin_buffer[fd], '\n') == NULL)
		basin_buffer[fd] = read_from_file(basin_buffer[fd], fd);
	if (basin_buffer[fd] == NULL)
		return (free(basin_buffer[fd]), NULL);
	line = extract_line(basin_buffer[fd]);
	basin_buffer[fd] = obtain_remaining(basin_buffer[fd]);
	return (line);
}
