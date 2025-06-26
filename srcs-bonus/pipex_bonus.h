/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:40:34 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/10 19:02:03 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"

# define P_READ 0
# define P_WRITE 1

typedef struct s_pipex
{
	int		ac;
	int		heredoc;
	char	**vars;
	char	**path;
	ssize_t	file_in;
	ssize_t	file_out;
	pid_t	*clon;
}	t_pipex;

void	open_files(t_pipex *pipex, int ac, char **av);
void	call_error(char *err, char *msg);
void	exit_error(char *err, char *msg, int exit_code);

/* path utils */
char	**create_path_env(char **env);
char	*get_valid_path_for_cmd(char *command, char **path);

/* exec utils */
pid_t	exec_through_pipes_and_forks(t_pipex *pipex, char *av);
pid_t	exec_writes_to_outfile(t_pipex *pipex, char *av);

/* general utils*/
void	ft_free_matrix(void **mtx);
int		ft_strchr_index(char *str, int char_to_find);

/* arg utils*/
char	**command_split(char const *s);

#endif
