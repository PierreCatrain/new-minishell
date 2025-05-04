/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-03 12:43:58 by picatrai          #+#    #+#             */
/*   Updated: 2025-05-03 12:43:58 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_lst_exec	*t_lst_exec_new(void)
{
	t_lst_exec	*new;

	new = malloc(sizeof(t_lst_exec));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
    new->fd_in = 0;
    new->fd_out = 1;
	new->args = NULL;
	return (new);
}

t_lst_exec	*t_lst_exec_last(t_lst_exec *ls)
{
    if (!ls)
        return (NULL);
	while (ls->next != NULL)
		ls = ls->next;
	return (ls);
}

int	t_lst_exec_add_back(t_lst_exec **ls, t_lst_exec *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*ls == NULL)
	{
		*ls = new;
		return (SUCCESS);
	}
	new->prev = t_lst_exec_last(*ls);
	t_lst_exec_last(*ls)->next = new;
	return (SUCCESS);
}

void t_lst_exec_free_and_close(t_lst_exec **exec)
{
    t_lst_exec	*tmp;

	if (*exec == NULL)
		return ;
	while ((*exec)->prev != NULL)
		*exec = (*exec)->prev;
	while (*exec != NULL)
	{
		if ((*exec)->args != NULL)
			free_2d((*exec)->args);
        if ((*exec)->fd_in > 2)
            close((*exec)->fd_in);
        if ((*exec)->fd_out > 2)
            close((*exec)->fd_out);
		tmp = *exec;
		*exec = (*exec)->next;
		free(tmp);
	}
}

void t_lst_exec_print(t_lst_exec *exec)
{
	while (exec)
	{
		int i = -1;
		while (exec->args[++i])
		{
			printf("%s|", exec->args[i]);
			printf("in:%d|", exec->fd_in);
			printf("out:%d\n", exec->fd_out);
		}
		exec = exec->next;
	}
}