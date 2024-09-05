/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyuela <mhoyuela@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-22 13:23:02 by mhoyuela          #+#    #+#             */
/*   Updated: 2024/05/27 16:03:54 by mhoyuela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buffer_update(char *buffer)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	ptr = malloc((ft_strlen(buffer) - i + 1) * (sizeof(char)));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
	{
		ptr[j++] = buffer[i++];
	}
	ptr[j] = '\0';
	free(buffer);
	return (ptr);
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read_fd(int fd, char *buffer)
{
	char	*ptr;
	int		bytes;
	char	*tmp;

	bytes = 1;
	ptr = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!ptr)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && (bytes != 0))
	{
		bytes = read(fd, ptr, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(ptr);
			return (NULL);
		}
		ptr[bytes] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(buffer, ptr);
		free(tmp);
	}
	free(ptr);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	if (read(fd, 0, 0) < 0)
	{
		if (buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	if (buffer == NULL)
	{
		buffer = malloc(1 * sizeof(char));
		buffer[0] = '\0';
	}
	buffer = ft_read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = buffer_update(buffer);
	return (line);
}

int main(int argc, char *argv[])
{
    int     fd;
    char    *line;
    int     num_lines = 7;

	(void)argc;
	(void)argv;
    fd = 4;
    if (fd == -1)
    {
        printf("%d\n", fd);
        write(1, "Error File\n", 11);
		return (0);
    }
    while (num_lines)
    {
        line = get_next_line(fd);
        printf("Linea_%d: %s\n", 7 - num_lines, line);
		free(line);
        num_lines--;
    }
    return (0);
}
