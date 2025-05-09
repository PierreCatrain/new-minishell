/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_for_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:12:58 by picatrai          #+#    #+#             */
/*   Updated: 2025/05/09 13:13:48 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int count_heredoc(int **tab, t_token *token)
{
    int count;

    count = 0;
    while (token)
    {
        if (token->grammaire == HEREDOC)
            count++;
        token = token->next;
    }
    if (count == 0)
        return SUCCESS;
    *tab = malloc((count + 1) * sizeof(int));
    if (*tab == NULL)
        return ERROR_MALLOC;
    (*tab)[count] = -3;// delimiteur de fin
    while (--count >= 0)
        (*tab)[count] = -2;// pour pas que ce soit vide
    return SUCCESS;
}

void free_close_tab_heredoc(int *tab)
{
    int i = -1;
    if (tab == NULL)
        return ;

    while (tab[++i] != -3)
    {
        if (tab[i] > 2)
            close(tab[i]);
    }
    free(tab);
}

int ft_get_heredoc_path(char **path)
{
	char	*str_index_path;
	int		index;

	*path = ft_strdup("/tmp/.here_doc");
    if (*path == NULL)
        return ERROR_MALLOC;
	index = 1;
    str_index_path = NULL;
	while (index <= 99999)// faudrait tester de baisser ca pour voir un test de failure todo
	{
		if (ft_itoa(&str_index_path, index) != SUCCESS)
            return (free(*path), ERROR_MALLOC);
		if (ft_join(path, str_index_path) != SUCCESS)
            return (ERROR_MALLOC);
		if (access(*path, 0) != 0)
			return (SUCCESS);
		else
        {
			free(*path);
            *path = ft_strdup("/tmp/.here_doc");
            if (*path == NULL)
                return ERROR_MALLOC;
        }
		index++;
	}
	ft_putstr_fd("minishell: heredoc failed\n", 2);
	return (FAILURE);
}

int	ft_complete_heredoc(int fd, char *lim, t_data *data)
{
	char	*line;
	char	*tmp;

	ft_putstr_fd("> ", 1);
	line = ft_readline_heredoc(lim);// faut le revoir todo
	if (line == NULL)
		return (FAILURE);
    printf("%s,,,,,%s\n", lim, line);
	if (ft_strcmp(line, lim) != 0)
	{
		// if (ft_expand_here_doc(&line, data) != SUCCESS)//todo
        //     return (FAILURE);
		ft_putstr_fd(line, fd);
		free(line);
		if (ft_complete_heredoc(fd, lim, data) != SUCCESS)
			return (FAILURE);
	}
	else
		free(line);
	return (SUCCESS);
}


int ft_heredoc(int **tab, t_token *token, t_data *data)
{
    int index = -1;

    if (count_heredoc(tab, token) != SUCCESS)
        return (ERROR_MALLOC);
    while (token)
    {
        if (token->grammaire == HEREDOC)
        {
            char *path_heredoc;

            path_heredoc = NULL;
            token = token->next;
			if (ft_get_heredoc_path(&path_heredoc) != SUCCESS)
                return (free_close_tab_heredoc(*tab), FAILURE);

            (*tab)[++index] = open(path_heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
            if ((*tab)[index] == -1)
                return (free_close_tab_heredoc(*tab),free(path_heredoc), FAILURE);
            free(path_heredoc);
            if (ft_complete_heredoc((*tab)[index], token->str, data) != SUCCESS)
                return (free_close_tab_heredoc(*tab), FAILURE);
        }
        token = token->next;
    }
    return SUCCESS;
}

int build_for_exec(t_token *token, t_lst_exec **exec, t_data *data)
{
    int *tab_heredoc;
    int index_heredoc;

    tab_heredoc = NULL;
    index_heredoc = 0;
    if (ft_heredoc(&tab_heredoc, token, data) != SUCCESS)
        return FAILURE;
    while (token)
    {
        if (token->grammaire == CMD)
        {
            if (t_lst_exec_add_back(exec, t_lst_exec_new()) != SUCCESS)
                return (t_lst_exec_free_and_close(exec), free_close_tab_heredoc(tab_heredoc), ERROR_MALLOC);
        }
        if (token->grammaire == CMD || token->grammaire == ARG)
        {
            if (ft_join_2d_spe(&(t_lst_exec_last(*exec)->args), token->str) != SUCCESS)
                return (t_lst_exec_free_and_close(exec), free_close_tab_heredoc(tab_heredoc), ERROR_MALLOC);
        }
        else if (token->grammaire == INFILE && t_lst_exec_last(*exec)->fd_in != -1)
        {
            if (t_lst_exec_last(*exec)->fd_in > 2)
                close (t_lst_exec_last(*exec)->fd_in);
            t_lst_exec_last(*exec)->fd_in = open(token->next->str, O_RDONLY);
        }
        else if (token->grammaire == OUTFILE && t_lst_exec_last(*exec)->fd_out != -1)
        {
            if (t_lst_exec_last(*exec)->fd_out > 2)
                close (t_lst_exec_last(*exec)->fd_out);
            t_lst_exec_last(*exec)->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        }
        else if (token->grammaire == APPEND && t_lst_exec_last(*exec)->fd_out != -1)
        {
            if (t_lst_exec_last(*exec)->fd_out > 2)
                close (t_lst_exec_last(*exec)->fd_out);
            t_lst_exec_last(*exec)->fd_out = open(token->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
        }
        else if (token->grammaire == HEREDOC)
        {
            if (t_lst_exec_last(*exec)->fd_in > 2)
                close (t_lst_exec_last(*exec)->fd_in);  
            else if (t_lst_exec_last(*exec)->fd_in == -1)
                close(tab_heredoc[index_heredoc]);
            t_lst_exec_last(*exec)->fd_in = tab_heredoc[index_heredoc];
            tab_heredoc[index_heredoc] = -2;// pour que je les closes pas depuis le tab de heredoc
        }
        else if (token->grammaire == PIPE)
        {
            //je fais ca quand j aurais revu l exec
        }

        token = token->next; 
    }
    free_close_tab_heredoc(tab_heredoc);
    return SUCCESS;
}