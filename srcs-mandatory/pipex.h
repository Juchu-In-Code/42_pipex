/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:40:34 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/11 19:29:38 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	char	**vars;
	char	**path;
	ssize_t	file_in;
	ssize_t	file_out;
	pid_t	clon[2];
}	t_pipex;

void	open_files(t_pipex *pipex, int ac, char **av);
void	call_error(char *err, char *msg);
void	exit_error(char *err, char *msg, int exit_code);
char	**create_path_env(char **env);
char	*get_valid_path_for_cmd(char *command, char **path);
pid_t	exec_takes_inputfile(t_pipex *pipex, char *av, int *p);
pid_t	exec_writes_to_outfile(t_pipex *pipex, char *av, int *p);
void	ft_free_matrix(void **mtx);
int		ft_strchr_index(char *str, int char_to_find);
char	**command_split(char const *s);

#endif
