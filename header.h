/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:29:47 by picatrai          #+#    #+#             */
/*   Updated: 2025/05/09 14:10:28 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


enum    status
{
    SUCCESS = 0,
    FAILURE,
    ERROR_CONFIG,
    ERROR_MALLOC,
    ERROR_FILE,
    ERROR_GRAMMAIRE,
    ERROR_ONLY_WHITESPACE,
    ERROR_WITH_QUOTES
};

enum    grammaire
{
    UNDEFINED = 0,
    CMD,
    ARG,
    INFILE_TEXT,
    OUTFILE_TEXT,
    APPEND_TEXT,
    HEREDOC_TEXT,
    INFILE,
    OUTFILE,
    APPEND,
    HEREDOC,
    PIPE,
};

typedef struct s_env
{
	char    *str;
    struct s_env	*prev;
	struct s_env	*next;
} t_env;


typedef struct s_token
{
	char				*str;
	int					grammaire;
	struct s_token		*prev;
	struct s_token		*next;
} t_token;

typedef struct s_lst_exec
{
    char				**args;
	int					fd_in;
	int					fd_out;
	struct s_lst_exec	*prev;
	struct s_lst_exec	*next;
} t_lst_exec;

typedef struct s_data
{
    t_env  *env;
    int exit_status;

} t_data;

int	ft_strlen(char *str);
void    ft_putstr_fd(char *str, int fd);
char	*ft_strdup(char *str);
void ft_print_2d_fd(char **str, int fd);
int ft_append(char **str, char c);
int is_whitespace(char c);
int ft_join_2d(char ***tab, char *str);
int ft_join_2d_spe(char ***tab, char *str);
void	free_2d(char **str);
int	ft_strlen_2d(char **str);
int	ft_strcmp(char *str1, char *str2);
int ft_join(char **str1, char *str2);
int ft_itoa(char **str, int nbr);
char *ft_trad_grammaire(int grammaire);
int	is_input_only_whitespace(char *str);

int ft_duplicate_envp(char **envp, t_data *data);


int	t_env_add_back(t_env **ls, t_env *new);
t_env	*t_env_last(t_env *ls);
t_env	*t_env_new(char *str);
void t_env_free(t_env **env);
void	t_env_print(t_env *env, int fd);

int ft_parsing(char *input, t_data *data, t_lst_exec **exec);

int	t_token_add_back(t_token **ls, t_token *new);
t_token	*t_token_last(t_token *ls);
t_token	*t_token_new(void);
void t_token_free(t_token **token);
void	t_token_print(t_token *token, int fd, int mode);


int make_token(char *input, t_token **token);
int isolate_meta_cara(t_token **token);
int check_quotes_closes(char *str);

int expand(t_token **token, t_data *data);

int grammaire(t_token **token);

int build_for_exec(t_token *token, t_lst_exec **exec, t_data *data);

int	t_lst_exec_add_back(t_lst_exec **ls, t_lst_exec *new);
t_lst_exec	*t_lst_exec_last(t_lst_exec *ls);
t_lst_exec	*t_lst_exec_new(void);
void t_lst_exec_free_and_close(t_lst_exec **exec);
void t_lst_exec_print(t_lst_exec *exec);

char	*ft_readline_heredoc(char *lim);

int ft_exec(t_data *data, t_lst_exec *exec);
int bultin_env(t_data *data);
int bultin_echo(char **args);
int bultin_unset(t_data *data, char **args);

#endif