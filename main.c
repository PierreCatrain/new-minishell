/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:29:21 by picatrai          #+#    #+#             */
/*   Updated: 2025/05/09 18:22:11 by utilisateur      ###   ########.fr       */
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
        if (t_env_add_back(&data->env, t_env_new(envp[i], 1)) != SUCCESS)
        {
            t_env_free(&data->env);
            return FAILURE;
        }
    }
    return SUCCESS;
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
        if (ft_parsing(input, &data, &exec) != SUCCESS)
            return (t_env_free(&data.env), FAILURE);
        ft_exec(&data, exec);
        t_lst_exec_free_and_close(&exec);
    }


    
    t_env_free(&data.env);
    return (0);
}