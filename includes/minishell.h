/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:01:13 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/10 18:21:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

# define MAX_PATH			4096 //assigned the value, since PATH_MAX doesn't work on my distro

# define PIPE				1
# define REDIR_INPUT		2
# define REDIR_OUTPUT		3
# define HERE_DOC			4
# define RO_APPEND			5
# define REDIR_ARG			6
# define CMD				7
# define ARG				8

# define S_QUOTES			1
# define D_QUOTES			2

# define SYNT_ERR_MSG		"minishell: syntax error near unexpected token `"
# define MALLOC_ERR_MSG		"minishell: failure to allocate memory\n"

# define CMD_MISUSAGE		2
# define CMD_ACCESS_DENIED	126
# define CMD_NOT_FOUND		127
# define SYNTAX_ERR			258

# define PARENT				0
# define CHILD				1

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
	int				std_fdin;
	int				std_fdout;
	int				nb_seq;
	int				seq_used;
	int				nb_pipes;
	int				*pipes;
	pid_t			*pids_arr;
	char			*old_pwd;	//added this variable to the struct to keep a track of old pwd for "cd -"
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

/* BUILTINS */

/* bt_cd.c */
int			built_in_cd(t_shell *shell, char **cmd_args);
char		*expand_tilde(char *home, char *arg);
char		*find_pwd(void);
void		assign_old_pwd(t_shell *shell, char *arg,
				int success_code, char *pwd);

/* bt_echo.c */
int			built_in_echo(t_shell *shell, char **cmd_args);

/* bt_env.c */
int			built_in_env(t_shell *shell, char **cmd_args);
void		change_env_var(t_shell **shell, char *var, char *new_var);

/* bt_exit.c */
void		built_in_exit(t_shell *shell, char **cmd_args);
void		free_case_exit(t_shell *shell);

/* bt_export.c */
int			built_in_export(t_shell *shell, char **cmd_args);

/* bt_pwd.c */
int			built_in_pwd(t_shell *shell, char *cmd_args);

/* bt_unset.c */
int			built_in_unset(t_shell *shell, char **cmd_args);

/* ENV */

/*envdup.c*/
char		**envdup(char **envp, int pass);
/* paths.c */
char		**recup_paths(t_shell *shell, char **cmd_args);

/* EXEC */

/* exec_cmd.c*/
int			is_built_in(const char *cmd);
void		cmd_exec(t_shell *shell, char **cmd_args,
				t_token *token, int process);
/* exec_errors.c */
void		display_cmd_not_found(char **cmd_args, char **paths);
void		handle_access_denied(char *path_with_cmd,
				t_shell *shell, char **cmd_args);
int			is_path_functionnal(char *path_with_cmd,
				t_shell *shell, char **cmd_args);
/* exec_path_cmd.c */
void		path_cmd_exec(t_shell *shell, char **cmd_args);

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
int			operate_redir(t_shell *shell, t_token *redir_tk,
				t_token *token, int process);

/* pipes_redirs_cmds.c */
int			is_forking_required(t_token *token, t_shell *shell);
void		pipes_redirs_cmd(t_shell *shell, t_token *token,
				int iter, int process);
/* pipes.c */
void		pipes_activation(t_shell *shell, int num_pipes, t_token *token);
void		close_all_pipes(t_shell *shell, int num_pipes);
void		redirect_to_pipe(t_shell *shell, int iter);

/* UTILS */

/* free.c */
void		clean_child_process(t_shell *shell);
void		free_case_err(t_shell *shell, t_token *token);
void		free_problem_str_arr(char **split, int i);
void		free_split(char **split);
/* init_structs.c */
void		reset_shell_struct(t_shell *shell);
void		init_shell_struct(t_shell *shell, char **envp);
/* syntax_err.c */
int			is_syntax_err(t_token *token, t_shell *shell);
/* token_utils_1.c */
t_token		*token_new(char *item);
t_token		*token_last(t_token *token);
int			token_size(t_token *token);
/* token_utils_2.c */
void		token_delone(t_token **token);
void		token_clear(t_token **token);
void		token_add_front(t_token **token, t_token *new);
void		token_add_back(t_token **token, t_token *new);

/* DEBUG */  // NOT TO BE INCLUDED IN FINAL REPO !!!!!

/* debug_utils.c */
void		display_every_token(t_token *token);
void		inspect_char_arr(char **arr);
void		inspect_exit_code(t_shell *shell);

#endif
