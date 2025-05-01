/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 09:24:45 by picatrai          #+#    #+#             */
/*   Updated: 2025-05-01 09:24:45 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int check_quotes_closes(char *str)
{
    int i = -1;
    int singles = -1;
    int doubles = -1;

    while (str[++i])
    {
        if (str[i] == '\'' && doubles == -1)
            singles *= -1;
        else if (str[i] == '"' && singles == -1)
            doubles *= -1;
    }
    if (singles == 1 || doubles == 1)
        return FAILURE;
    return SUCCESS;
}

// int make_token(char *input, t_token **token)
// {
//     int i = -1;
//     int singles = -1;
//     int doubles = -1;
//     int completing = -1;

//     while (input[++i])
//     {
//         if (input[i] == '\'' && doubles == -1)
//         {
//             singles *= -1;
//             if (completing == 1 && singles == 1 && t_token_add_back(token, t_token_new(SINGLES_QUOTES)) != SUCCESS)
//                 return FAILURE;
//         }
//         else if (input[i] == '"' && singles == -1)
//         {
//             doubles *= -1;
//             if (completing == 1 && doubles == 1 && t_token_add_back(token, t_token_new(DOUBLES_QUOTES)) != SUCCESS)
//                 return FAILURE;
//         }
//         else
//         {
//             if (((i == 0 && is_whitespace(input[i]) == FAILURE) || (i != 0 && is_whitespace(input[i - 1]) == SUCCESS && is_whitespace(input[i]) == FAILURE)) && singles == -1 && doubles == -1)
//             {
//                 if (t_token_add_back(token, t_token_new(NO_QUOTE)) != SUCCESS)
//                     return FAILURE;
//             }

//             if (is_whitespace(input[i]) == FAILURE || singles == 1 || doubles == 1)
//             {
//                 t_token_last(*token)->str = ft_append((t_token_last(*token)->str), input[i]);
//                 if (t_token_last(*token)->str == NULL)
//                     return FAILURE;
                
//                 if (completing == 1)
//             }
//         }
//     }
//     return SUCCESS;
// }


int make_token(char *input, t_token **token)
{
    int i = -1;
    int singles = -1;
    int doubles = -1;
    int completing = -1;

    while (input[++i])
    {
        if (is_whitespace(input[i]) == SUCCESS && (singles == -1 && doubles == -1))
            completing = -1;
        else
        {
            if (completing == -1)
            {
                if (t_token_add_back(token, t_token_new()) != SUCCESS)
                    return FAILURE;   
                completing = 1;
            }
            t_token_last(*token)->str = ft_append((t_token_last(*token)->str), input[i]);
            if (t_token_last(*token)->str == NULL)
                return FAILURE;

            if (input[i] == '\'' && doubles == -1)
                singles *= -1;
            else if (input[i] == '"' && singles == -1)
                doubles *= -1;
        }
    }
    return SUCCESS;
}

int isolate_meta_cara(t_token **token)
{
    while (*token)
    {
        int i = -1;
        int singles = -1;
        int doubles = -1;

        while ((*token)->str[++i])
        {
            if ((*token)->str[i] == '\'' && doubles == -1)
                singles *= -1;
            else if ((*token)->str[i] == '"' && singles == -1)
                doubles *= -1;
        }
        
        *token = (*token)->next;
    }
    while ((*token)->prev != NULL)
        *token = (*token)->prev;

    return SUCCESS;
}

int ft_tokenisation(char *input, t_token **token)
{
    if (check_quotes_closes(input))
    {
        ft_putstr_fd("minishell: syntax error with open quotes\n", 2);
        return FAILURE;
    }

    if (make_token(input, token) != SUCCESS)
        return (t_token_free(token), FAILURE);
    
    if (isolate_meta_cara(token) != SUCCESS)
        return (t_token_free(token), FAILURE);
    
}