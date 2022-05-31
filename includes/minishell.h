/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:01:13 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/31 16:21:31 by cjulienn         ###   ########.fr       */
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
#define	REDIR_ARG		6
#define CMD				7
#define	ARG				8

#define	S_QUOTES		1
#define D_QUOTES		2

typedef struct s_shell
{
	int				i;
	size_t			item_length;
	int				exit_status;
	char			**env;
	char			**paths;
	char			*user_input;
	int				fd_in;
	int				fd_out;
	int				nb_cmds;
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
}					t_token;

typedef struct s_seq
{
	char			*cmd_with_args;
	char			**fd_redirs;
}					t_seq;

/* BUILTINS */

int			built_in_cd(t_shell *shell, char **cmd_args);
int			built_in_echo(t_shell *shell, char **cmd_args);
int			built_in_env(t_shell *shell, char **cmd_args);
int			built_in_exit(t_shell *shell, char **cmd_args);
int 		built_in_export(t_shell *shell, char **cmd_args);
int			built_in_pwd(t_shell *shell, char **cmd_args);
int 		built_in_unset(t_shell *shell, char **cmd_args);

/* ENV */

/*envdup.c*/
char		**envdup(char **envp, int pass);
/* paths.c */
char		**recup_paths(t_shell *shell);

/* EXEC */

/* exec_cmd.c*/
void		cmd_exec(t_shell *shell, char **cmd_args, t_token *token);
/* exec_errors.c */
void		display_cmd_not_found(char **cmd_args, char **paths);
void		handle_access_denied(char *path_with_cmd,
	t_shell *shell, char **cmd_args);
int			is_path_functionnal(char *path_with_cmd,
	t_shell *shell, char **cmd_args);
/* exec_path_cmd.c */
void		path_cmd_exec(t_shell *shell, char **cmd_args);

/* FREE */

/* free_child.c */

/* free_parent.c */
void		free_case_err(t_shell *shell, t_token *token);
void		free_problem_str_arr(char **split, int i);
void		free_split(char **split);

/* MINISHELL */

/* process_tokens.c */
void		process_tokens(t_token *token, t_shell *shell);

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
char		*isolate_item(char *user_input, t_shell *shell, t_token *token);

/* REDIRS */

/* fd_redirs.c */
void		operate_redir(t_shell *shell, int type,
	char *path, t_token *token);
/* pipes_redirs_cmds.c */
void		pipes_redirs_cmd(t_shell *shell, t_token *token, int iter);
/* pipes.c */
void		pipes_activation(t_shell *shell, int num_pipes, t_token *token);
void		close_all_pipes(t_shell *shell, int num_pipes);
void		redirect_to_pipe(t_shell *shell, int iter);

/* STRUCTS */

/* init_structs.c */
void		reset_shell_struct(t_shell *shell);
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
/* triple_join.c */
char		*ft_triple_join(const char *s1, const char *s2, const char *s3);

/* DEBUG */

/* debug_utils.c */
void		display_every_token(t_token *token);
void		inspect_char_arr(char **arr);

#endif
