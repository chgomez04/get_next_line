/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:45:41 by chgomez           #+#    #+#             */
/*   Updated: 2025/07/23 19:44:00 by chgomez          ###   ########.fr       */
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
			return (free(cup_buffer), free(basin_buffer), NULL);
		cup_buffer[bytes_read] = '\0';
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (basin_buffer == NULL)
			return (free(cup_buffer), NULL);
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
	static char	*basin_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (basin_buffer == NULL)
	{
		basin_buffer = ft_calloc(1, sizeof(char));
		if (basin_buffer == NULL)
			return (NULL);
	}
	if (ft_strchr(basin_buffer, '\n') == NULL)
		basin_buffer = read_from_file(basin_buffer, fd);
	if (basin_buffer == NULL)
		return (NULL);
	line = extract_line(basin_buffer);
	basin_buffer = obtain_remaining(basin_buffer);
	return (line);
}
