/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:46:40 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/10 14:43:02 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_world(char const *s, char sep)
{
	int	flag;
	int	count;

	if (!s)
		return (0);
	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s != sep && flag == 0)
		{
			count++;
			flag = 1;
		}
		else if (*s == sep)
			flag = 0;
		s++;
	}
	return (count);
}

char	*dup_word(char const *s, int start, int end)
{
	char	*str;
	int		i;

	str = malloc((end - start) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char *s, char c)
{
	char		**tab;
	int			start_word;
	int			j;
	int			i;

	tab = malloc(sizeof(char *) * (count_world(s, c) + 1));
	if (!tab || !s)
		return (NULL);
	i = -1;
	j = 0;
	start_word = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && start_word < 0)
			start_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start_word >= 0)
		{
			tab[j++] = dup_word(s, start_word, i);
			if (tab[j -1] == NULL)
				return (free_2d(tab), NULL);
			start_word = -1;
		}
	}
	tab[j] = 0;
	return (tab);
}