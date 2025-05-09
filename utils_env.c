/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 06:29:39 by picatrai          #+#    #+#             */
/*   Updated: 2025/05/09 17:48:43 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env	*t_env_new(char *str, int is_define)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->is_define = is_define;
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	return (new);
}

t_env	*t_env_last(t_env *ls)
{
    if (!ls)
        return (NULL);
	while (ls->next != NULL)
		ls = ls->next;
	return (ls);
}

int	t_env_add_back(t_env **ls, t_env *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*ls == NULL)
	{
		*ls = new;
		return (SUCCESS);
	}
	new->prev = t_env_last(*ls);
	t_env_last(*ls)->next = new;
	return (SUCCESS);
}

void t_env_free(t_env **env)
{
	t_env	*tmp;

	if (*env == NULL)
		return ;
	while ((*env)->prev != NULL)
		*env = (*env)->prev;
	while (*env != NULL)
	{
		if ((*env)->str != NULL)
			free((*env)->str);
		tmp = *env;
		*env = (*env)->next;
		free(tmp);
	}
}

void	t_env_print(t_env *env, int fd)
{
	while (env && env->prev != NULL)
		env = env->prev;
	while (env)
	{
		ft_putstr_fd(env->str, fd);
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
}