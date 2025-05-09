/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:30:22 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/09 14:17:41 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_exec(t_data *data, t_lst_exec *exec)
{
    if (!ft_strcmp(exec->args[0], "env") && bultin_env(data) != SUCCESS)
        return FAILURE;
    else if (!ft_strcmp(exec->args[0], "echo") && bultin_echo(exec->args) != SUCCESS)
        return FAILURE;
    else if (!ft_strcmp(exec->args[0], "unset") && bultin_unset(data, exec->args) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}