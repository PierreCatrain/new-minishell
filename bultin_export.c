/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:13:47 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/10 13:10:02 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_handle_export(char *str1, t_env *env)
{
    int i = 0;

    while (str1[i] && env->str[i] && str1[i] == env->str[i] && str1[i] != '=')
        i++;
        
    if (str1[i] == '=')
    {
        env->is_define = 1;
        free(env->str);
        env->str = ft_strdup(str1);
        if (env->str == NULL)
            return (ERROR_MALLOC);
        return SUCCESS;
    }
    return FAILURE;
}

int bultin_export(t_data *data, char **args)
{
    int i = 0;
    if (args[1] == NULL)
    {
        while (data->env && data->env->prev != NULL)
            data->env = data->env->prev;
	    while (data->env)
	    {
            printf("declare -x \"%s\"\n", data->env->str);
            if (data->env->next)
		        data->env = data->env->next;
            else
                break;
	    }
        return change_exit_status(&data->exit_status, 0), SUCCESS;
    }
    while (args[++i])
    {
        while (data->env->prev)
            data->env = data->env->prev;
        while (data->env)
        {
            int res = ft_handle_export(args[i], data->env); 
            if (res == ERROR_MALLOC)
                return (change_exit_status(&data->exit_status, 1), ERROR_MALLOC);
            else if (res == SUCCESS)
                break;
            
            
                
            if (data->env->next == NULL)
            {
                if (t_env_add_back(&(data->env), t_env_new(args[i], ft_occ(args[i], '='))) != SUCCESS)
                    return change_exit_status(&data->exit_status, 1), FAILURE;
                break;
            }
            else
                data->env = data->env->next;
        }
    }
    while (data->env->prev)
        data->env = data->env->prev;
                
    return change_exit_status(&data->exit_status, 0), SUCCESS;
}