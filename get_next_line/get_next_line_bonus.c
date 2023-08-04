/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:50:56 by asenel            #+#    #+#             */
/*   Updated: 2023/07/31 17:12:23 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*del_line(char *left)
{
	char	*buff;
	int		i;

	i = 0;
	while (left[i] && left[i] != '\n')
		i++;
	if (!left[i])
	{
		free(left);
		return (NULL);
	}
	i++;
	buff = ft_substr(left, i, (ft_strlen(left) - i));
	if (!buff)
		return (NULL);
	free(left);
	return (buff);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!(buffer[i]))
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		line = ft_substr(buffer, 0, i + 1);
	else
		line = ft_substr(buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_file(int fd, char *buffer)
{
	char	*buff;
	int		byte;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	byte = 1;
	while (!ft_strchr(buffer, '\n') && byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			free(buffer);
			return (NULL);
		}
		buff[byte] = '\0';
		buffer = ft_strjoin(buffer, buff);
	}
	free(buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	buffer[fd] = del_line(buffer[fd]);
	return (line);
}
