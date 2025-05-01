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
		return (0);
	index = 0;
	while (str[index])
	{
		if (str[index] != ' ' && (str[index] < 9 || str[index] > 13))
			return (1);
		index++;
	}
	return (0);
}

int ft_parsing(char *input, t_data *data)
{
    t_token *token;

    token = NULL;

    if (is_input_only_whitespace(input))
        add_history(input);
    else
        return SUCCESS;


    if (ft_tokenisation(input, &token) != SUCCESS)
        return FAILURE;

    t_token_print(token, 1, 1);

    t_token_free(&token);
    
    

    return 0;
}