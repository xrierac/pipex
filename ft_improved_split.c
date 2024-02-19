/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:14:16 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/19 16:22:37 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static char	**free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

static int	get_number_words(char const *s, char c, char d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			if (*s == d && ft_strchr(s + 1, d) != 0)
				j = 1;
			while (j == 1)
			{
				s++;
				if (*s == d)
					j = 0;
			}
			i++;
			j++;
		}
		if (*s == c && j != 0)
			j = 0;
		s++;
		}
	return (i);
}

static char *get_quote(char const *s, char d)
{
	int	i;

	i = 0;
	s++;
	while (s[i] !d && s[i])
		i++;
	return (ft_substr(s, 0, i));
}

static char	*get_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (ft_substr(s, 0, i));
}

char	**ft_split_v2(char const *s, char c, char d)
{
	char	**arr;
	int		j;

	if (!s)
		return (0);
	arr = malloc(sizeof(char *) * (get_number_words(s, c, d) + 1));
	if (!arr)
		return (0);
	j = -1;
	while (*s)
	{
		if (*s == d && ft_strchr(s + 1, d) != 0)
		{
			arr[j++] = get_quote(s, d);
			if (arr[j] == 0)
				return (free_memory(arr));
			s = s + 1 + ft_strlen(arr[j]);
		}
		else if (*s == c)
			s++;
		else
		{
			arr[j++] = get_word(s, c);
			if (arr[j] == 0)
				return (free_memory(arr));
			s = s + ft_strlen(arr[j]);
		}
	}
	arr[j++] = 0;
	return (arr);
}
