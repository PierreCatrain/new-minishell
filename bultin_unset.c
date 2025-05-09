/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:39:04 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/09 17:54:05 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int match_env(char *str1, t_env *env)
{
    int i = 0;

    while (str1[i] && env->str[i] && str1[i] == env->str[i])
        i++;
    if (env->str[i] == '=' || (env->is_define == 0 && ft_strlen(str1) <= ft_strlen(env->str)))
        return SUCCESS;
    return FAILURE;
}

int bultin_unset(t_data *data, char **args)
{
    int i = 0;
    if (data->env == NULL)
        return SUCCESS;
    while (args[++i])
    {
        while (data->env->prev)
            data->env = data->env->prev;
        while (data->env)
        {
            if (match_env(args[i], data->env) == SUCCESS)
            {
                if (data->env->prev)
                    data->env->prev->next = data->env->next;
                if (data->env->next)
                    data->env->next->prev = data->env->prev;
                t_env *tmp;
                
                tmp = data->env;
                if (data->env->prev)
                {
                    while (data->env->prev)
                        data->env = data->env->prev;
                }
                else
                    data->env = data->env->next;
                free(tmp->str);
                free(tmp);
                break;
            }
            
            if (data->env->next == NULL)
                break;
            else
                data->env = data->env->next;
        }
    }
    while (data->env->prev)
        data->env = data->env->prev;
    return SUCCESS;
}