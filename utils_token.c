/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 09:14:19 by picatrai          #+#    #+#             */
/*   Updated: 2025-05-01 09:14:19 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token	*t_token_new(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->str = NULL;
	new->grammaire = UNDEFINED;
	return (new);
}

t_token	*t_token_last(t_token *ls)
{
    if (!ls)
        return (NULL);
	while (ls->next != NULL)
		ls = ls->next;
	return (ls);
}

int	t_token_add_back(t_token **ls, t_token *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*ls == NULL)
	{
		*ls = new;
		return (SUCCESS);
	}
	new->prev = t_token_last(*ls);
	t_token_last(*ls)->next = new;
	return (SUCCESS);
}

void t_token_free(t_token **token)
{
    t_token	*tmp;

	if (*token == NULL)
		return ;
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
	while (*token != NULL)
	{
		if ((*token)->str != NULL)
			free((*token)->str);
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
}

char *ft_trad_grammaire(int grammaire)
{
	char *trad[] = {
        "UNDEFINED",
        "CMD",
        "ARG",
		"INFLE_TEXT",
        "OUTFILE_TEXT",
        "APPEND_TEXT",
        "HEREDOC_TEXT",
        "INFILE",
        "OUTFILE",
        "APPEND",
        "HEREDOC",
        "PIPE"
    };
	return trad[grammaire];
	// if (grammaire == 0)
	// 	return "UNDEFINED";
	// else if (grammaire == 1)
	// 	return "CMD";
	// else if (grammaire == 2)
	// 	return "ARG";
	// else if (grammaire == 3)
	// 	return "INFILE";
	// else if (grammaire == 4)
	// 	return "OUTFILE";
	// else if (grammaire == 5)
	// 	return "HEREDOC";
	// else if (grammaire == 6)
	// 	return "APPEND";
	// else if (grammaire == 7)
	// 	return "INFLE_TEXT";
	// else if (grammaire == 8)
	// 	return "OUTFILE_TEXT";
	// else if (grammaire == 9)
	// 	return "HEREDOC_TEXT";
	// else if (grammaire == 10)
	// 	return "APPEND_TEXT";
	// else if (grammaire == 11)
	// 	return "PIPE";
}

// en fonction de ce que l'on veut montrer (1 pour juste str // 2 pour str + grammire)
void	t_token_print(t_token *token, int fd, int mode)
{
	while (token->prev != NULL)
		token = token->prev;
	while (token)
	{
		if (mode == 1)
        	printf("|%s|\n", token->str);
		else
		printf("|%s|		%s\n", token->str, ft_trad_grammaire(token->grammaire));
        if (mode >= 3)
            printf("|||%d\n", token->grammaire);
		token = token->next;
	}
}

int	ft_strlen_2d(char **str)
{
	int	index;

	if (str == NULL)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

void	free_2d(char **str)
{
	int	index;

	if (str == NULL)
		return ;
	index = -1;
	while (str[++index])
		free(str[index]);
	free(str);
}

int ft_join_2d(char ***tab, char *str)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(*tab) + 2) * sizeof(char *));
	if (new == NULL)
		return (free_2d(*tab), free(str), ERROR_MALLOC);
	index = -1;
	while (*tab && (*tab)[++index])
		new[index] = (*tab)[index];
	new[ft_strlen_2d(*tab)] = str;
	new[ft_strlen_2d(*tab) + 1] = NULL;
	free(*tab);
	*tab = new;
	return (SUCCESS);
}


// en cas de probleme on free pas str et on dup str plutot que de juste prendre son address
int ft_join_2d_spe(char ***tab, char *str)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(*tab) + 2) * sizeof(char *));
	if (new == NULL)
		return (free_2d(*tab), ERROR_MALLOC);
	index = -1;
	while (*tab && (*tab)[++index])
		new[index] = (*tab)[index];
	new[ft_strlen_2d(*tab)] = ft_strdup(str);
	if (new[ft_strlen_2d(*tab)] == NULL)
		return (free_2d(*tab), ERROR_MALLOC);
	new[ft_strlen_2d(*tab) + 1] = NULL;
	free(*tab);
	*tab = new;
	return (SUCCESS);
}