/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:29:48 by ahajji            #+#    #+#             */
/*   Updated: 2023/06/19 20:15:45 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define HEREDOC 1
# define READ 2
# define CREATE 3
# define APPEND 4
# define SUCCESS 0
# define ERROR -1

// EXIT CODES
# define FILE_NOT_FOUND 1
# define CMD_NOT_FOUND 127
# define PERMISSION_ERR 126

/********************************************************************/
/*					 struct has linked list of envp 					*/
/********************************************************************/

typedef struct s_general_info
{
	int		proc_running;
	int		hrdc_state;
	int		hrdc_quotes;
	int		hrdc_exit;
	pid_t	hrdc_child;
}	t_general_info;

t_general_info				g_info;

typedef struct s_list
{
	char				*var;
	char				*value;
	int					valid;
	int					valid2;
	struct s_list		*next;
}						t_list;

/********************************************************************/
/*					struct has linked list of lexer 					*/
/********************************************************************/

/********************************************************************/
/*					struct has linked list of lexer 					*/
/********************************************************************/

typedef struct s_listLex
{
	char				*content;
	int					len;
	char				type;
	char				state;
	struct s_listLex	*prev;
	struct s_listLex	*next;
}						t_listLex;

/********************************************************************/
/*					 struct has linked list of envp 					*/
/********************************************************************/

typedef struct s_minishell
{
	t_list				**head;
	t_listLex			*headlex;
	char				*ptr_input;
	int					i;
	int					pguistvar;
	int					pguist;
	int					valid;
	int					valid2;
	int					valid3;
	int					valid4;
	int					valid5;
	int					begnext;
	int					begprev;
	int					j;
	int					count;
}						t_minishell;

/********************************************************************/
/*					 struct has to nassim         					*/
/********************************************************************/

typedef struct s_file
{
	char				*name;
	int					mode;
	struct s_file		*next;
}						t_file;

