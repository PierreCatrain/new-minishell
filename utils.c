/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 06:25:25 by picatrai          #+#    #+#             */
/*   Updated: 2025-05-01 06:25:25 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strlen(char *str)
{
    int	i = 0;

	if (!str)
        return (0);

    while (str[i])
        i++;
    return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		index;

    if (!str)
        return (NULL);
	new = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	index = -1;
	while (str[++index])
		new[index] = str[index];
	new[index] = '\0';
	return (new);
}

void ft_print_2d_fd(char **str, int fd)
{
    int i = -1;

    if (!str)
        return ;
    while (str[++i])
    {
        write(fd, str[i], ft_strlen(str[i]));
        write(fd, "\n", 1);
    }
}

char *ft_append(char *str, char c)
{
    char	*new;
	int		index;

	new = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (new == NULL)
		return (free(str), NULL);
	index = -1;
	while (str && str[++index])
		new[index] = str[index];
    new[ft_strlen(str)] = c;
	new[ft_strlen(str) + 1] = '\0';
    free(str);
	return (new);
}

int is_whitespace(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return SUCCESS;
    return (FAILURE);
}
