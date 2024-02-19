/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_improved_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:14:16 by xriera-c          #+#    #+#             */
/*   Updated: 2024/02/19 12:28:59 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

}
static char	*get_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (ft_substr(s, 0, i));
}

char	**ft_split(char const *s, char c, char d)
{
	char	**arr;
	int		j;

	if (!s)
		return (0);
	arr = malloc(sizeof(char *) * (

}
