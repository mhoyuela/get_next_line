/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyuela <mhoyuela@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-22 13:23:02 by mhoyuela          #+#    #+#             */
/*   Updated: 2024-05-22 13:23:02 by mhoyuela         ###   ########.fr       */
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
	while (buffer[i])
	{
		ptr[j++] = buffer[i++];
	}
	ptr[j] = '\0';
	free(buffer);
	return (ptr);
}

/*la manera en la que el buffer va a vanzando y se queda en la
ultima linea quye contó es con los dos contadores, mientras la i avanza
la j se reinicializa a 0*/
char	*ft_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
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

/*No puedo hacerlo todo en un bucle poeque si lo hago en uno
no puedo darle el valor exacto de memoria a line, y si meto line
dentro del bucle me va crear memoria para cada vez que entre en el buvle*/
	
char	*ft_read_fd(int fd, char *buffer)
{
	char	*ptr;
	size_t	bytes;
	char	*tmp;

	bytes = 1;
	ptr = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!ptr)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && (bytes != 0))
	{//aqui bytes sera 0 si ha leido todo el archivo
		bytes = read(fd, ptr, BUFFER_SIZE);//EN EL BUCLE LEE DE BUFFER_SIZE EN BUFFER_SIZE
		if ((int)bytes == -1)
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

/*La variable estatica buffer(se llena de BUFFER_SIZE++)se declara en get_next_line
y es estatica para que almacene el valor que devuelve ft_buffer_update, que lo modifica 
cada vez que llamamos a la funcion 
La funcion ft_read_fd recibe la clave de un archivo y llena el buffer con el
contenido de ese archivo. ft_read_fd devuelve el buffer con todo el
contenido del archivo.
La funcion ft_line devuelve una linea recibe buffer. En La funcion ft_buffer_update 
le quito la linea que me devuelve ft_line y actualizo el buffer.
Después en get_next_line devuelvo la linea y el buffer se va acualizando
porque es una variable estatica en get_next_line y tiene el ultimo valor
de ft_buffer_update*/
/*int main()
{
	int fd;
	char *line;
	const char *archivo = "/Documents/RepositoryGet";

	fd = open(archivo, O_RDONLY);
	printf("%s\n", line);
	return (0);
}*/
/*int main(int argc, char *argv[])
{
    int     fd;
    char    *line;
    int     num_lines = 7;

	(void)argc;
    fd = open(argv[1], O_RDONLY);
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
}*/