/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 10:46:36 by picatrai          #+#    #+#             */
/*   Updated: 2025-05-02 10:46:36 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_get_pid(char **pid)
{
    int len;
    char buffer[256];
    int fd;

    fd = open("/proc/self/stat", O_RDONLY);
    if (fd == -1)
        return (ERROR_FILE);

    len = read(fd, buffer, sizeof(buffer) - 1);
    if (len <= 0)
        return (close(fd), ERROR_FILE);

    buffer[len] = '\0';
    close(fd);
    *pid = ft_strdup(buffer);
    if (*pid == NULL)
        return FAILURE;
    return SUCCESS;
}


int is_a_cara_expand_limiter(char c)
{
    if (c == ' ' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return FAILURE;
    return SUCCESS;
}

int ft_extract_for_expand(char **expand, char *str)
{
    int i = -1;
    while (str[++i] && is_a_cara_expand_limiter(str[i]) == FAILURE)
    {
        if (ft_append(expand, str[i]) != SUCCESS)
            return (ERROR_MALLOC);
    }
    return SUCCESS;
}

int ft_get_env(char **res, char *to_find, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(to_find, env->str) == '\0' - '=' && env->str[ft_strlen(to_find)] == '=')
        {
            *res = ft_strdup(&(env->str[ft_strlen(to_find) + 1]));
            if (*res == NULL)
                return FAILURE;
        }

        if (env->next != NULL)
            env = env->next;
        else
            break;
    }
}

int expand(t_token **token, t_data *data)
{
    while (*token)
    {
        char *new;
        int i = -1;
        int singles = -1;
        int doubles = -1;

        new = NULL;

        while ((*token)->str[++i])
        {
            if ((*token)->str[i] == '\'' && doubles == -1)
                singles *= -1;
            else if ((*token)->str[i] == '"' && singles == -1)
                doubles *= -1;
            else if ((*token)->str[i] == '$' && (*token)->str[i + 1] == '$' && singles == -1)
            {
                char *pid;

                pid = NULL;
                if (ft_get_pid(&pid) != SUCCESS)
                    return (free(new), FAILURE);
                if (ft_join(&new, pid) != SUCCESS)
                    return ERROR_MALLOC;
                i++;
            }
            else if ((*token)->str[i] == '$' && (*token)->str[i + 1] == '?' && singles == -1)
            {
                char *exit_status;

                exit_status = NULL;
                if (ft_itoa(&exit_status, data->exit_status) != SUCCESS)
                    return (free(new), FAILURE);
                if (ft_join(&new, exit_status) != SUCCESS)
                    return ERROR_MALLOC;
                i++;
            }
            else if ((*token)->str[i] == '$' && (*token)->str[i + 1] != '\0' && is_a_cara_expand_limiter((*token)->str[i + 1]) == FAILURE && singles == -1)
            {
                char *expand;
                char *res;

                expand = NULL;
                if (ft_extract_for_expand(&expand, &((*token)->str[i + 1])) != SUCCESS)
                    return (free(new), FAILURE);
                i += ft_strlen(expand);
                res = NULL;
                if (ft_get_env(&res, expand, data->env) != SUCCESS)
                    return (free(new), free(expand), FAILURE);
                free(expand);
                if (ft_join(&new, res) != SUCCESS)
                    return ERROR_MALLOC;
            }
            else
            {
                if (ft_append(&new, (*token)->str[i]) != SUCCESS)
                    return (ERROR_MALLOC);
            }
        }
        // free((*token)->str);
        (*token)->str = new;


        
        
        
        if ((*token)->next != NULL)
            *token = (*token)->next;
        else
            break;

    }
    while ((*token)->prev != NULL)
        *token = (*token)->prev;
}