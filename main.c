/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 13:29:21 by picatrai          #+#    #+#             */
/*   Updated: 2025-04-30 13:29:21 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_duplicate_envp(char **envp, t_data *data)
{
    if (!envp)
        return FAILURE;
    data->env = NULL;

    int i = -1;
    while (envp[++i])
    {
        if (t_env_add_back(&data->env, t_env_new(envp[i])) != SUCCESS)
        {
            t_env_free(&data->env);
            return FAILURE;
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    data.exit_status = 0;

    if (argc != 1)
    {
        ft_putstr_fd("minishell: pas besoin d'argument(s)\n", 2);
        return ERROR_CONFIG;
    }
    if (ft_duplicate_envp(envp, &data) == FAILURE)
    {
        ft_putstr_fd("minishell: erreur en copiant l'env\n", 2);
        return FAILURE;
    }

    while (1)
    {
        char *input;
        t_lst_exec *exec;

        exec = NULL;

        input = readline("minishell ~ ");
        if (!input)
			return (ft_putstr_fd("exit\n", 1), t_env_free(&data.env), 0);
        ft_parsing(input, &data, &exec);
    }


    //truc a free
    t_env_free(&data.env);
    return (0);
}