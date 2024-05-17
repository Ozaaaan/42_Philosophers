/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:19:58 by ozdemir           #+#    #+#             */
/*   Updated: 2024/01/03 14:38:41 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strchr_gnl(char *s)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

void	ft_rest(char *buffer)
{
	int	i;
	int	j;
	int	indice;

	j = 0;
	i = 0;
	indice = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[j])
		j++;
	while (indice < j - i)
	{
		buffer[indice] = buffer[indice + i];
		indice++;
	}
	buffer[indice] = '\0';
}

int	ft_len(char *s, int j)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	if (j == 1)
		c = '\n';
	while (s && s[i] && s[i] != c)
		i++;
	if (c == '\n' && s && s[i] && s[i] == '\n')
		i++;
	return (i);
}

char	*test(char *s1, char *dest)
{
	free(s1);
	if (dest)
	{
		if (dest[0] == '\0')
		{
			free(dest);
			dest = NULL;
		}
	}
	return (dest);
}

char	*ft_join(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	dest = malloc(sizeof(char) * ((ft_len(s1, 1) + ft_len(s2, 0)) + 1));
	if (dest)
	{
		while (s1 && s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2 && s2[j] && s2[j] != '\n')
		{
			dest[i + j] = s2[j];
			j++;
		}
		dest[i + j] = '\n';
		if (s2[j] && s2[j] == '\n')
			j++;
		dest[i + j] = '\0';
	}
	return (test(s1, dest));
}
