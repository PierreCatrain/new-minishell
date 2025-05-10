/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:34:56 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/10 12:07:01 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_maj_pwd(t_data *data)
{
    char *tmp;
    char path[1024];//mettre path max todo

    tmp = NULL;
    if (getcwd(path, 1024) == NULL)
        return change_exit_status(&data->exit_status, 0), SUCCESS;// pas sur du return todo
    
    
    while (data->env->prev)
        data->env = data->env->prev;
    while (data->env)
    {
        if (match_env("PWD", data->env) == SUCCESS)
        {
            tmp = ft_strdup(&(data->env->str[4]));
            if (tmp == NULL)
                return (ERROR_MALLOC);
            free(data->env->str);
            data->env->str = NULL;
            if (ft_join_spe(&(data->env->str), "PWD=") != SUCCESS)
                return ERROR_MALLOC;
            if (ft_join_spe(&(data->env->str), path) != SUCCESS)
                return ERROR_MALLOC;
        }
        if (data->env->next)
            data->env = data->env->next;
        else
            break;
    }
    while (data->env->prev)
        data->env = data->env->prev;
    while (data->env)
    {
        if (match_env("OLDPWD", data->env) == SUCCESS)
        {
            free(data->env->str);
            data->env->str = NULL;
            if (ft_join_spe(&(data->env->str), "OLDPWD=") != SUCCESS)
                return free(tmp), ERROR_MALLOC;
            if (ft_join_spe(&(data->env->str), tmp) != SUCCESS)
                return free(tmp), ERROR_MALLOC;
        }
            
        if (data->env->next)
            data->env = data->env->next;
        else
            break;
    }
    while (data->env->prev)
        data->env = data->env->prev;
    return free(tmp), SUCCESS;
}

int  bultin_cd(t_data *data, char **args)
{
    if (ft_strlen_2d(args) >= 3)
    {
        printf("minishell: cd: trop d'arguments\n");
        return change_exit_status(&data->exit_status, 1), SUCCESS;
    }
    else if (ft_strlen(args[1]) >= 256)
    {
        printf("minishell: cd: %s: Nom de fichier trop long\n", args[1]);
        return change_exit_status(&data->exit_status, 1), SUCCESS;
    }

    if (chdir(args[1]) != 0)
    {
        printf("minishell: cd: %s: Aucun fichier de ce nom\n", args[1]);
        return change_exit_status(&data->exit_status, 1), SUCCESS;
    }
    else if (ft_maj_pwd(data) != SUCCESS)
        return change_exit_status(&data->exit_status, 1), SUCCESS;

    return change_exit_status(&data->exit_status, 0), SUCCESS;
}
