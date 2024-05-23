/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyuela <mhoyuela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:27:05 by mhoyuela          #+#    #+#             */
/*   Updated: 2024/05/22 13:28:17 by mhoyuela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	if (s3 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = (char)s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = (char)s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	char			*t;
	unsigned char	r;

	r = (char)c;
	t = (char *)s;
	i = 0;
	if (r == 0)
		return (&t[ft_strlen(s)]);
	while (t[i] != '\0')
	{
		if (t[i] == r)
		{
			return (&t[i]);
		}
		i++;
	}
	if (r == '\0' || c == 1024)
		return (&t[i]);
	return (NULL);
}
