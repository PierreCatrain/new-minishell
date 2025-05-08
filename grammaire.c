/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammaire.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-03 10:54:30 by picatrai          #+#    #+#             */
/*   Updated: 2025-05-03 10:54:30 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void ft_grammaire_redirection_text(t_token **token)
{
    while (*token)
    {
        if ((*token)->grammaire == UNDEFINED && (*token)->prev && (*token)->prev->grammaire >= INFILE && (*token)->prev->grammaire <= HEREDOC)
            (*token)->grammaire = (*token)->prev->grammaire - 4;

        if ((*token)->next != NULL)
            *token = (*token)->next;
        else
            break;
    }
    while ((*token)->prev != NULL)
        *token = (*token)->prev;
}

void ft_grammaire_cmd_arg(t_token **token)
{
    while (*token)
    {
        if (((*token)->grammaire == UNDEFINED && (*token)->prev && (*token)->prev->grammaire == PIPE) || ((*token)->grammaire == UNDEFINED && (*token)->prev == NULL))
            (*token)->grammaire = CMD;
        else if ((*token)->grammaire == UNDEFINED)
            (*token)->grammaire = ARG;

        if ((*token)->next != NULL)
            *token = (*token)->next;
        else
            break;
    }
    while ((*token)->prev != NULL)
        *token = (*token)->prev;
}

int ft_grammaire_condition(t_token *token)
{
    while (token)
    {
        if ((token->next && token->grammaire >= INFILE && token->next->grammaire >= INFILE) || (token->grammaire >= INFILE && (token->prev == NULL || token->next == NULL)))
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
            ft_putstr_fd(token->str, 2);
            ft_putstr_fd("'\n", 2);
            return ERROR_GRAMMAIRE;
        }
        token = token->next;
    }
    return SUCCESS;
}

int grammaire(t_token **token)
{
    ft_grammaire_redirection_text(token);
    ft_grammaire_cmd_arg(token);
    if (ft_grammaire_condition(*token) != SUCCESS)
        return ERROR_GRAMMAIRE;
    return SUCCESS;
}