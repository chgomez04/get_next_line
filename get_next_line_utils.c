/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgomez <chgomez@student.42barcelona.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:46:34 by chgomez           #+#    #+#             */
/*   Updated: 2025/07/16 17:46:39 by chgomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*p;
	size_t			total_size;
	unsigned char	*aux;
	unsigned char	c;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	total_size = nmemb * size;
	if (nmemb != 0 && (total_size / nmemb) != size)
		return (NULL);
	p = malloc(total_size);
	if (p != NULL)
	{
		aux = p;
		c = 0;
		while (total_size-- > 0)
			*aux++ = c;
	}
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p != '\0')
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	if (*p == '\0' && (char)c == '\0')
		return (p);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (*(s + cont) != '\0')
		cont++;
	return (cont);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	s_join = (char *)malloc(total_len * sizeof(char));
	if (s_join == NULL)
		return (NULL);
	ft_memcpy(s_join, s1, s1_len);
	ft_memcpy(s_join + s1_len, s2, s2_len);
	*(s_join + s1_len + s2_len) = '\0';
	return (s_join);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*t_dest;
	const unsigned char	*t_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	t_dest = dest;
	t_src = src;
	while (n--)
	{
		*t_dest = *t_src;
		t_dest++;
		t_src++;
	}
	return (dest);
}
