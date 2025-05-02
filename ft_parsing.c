/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 09:06:06 by picatrai          #+#    #+#             */
/*   Updated: 2025-05-01 09:06:06 by picatrai         ###   ########.fr       */
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

int ft_parsing(char *input, t_data *data)
{
    t_token *token;

    token = NULL;

    if (is_input_only_whitespace(input) == FAILURE)
        add_history(input);
    else
        return SUCCESS;


    if (check_quotes_closes(input))
    {
        ft_putstr_fd("minishell: syntax error with open quotes\n", 2);
        return FAILURE;
    }

    // on fait les tokens
    if (make_token(input, &token) != SUCCESS)
        return (t_token_free(&token), FAILURE);

    // printf("juste apres make token\n");
    // t_token_print(token, 1, 1);
    
    // on isole les meta caracteres
    if (isolate_meta_cara(&token) != SUCCESS)
        return (t_token_free(&token), FAILURE);
    // printf("juste apres isolate meta cara\n");
    // t_token_print(token, 1, 1);

    // expand
    if (expand(&token, data) != SUCCESS)
        return (t_token_free(&token), FAILURE);
    printf("juste apres expand\n");
        t_token_print(token, 1, 1);



    // grammaire

    // on fait notre liste chainee

    // t_token_free(&token);
    
    

    return 0;
}