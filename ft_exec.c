/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:30:22 by utilisateur       #+#    #+#             */
/*   Updated: 2025/05/10 14:51:35 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_get_path(char **path, t_env *env, char *cmd)
{
    char **path_splited;
    
    while (env->prev)
        env = env->prev;
    while (env)
    {
        if (match_env("PATH", env) == SUCCESS && env->is_define == 1)
        {
            path_splited = ft_split(&(env->str[5]), ':');
            if (path_splited == NULL)
                return ERROR_MALLOC;
            int i = -1;
            
            while (path_splited[++i])
            {
                char *joined;

                joined = NULL;
                if (ft_join_spe(&joined, path_splited[i]) != SUCCESS)
                    return (free_2d(path_splited), ERROR_MALLOC);
                if (ft_append(&joined, '/') != SUCCESS)
                    return free_2d(path_splited), ERROR_MALLOC;
                if (ft_join_spe(&joined, cmd) != SUCCESS)
                    return free_2d(path_splited), ERROR_MALLOC;
                if (access(joined, X_OK) == SUCCESS)
                {   
                    *path = joined;
                    return free_2d(path_splited), SUCCESS;
                }
                free(joined);
            }
            free_2d(path_splited);
            if (access(cmd, X_OK) == SUCCESS)
            {
                *path = ft_strdup(cmd);
                if (*path == NULL)
                    return ERROR_MALLOC;
                return SUCCESS;
            }
        }
        if (env->next)
            env = env->next;
        else
            break;
    }
    while (env->prev)
        env = env->prev;
    return ERROR_NOT_IN_PATH;
}

int remake_envp(char ***envp, t_env *env)
{
    while (env->prev)
        env = env->prev;
    while (env)
    {
        if (env->is_define == 1)
        {
            if (ft_join_2d_spe(envp, env->str) != SUCCESS)
                return ERROR_MALLOC;
        }
        if (env->next)
            env = env->next;
        else
            break;
    }
    while (env->prev)
        env = env->prev;
    return SUCCESS;
}

int ft_exec_for_all(t_data *data, t_lst_exec *exec)
{
    char *path;
    int res_get_path;
    path = NULL;
    

    res_get_path = ft_get_path(&path, data->env, exec->args[0]);
    if (res_get_path == ERROR_MALLOC)
        return ERROR_MALLOC;
    else if (res_get_path == ERROR_NOT_IN_PATH)
        data->exit_status = 127;
    else
    {
        char **envp;

        envp = NULL;
        if (remake_envp(&envp, data->env) != SUCCESS)
            return free(path), FAILURE;
        char **argv;
        
        argv = ft_strdup_2d(exec->args);
        if (argv == NULL)
            return free(path), free_2d(envp), ERROR_MALLOC;

        t_lst_exec_free_and_close(&exec);
        t_env_free(&(data->env));

        
        if (execve(path, argv, envp) != SUCCESS)
        {
            free(path);
            free_2d(argv);
            free_2d(envp);
            ft_putstr_fd("minishell: cannot execute binary file", 2);
            exit(126);
        }
    }
        
    return SUCCESS;
}

int ft_child(t_data *data, t_lst_exec *exec)
{
    if (!ft_strcmp(exec->args[0], "env"))
        bultin_env(data);
    else if (!ft_strcmp(exec->args[0], "echo"))
        bultin_echo(data, exec->args);
    else if (!ft_strcmp(exec->args[0], "unset"))
        bultin_unset(data, exec->args);
    else if (!ft_strcmp(exec->args[0], "export"))
        bultin_export(data, exec->args);
    else if (!ft_strcmp(exec->args[0], "pwd"))
        bultin_pwd(data);
    else if (!ft_strcmp(exec->args[0], "cd"))
        bultin_cd(data, exec->args);
    else
        ft_exec_for_all(data, exec);
    
        
    t_lst_exec_free_and_close(&exec);
    t_env_free(&(data->env));
    exit(data->exit_status);

    // return SUCCESS;
}

int ft_exec(t_data *data, t_lst_exec *exec)
{
    int pid;
    int status;
    
    while (exec)
    {
        pid = fork();
        if (pid == -1)
            return FAILURE;
        else if (pid == 0)
        {
            if (ft_child(data, exec) != SUCCESS)
                ;
        }
        // if (ft_child(data, exec) != SUCCESS)
        //         ;
        
        if (exec->next)
            exec = exec->next;
        else
            break;
    }
    waitpid(pid, &status, 0);
    
    data->exit_status = WEXITSTATUS(status);











    
    // if (!ft_strcmp(exec->args[0], "env") && bultin_env(data) != SUCCESS)
    //     return FAILURE;
    // else if (!ft_strcmp(exec->args[0], "echo") && bultin_echo(exec->args) != SUCCESS)
    //     return FAILURE;
    // else if (!ft_strcmp(exec->args[0], "unset") && bultin_unset(data, exec->args) != SUCCESS)
    //     return FAILURE;
    // else if (!ft_strcmp(exec->args[0], "export") && bultin_export(data, exec->args) != SUCCESS)
    //     return FAILURE;
    // else if (!ft_strcmp(exec->args[0], "pwd") && bultin_pwd(data) != SUCCESS)
    //     return FAILURE;
    // else if (!ft_strcmp(exec->args[0], "cd") && bultin_cd(data, exec->args) != SUCCESS)
    //     return FAILURE;
    return SUCCESS;
}