/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:52:47 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/10 13:08:08 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_check_option_valid_echo(char *arg)
{
    int i = 0;
    if (arg[i] != '-' || arg[1] == '\0')
        return FAILURE;
    while (arg[++i])
    {
        if (arg[i] != 'n')
            return FAILURE;
    }
    return SUCCESS;
}

int bultin_echo(t_data *data, char **args)
{
    int i = 0;//on skip echo
    int find_option = 0;
    
    while (args[++i])
    {
        if (ft_check_option_valid_echo(args[i]) == SUCCESS)
        {
            find_option = 1;
        }
        else
            break;
    }
    while (args[i])
    {
        if (args[i + 1] == NULL)
            printf("%s", args[i]);
        else
            printf("%s ", args[i]);
        i++;
    }
    if (find_option == 0)
        printf("\n");
    return change_exit_status(&data->exit_status, 0), SUCCESS;
}

