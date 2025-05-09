/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:51:49 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/09 17:00:48 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int bultin_pwd(void)
{
    char str[1024];//mettre path max todo

    if (getcwd(str, 1024) == NULL)
        return FAILURE;

    printf("%s\n", str);
    return SUCCESS;
}