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

int ft_parsing(char *input, t_data *data, t_lst_exec **exec)
{
    t_token *token;

    token = NULL;

    if (is_input_only_whitespace(input) == FAILURE)
        add_history(input);
    else
        return ERROR_ONLY_WHITESPACE;


    if (check_quotes_closes(input))
    {
        ft_putstr_fd("minishell: syntax error with open quotes\n", 2);
        return ERROR_WITH_QUOTES;
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
    if (expand(&token, data) != SUCCESS)// a voir pour la gestion d erreur selon les droits du fichier /proc/self/stat
        return (t_token_free(&token), FAILURE);
    // printf("juste apres expand\n");
    //     t_token_print(token, 1, 2);



    // grammaire
    if (grammaire(&token) != SUCCESS)
        return (t_token_free(&token), ERROR_GRAMMAIRE);
    // printf("juste apres grammaire\n");
        // t_token_print(token, 1, 2);

    // on fait notre liste chainee
    // a voir comment on gere les erreurs de fichier et les erreur de malloc et de heredoc
    if (build_for_exec(token, exec, data) != SUCCESS)
        return (t_token_free(&token), FAILURE);

    printf("resultat du parsing :\n");        
    t_lst_exec_print(*exec);
    //test on est sur pierre
        
    t_lst_exec_free_and_close(exec);
    t_token_free(&token);
    
    

    return 0;
}