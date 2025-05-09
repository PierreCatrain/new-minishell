/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:51:49 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/09 19:10:09 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int bultin_pwd(t_data *data)
{
    char str[1024];//mettre path max todo

    if (getcwd(str, 1024) == NULL)
        return change_exit_status(&data->exit_status, 1), FAILURE;

    printf("%s\n", str);
    return change_exit_status(&data->exit_status, 0), SUCCESS;
}