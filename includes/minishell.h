/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:01:13 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/20 19:39:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PIPE			1
#define REDIR_INPUT		2
#define REDIR_OUTPUT	3
#define HERE_DOC		4
#define RO_APPEND		5
#define CMD				6
#define	ARG				7

#define	S_QUOTES		1
#define D_QUOTES		2

#define	IN_PIPE			1
#define OUT_PIPE		2
#define COMBINED		3

typedef struct s_shell
{
	int				i;
	int				exit_status;
	char			**env;
	char			**paths;
	char			*user_input;
	char			*ui_copy;
	int				fd_in;
	int				fd_out;
	int				nbr_cmds;
	int				cmds_used;
	int				nb_pipes;
	int				*pipes;
	pid_t			*pids_arr;
}					t_shell;

typedef struct s_token
{
	char			*item;
	int				type;
	int				is_quotted;
	int				used;
	struct s_token	*prev;
	struct s_token	*next;
	struct s_shell	*shell;
}					t_token;

typedef struct s_seq
{
	char			*cmd;
	char			**cmds;
	char			*redir;
	char			**redirs;
}
				t_seq;

/* BUILTINS */

int			built_in_cd(char **args, t_shell *shell);
int			built_in_echo(char **args);
int			built_in_env(t_shell *shell);
void		built_in_exit(char **args, t_shell *shell);
int 		built_in_export(t_shell *shell, char **args);
int			built_in_pwd(void);
int 		built_in_unset(t_shell *shell, char **args);

/* ENV */

/*envdup.c*/
char		**envdup(char **envp, int pass);
/* paths.c */
char		**recup_paths(t_shell *shell);

/* EXEC */

/* exec_errors.c */
void		display_cmd_not_found(char **cmd_args, char **paths);
void		handle_access_denied(char *path_with_cmd,
	t_shell *shell, char **cmd_args);
int			is_path_functionnal(char *path_with_cmd,
	t_shell *shell, char **cmd_args);
/* exec_path_cmd.c */
void		path_cmd_exec(t_shell *shell, char **cmd_args);

/* PARSING */

/* expansions.c */
void		expand_env_var(t_token *token);
/* parsing.c */
t_token		*parse_user_input(t_shell *shell);
/* quotes.c */
int			remove_quotes(t_token *token);
int			is_quote_valid(char *item, char sep);
size_t		calc_quote_length(char *str, size_t i);
/* tokenisation.c */
char		*isolate_item(t_shell *shell);

/* STRUCTS */

/* init_structs.c */
void		init_shell_struct(t_shell *shell, char **envp);
/* token_utils_1.c */
t_token		*token_new(char *item);
t_token		*token_last(t_token *token);
int			token_size(t_token *token);
/* token_utils_2.c */
void		token_delone(t_token **token);
void		token_clear(t_token **token);
void		token_add_front(t_token **token, t_token *new);
void		token_add_back(t_token **token, t_token *new);

/* UTILS */

/* free.c */
void		free_three_ptn(void *ptn_1, void *ptn_2, void *ptn_3);
void		free_split(char **split);
void		free_problem_str_arr(char **split, int i);

char		*ft_triple_join(const char *s1, const char *s2, const char *s3);

/* DEBUG */

/* debug_utils.c */

#endif