typedef struct s_cmd
{
	char				*path;
	char				*cmd;
	char				**args;
	char				**env;
	int					pipe;
	int					in;
	int					out;
	t_file				*file;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_shell
{
	int					exit_status;
	char				*curr_dir;
	char				*path;
	char				**env;
	t_list				**var;
	t_cmd				*cmds;
}						t_shell;

int						ft_strlen(const char *s);
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
void					printEnvp(t_list *head);
t_list					*lst_new(char *en);
t_list					*ft_lstlast(t_list *head);
void					ft_lstadd_back(t_list **head, t_list *new_list);
void					newlist_and_add(t_list **head, char **en);
void					history(char *ptr_input);
int						my_prompt(t_minishell *data, t_listLex **headLex,
							t_list **head);
t_listLex				*lst_last_lex(t_listLex *last);
void					free_list(t_list **head);
char					*ft_strdup(const char *s1);
void					lexer(t_minishell *data, t_listLex **headLex);
t_listLex				*lst_new_lex(char *ptr, int state);
t_listLex				*lst_last_lex(t_listLex *last);
void					add_back_front(t_listLex **haedLex,
							t_listLex *new_list);
void					newlst_add_front_back(char *part_input,
							t_listLex **headLex, int state);
int						return_type(char *ptr, int state);
int						return_state(char *ptr, int state);
void					print_content(t_listLex *headLex);
int						check_syntax(t_minishell *data, t_listLex **headLex,
							t_shell *shell);
void					expand_variable(t_listLex **headLex, t_list **head,
							t_minishell *data, t_shell shell);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strjoin(char *s1, char *s2);
int						organiz_comands(t_listLex **headLex, t_minishell *data,
							t_cmd **data_na, t_shell *shell);
t_cmd					*lst_new_comand(void);
t_cmd					*lst_last_comand(t_cmd *last);
void					add_back_front_comand(t_cmd **haedLex, t_cmd *new_list);
void					newlst_add_front_back_comand(t_cmd **headLex);
void					newlst_add_front_back_file(t_file **headLex, char *ptr,
							int mode);
void					add_back_front_file(t_file **haedLex, t_file *new_list);
t_file					*lst_last_file(t_file *last);
t_file					*lst_new_file(char *ptr, int mode);
char					*ft_strjoin2(char *s1, char *s2);
char					*get_value_var(t_list *head, char *ptr, char state,
							t_minishell *data);
char					**get_arre_envs(t_list *head);
char					*ft_itoa(int n);
int						my_export(t_shell *shell, int mode);
void					add_to_istvar(t_list **head, char *tmp);
char					*get_var(t_list *head, char *var);
void					*ft_calloc(size_t count, size_t size);
int						print_env(t_shell *shell);

int						my_unset(t_shell *shell);
void					skip_stb_two(char **ptr2, int *j, char *ptr);
void					skip_stb_one(char **ptr2, int *j, char *ptr, int *i);
void					skip_stb_three(char **ptr2, int *j, char *ptr, int i);
char					*skip_sp_tb(char *ptr, t_minishell *data);
char					*get_value_var(t_list *head, char *ptr, char state,
							t_minishell *data);
void					update_ptr_input_two(t_minishell *data, int *i);
void					update_ptr_input(t_minishell *data);
int						len_word_doblex(int i, t_minishell *data);
void					if_doble_cot(t_minishell *data, int *i,
							t_listLex **headLex);
void					else_doble_cot(t_minishell *data, int *i,
							t_listLex **headLex);
void					expand_variable_two(t_listLex *tmp, char **ptr,
							t_shell shell);
void					expand_variable_three(t_listLex *tmp, int *valid);
void					expand_variable_for(t_listLex *tmp, t_minishell *data);
void					expand_variable_five(t_listLex *tmp, char **ptr);
void					dobule_cot_ptr(t_minishell *data, t_listLex **headLex,
							int *i);
int						len_sengle_cot(t_minishell *data, int i);
void					sengle_cot_ptr(t_minishell *data, t_listLex **headLex,
							int *i);
int						len_word_lex(int i, t_minishell *data);
int						get_var_gen_two(t_minishell *data, int *i, char **ptr);
int						check_and_return(t_minishell *data, int i);
void					get_var_gen_three(t_minishell *data, int *i,
							char **ptr);
void					get_var_gen(t_minishell *data, t_listLex **headLex,
							int *i);
void					general_ptr_two(t_minishell *data, char **ptr, int *i,
							int *j);
void					general_ptr(t_minishell *data, t_listLex **headLex,
							int *i);
int						check_ptri_d(t_minishell *data, int i);
int						check_ptri_si(t_minishell *data, int i);
void					lexer_if(t_listLex **headLex);
void					lexer_else_if(t_listLex **headLex);
void					lexer_else_if_two(t_listLex **headLex);
void					lexer_else_if_three(t_listLex **headLex);
void					lexer_else_if_for(t_minishell *data,
							t_listLex **headLex, int *i);
void					lexer_else_if_five(t_minishell *data,
							t_listLex **headLex, int *i);
void					lexer_else_if_six(t_listLex **headLex);
void					lexer_else_if_seven(t_listLex **headLex);
void					lexer_else_if_eight(t_listLex **headLex, int *i);
void					lexer_else_if_nine(t_listLex **headLex, int *i);
void					lexer_else_if_ten(t_listLex **headLex, int *i);
int						check_if_exist(t_list *var, char *arg);
int						update_value_var(t_list **var, char *arg, char *ar0);
int						check_var(char *arg);
void					rmove_var_top(t_list **var, t_list **tmp);
void					rmove_var_last(t_list **tmp2, t_list **tmp);
void					rmove_var_behind(t_list **tmp, t_list **tmp3,
							t_list **tmp2);
void					rmove_var(t_list **var, char *arg);
int						print_export(t_shell *shell);
void					add_export_exist(t_shell *shell, char **arr, int i);
int						check_spaces(char *ptr_input);
void					history(char *ptr_input);
char					*get_var(t_list *head, char *var);
void					int_struct_shell(t_shell *shell, t_list **head);
void					free_command2(t_cmd *command);
void					free_command(t_cmd *command);
void					free_headlex(t_listLex **headLex);
int						leng_args(t_listLex *tmp);
int						check_beguist(char state, char *ptr, t_listLex *headLex,
							t_shell *shell);
int						organiz_dobl_singif_one_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_null_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_null(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_two_one_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_two_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_two_null_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_two_null(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_singif_two(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_dobl_sing(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_else_one_one_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_else_one_one(t_listLex **headLex,
							t_minishell *data, char **ptr, t_shell *shell);
int						organiz_else_one(t_listLex **headLex, t_minishell *data,
							char **ptr, t_shell *shell);
int						organiz_else_two(t_listLex **headLex, t_minishell *data,
							char **ptr, t_shell *shell);
int						organiz_else(t_listLex **headLex, t_minishell *data,
							char **ptr, t_shell *shell);
int						len_list(t_list *head);
char					**get_arre_envs(t_list *head);
void					organiz_comandvalid2(t_cmd *tmp2, char **ptr,
							t_minishell *data);
void					organiz_comandvalid3(t_cmd *tmp2, char **ptr,
							t_minishell *data);
void					organiz_comandvalid4(t_cmd *tmp2, char **ptr,
							t_minishell *data);
void					organiz_comandvalid5(t_cmd *tmp2, char **ptr,
							t_minishell *data, t_listLex	*tmp);
void					organiz_comandvalid(t_cmd *tmp2, char **ptr,
							t_minishell *data);
char					**copy_arr_envs(char **ptr);
void					int_struct_inmbg(t_minishell *data, char **ptr);
void					organiz_comand_f(char **ptr, t_cmd *tmp2,
							t_minishell *data, t_listLex	*tmp);
void					organiz_comand_if_two(t_listLex *tmp,
							t_minishell *data);
void					int_struct_comand(t_listLex **headLex, t_cmd **command,
							t_listLex **tmp, t_cmd **tmp2);
int						check_syntax_pipe_two_two(t_minishell *data,
							t_listLex *headLex, int *valid3, int *valid2);
void					check_syntax_pipe_two(int *valid3, t_minishell *data,
							int *valid2, t_listLex **headLex);
int						check_syntax_pipe_three(t_shell *shell, int *valid3,
							int *valid, int *valid2);
int						check_syntax_pipe(t_minishell *data, t_listLex *headLex,
							t_shell *shell);
void					check_syntax_redirction_two(t_listLex *headLex,
							char *ch, int *valid3, int *valid2);
int						check_syntax_redirction_three(int *valid3, int *valid2,
							char *ch, t_shell *shell);
int						check_syntax_redirction(t_listLex *headLex,
							t_shell *shell);
int						check_equal(char *arg);
void					lexer_else_if_tab(t_listLex	**headLex);

// Execution

int						check_if_exec(char *path);
int						get_cmd_path(t_cmd *cmd, char *path_variable);
int						handle_cmd(t_shell *shell);
int						exec_pipes(t_shell *shell);
int						child_process(t_shell *shell);
int						single_cmd(t_shell *shell);

// builtins

int						is_parent_builtin(t_cmd *cmd);
int						is_child_builtin(t_cmd *cmd);
int						exec_parent_builtin(t_shell *shell);
int						exec_child_builtin(t_shell *shell);
int						cd(t_shell *shell);
int						echo(char **args);
int						pwd(t_shell *shell);
int						ft_exit(t_shell *shell);

// general utils

t_list					*get_node(t_list *list, char *val);
void					update_env(t_shell *shell, char *path);
void					sig_handler(int signum);
void					ft_putstr_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
int						get_exit_status(int exit_status);

// libft utils
void					ft_putchar_fd(char c, int fd);
char					*my_strjoin(char const *s1, char const *s2);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char					*ft_strcpy(char *dest, char *source);
char					*ft_strcat(char *dest, char *source);
char					*ft_strchr2(const char *s, int c);
int						valid_number(char *arr);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(char *nb);

// IO redirections
void					rl_replace_line(const char *str, int mode);
void					reinit_global(t_general_info *info);
int						handle_input(t_shell *shell, char *input,
							int *fds, char *delim);
int						init_heredoc(t_shell *shell, t_file *file);
int						init_streams(t_shell *shell);
void					dup_redir(t_cmd *cmd, int *fds, int in_pipe);
void					close_streams(t_cmd *cmd);

// exit utils
void					free_shell_struct(t_shell *shell);
void					free_str_array(char **arr);
void					all_free(t_shell *shell, t_cmd **command,
							t_listLex **headLex, char **ptr_input);

#endif