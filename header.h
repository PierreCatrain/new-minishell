/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-30 13:29:47 by picatrai          #+#    #+#             */
/*   Updated: 2025-04-30 13:29:47 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>


#define SUCCESS 0
#define FAILURE 1



enum    error
{
    ERROR_CONFIG = 2,
    ERROR_MALLOC,
};

enum    quotes_type
{
    NO_QUOTE = 0,
    SINGLES_QUOTES,
    DOUBLES_QUOTES,
};

typedef struct s_env
{
    struct s_env	*prev;
	struct s_env	*next;
	char    *str;
} t_env;


typedef struct s_token
{
	char				*str;
	int					grammaire;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_data
{
    t_env  *env;

} t_data;

int	ft_strlen(char *str);
void    ft_putstr_fd(char *str, int fd);
char	*ft_strdup(char *str);
void ft_print_2d_fd(char **str, int fd);
char *ft_append(char *str, char c);
int is_whitespace(char c);

int ft_duplicate_envp(char **envp, t_data *data);


int	t_env_add_back(t_env **ls, t_env *new);
t_env	*t_env_last(t_env *ls);
t_env	*t_env_new(char *str);
void t_env_free(t_env **env);
void	t_env_print(t_env *env, int fd);

int ft_parsing(char *input, t_data *data);
int ft_tokenisation(char *input, t_token **token);

int	t_token_add_back(t_token **ls, t_token *new);
t_token	*t_token_last(t_token *ls);
t_token	*t_token_new(void);
void t_token_free(t_token **token);
void	t_token_print(t_token *token, int fd, int mode);

#endif