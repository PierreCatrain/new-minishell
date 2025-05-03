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

int	is_input_only_whitespace(char *str)
{
	int	index;

	if (str == NULL)
		return (SUCCESS);
	index = 0;
	while (str[index])
	{
		if (str[index] != ' ' && (str[index] < 9 || str[index] > 13))
			return (FAILURE);
		index++;
	}
	return (SUCCESS);
}

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
            if (ft_append((&(t_token_last(*token)->str)), input[i]) != SUCCESS)
                return ERROR_MALLOC;

            if (input[i] == '\'' && doubles == -1)
                singles *= -1;
            else if (input[i] == '"' && singles == -1)
                doubles *= -1;
        }
    }
    return SUCCESS;
}

int split_meta_cara(char *str, char ***splited)
{
    int i = -1;
    int singles = -1;
    int doubles = -1;
    char *mini_splited;

    mini_splited = NULL;


    while (str[++i])
    {
        if (str[i] == '\'' && doubles == -1)
            singles *= -1;
        else if (str[i] == '"' && singles == -1)
            doubles *= -1;
        
        if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && singles == -1 && doubles == -1)
        {
            if (ft_join_2d(splited, mini_splited) != SUCCESS)
                return ERROR_MALLOC;
            mini_splited = NULL;
            if (str[i] == str[i + 1] && (str[i] == '<' || str[i] == '>'))
            {
                if (ft_append(&mini_splited, str[i]) != SUCCESS)
                    return (free_2d(*splited), ERROR_MALLOC);
                if (ft_append(&mini_splited, str[i + 1]) != SUCCESS)
                    return (free_2d(*splited), ERROR_MALLOC);
                if (ft_join_2d(splited, mini_splited) != SUCCESS)
                    return ERROR_MALLOC;
                mini_splited = NULL;
                i++;
            }
            else
            {
                if (ft_append(&mini_splited, str[i]) != SUCCESS)
                    return (free_2d(*splited), ERROR_MALLOC);
                if (ft_join_2d(splited, mini_splited) != SUCCESS)
                    return ERROR_MALLOC;
                mini_splited = NULL;
            }
        }
        else
        {
            if (ft_append(&mini_splited, str[i]) != SUCCESS)
                return (free_2d(*splited), ERROR_MALLOC);
        }
    }
    if (mini_splited != NULL)
    {
        
        if (ft_join_2d(splited, mini_splited) != SUCCESS)
            return ERROR_MALLOC;

    }
    return (SUCCESS);
}

void build_basic_grammire(t_token *token)
{
    if (ft_strcmp(token->str, "|") == 0)
        token->grammaire = PIPE;
    else if (ft_strcmp(token->str, "<") == 0)
        token->grammaire = INFILE;
    else if (ft_strcmp(token->str, "<<") == 0)
        token->grammaire = HEREDOC;
    else if (ft_strcmp(token->str, ">") == 0)
        token->grammaire = OUTFILE;
    else if (ft_strcmp(token->str, ">>") == 0)
        token->grammaire = APPEND;
}

int insert_token(t_token **token, char **splited)
{
    t_token *prev;
    t_token *next;
    t_token *new;
    t_token *tmp;
    int i = -1;

    prev = (*token)->prev;
    next = (*token)->next;
    new = NULL;

    while (splited[++i])
    {
        if (t_token_add_back(&new, t_token_new()) != SUCCESS)
            return (free_2d(splited), t_token_free(&new), ERROR_MALLOC);
        t_token_last(new)->str = splited[i];
        build_basic_grammire(t_token_last(new));
    }
    tmp = *token;
    *token = t_token_last(new);
    if (prev != NULL)
    {
        prev->next = new;
        new->prev = prev;
    }
    if (next != NULL)
    {
        next->prev = t_token_last(new);
        t_token_last(new)->next = next;
    }

    free(tmp->str);
    free(tmp);
    free(splited);

    return SUCCESS;
}

int isolate_meta_cara(t_token **token)
{
    while (*token)
    {
        char **splited;

        splited = NULL;

        if (split_meta_cara((*token)->str, &splited) != SUCCESS)
            return ERROR_MALLOC;
        if (ft_strlen_2d(splited) == 1)
        {
            build_basic_grammire(*token);
            free_2d(splited);
        }
        else
        {
            if (insert_token(token, splited) != SUCCESS)
                return FAILURE;
        }
        
        
        if ((*token)->next != NULL)
            *token = (*token)->next;
        else
            break;

    }
    while ((*token)->prev != NULL)
        *token = (*token)->prev;

    return SUCCESS;
}