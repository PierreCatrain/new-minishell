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

// en fonction de ce que l'on veut montrer (1 pour juste str // 2 pour str + quotes // 3 pour str quotes grammaire)
void	t_token_print(t_token *token, int fd, int mode)
{
	while (token->prev != NULL)
		token = token->prev;
	while (token)
	{
        printf("|%s|\n", token->str);
        if (mode >= 3)
            printf("|||%d\n", token->grammaire);
		token = token->next;
	}
}