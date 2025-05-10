/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 06:25:25 by picatrai          #+#    #+#             */
/*   Updated: 2025/05/10 14:35:17 by utilisateur      ###   ########.fr       */
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

char **ft_strdup_2d(char **tab)
{
	char **new;
	
	new = malloc((ft_strlen_2d(tab) + 1) * sizeof(char *));
	if (new == NULL)
		return NULL;
	
	int i = -1;
	while (tab[++i])
	{
		new[i] = ft_strdup(tab[i]);
		if (new[i] == NULL)
		{
			while (--i >= 0)
				free(new[i]);
			free(new);
			return NULL;
		}
	}
	new[i] = NULL;
	return new;
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

int ft_append(char **str, char c)
{
    char	*new;
	int		index;

	new = malloc((ft_strlen(*str) + 2) * sizeof(char));
	if (new == NULL)
		return (free(*str), ERROR_MALLOC);
	index = -1;
	while (*str && (*str)[++index])
		new[index] = (*str)[index];
    new[ft_strlen(*str)] = c;
	new[ft_strlen(*str) + 1] = '\0';
    free(*str);
    *str = new;
	return (SUCCESS);
}

int is_whitespace(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return SUCCESS;
    return (FAILURE);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	index;

	index = 0;
	while (str1[index] && str2[index] && (str1[index] == str2[index]))
		index++;
	return (str1[index] - str2[index]);
}

int ft_join(char **str1, char *str2)
{
    char	*new;
	int		index_1;
    int     index_2;

	new = malloc((ft_strlen(*str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (new == NULL)
		return (free(*str1), free(str2), ERROR_MALLOC);
	index_1 = 0;
	while (*str1 && (*str1)[index_1])
    {
		new[index_1] = (*str1)[index_1];
        index_1++;
    }
    index_2 = 0;
    while (str2 && str2[index_2])
    {
        new[index_1 + index_2] = str2[index_2];
        index_2++;
    }
	new[ft_strlen(*str1) + ft_strlen(str2)] = '\0';
    free(*str1);
    free(str2);
    *str1 = new;
	return (SUCCESS);
}

// on free pas la deuxieme
int ft_join_spe(char **str1, char *str2)
{
    char	*new;
	int		index_1;
    int     index_2;

	new = malloc((ft_strlen(*str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (new == NULL)
		return (free(*str1), ERROR_MALLOC);
	index_1 = 0;
	while (*str1 && (*str1)[index_1])
    {
		new[index_1] = (*str1)[index_1];
        index_1++;
    }
    index_2 = 0;
    while (str2 && str2[index_2])
    {
        new[index_1 + index_2] = str2[index_2];
        index_2++;
    }
	new[ft_strlen(*str1) + ft_strlen(str2)] = '\0';
    free(*str1);
    *str1 = new;
	return (SUCCESS);
}

int	ft_count_itoa(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int ft_itoa(char **str, int nbr)
{
	char	*itoa;
	int		len;
	long	tmp_nbr;

	len = ft_count_itoa(nbr);
	tmp_nbr = nbr;
	itoa = (char *)malloc((len + 1) * sizeof(char));
	if (itoa == NULL)
		return (ERROR_MALLOC);
	itoa[len] = '\0';
	if (nbr < 0)
		tmp_nbr *= -1;
	while (len > 0)
	{
		itoa[len - 1] = (tmp_nbr % 10) + '0';
		tmp_nbr /= 10;
		len--;
	}
	if (nbr < 0)
	    itoa[0] = '-';
    *str = itoa;
	return (SUCCESS);
}


//0 quand on trouve pas et 1 quand on trouve
int	ft_occ(char *str, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			return 1;
		index++;
	}
	return (0);
}

void change_exit_status(int *exit_status, int new_exit)
{
	*exit_status = new_exit;
}