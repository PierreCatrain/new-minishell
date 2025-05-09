/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:34:56 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/09 18:42:03 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int  bultin_cd(t_data *data, char **args)
{
    // const char *new_dir = "/tmp";

    if (chdir(args[1]) == 0) {
        printf("Changement de répertoire réussi : \n");
    } else {
        perror("Erreur lors du changement de répertoire");
    }

    return SUCCESS;
}
