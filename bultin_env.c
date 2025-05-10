/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_data->env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:36:14 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/09 17:32:20 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int bultin_env(t_data *data)
{
    while (data->env && data->env->prev != NULL)
		data->env = data->env->prev;
	while (data->env)
	{
        if (data->env->is_define == 1)
            printf("%s\n", data->env->str);
		if (data->env->next)
			data->env = data->env->next;
		else
			break;
	}
	while (data->env->prev)
		data->env = data->env->prev;
    return change_exit_status(&data->exit_status, 0), SUCCESS;
}