/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:39:39 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/09 19:48:54 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	process_cleanup(t_pipex *pipex, int *p, char *av, int errno)
{
	ft_free_matrix((void **)pipex->path);
	pipex->path = NULL;
	close(pipex->file_in);
	close(pipex->file_out);
	if (p)
	{
		close(p[P_READ]);
		close(p[P_WRITE]);
	}
	if (errno == 3)
		exit_error("Pipex", "failure at pipe creation.", 3);
	if (errno == 4)
		exit_error("Pipex", "failure at cloning stage.", 4);
	if (errno == 5)
		exit_error("Pipex", "failure at redirecting file descriptors.", 5);
	if (errno == 6)
		exit_error(av, "Cannot be executed.", 6);
}

int	prep_and_exec_cmd(char *command_to_prep, char **path_env, char **env)
{
	char	**sliced_cmd;
	char	*cmd_path;

	if (!*command_to_prep || !command_to_prep)
		return (0);
	sliced_cmd = command_split(command_to_prep);
	if (!sliced_cmd)
		return (0);
	cmd_path = get_valid_path_for_cmd(sliced_cmd[0], path_env);
	if (!cmd_path || execve(cmd_path, sliced_cmd, env) == -1)
	{
		free(cmd_path);
		cmd_path = NULL;
		ft_free_matrix((void **)sliced_cmd);
		sliced_cmd = NULL;
	}
	return (0);
}

pid_t	exec_takes_inputfile(t_pipex *pipex, char *av, int *p)
{
	pid_t	clon;

	clon = fork();
	if (clon < 0)
		call_error(NULL, NULL);
	if (clon == 0)
	{
		dup2(pipex->file_in, STDIN_FILENO);
		dup2(p[P_WRITE], STDOUT_FILENO);
		close(p[P_READ]);
		close(p[P_WRITE]);
		if (!prep_and_exec_cmd(av, pipex->path, pipex->vars))
			process_cleanup(pipex, p, av, 6);
	}
	return (clon);
}

pid_t	exec_writes_to_outfile(t_pipex *pipex, char *av, int *p)
{
	pid_t	clon;

	clon = fork();
	if (clon < 0)
		call_error(NULL, NULL);
	if (clon == 0)
	{
		dup2(p[P_READ], STDIN_FILENO);
		dup2(pipex->file_out, STDOUT_FILENO);
		close(p[P_WRITE]);
		close(p[P_READ]);
		if (!prep_and_exec_cmd(av, pipex->path, pipex->vars))
			process_cleanup(pipex, p, av, 6);
	}
	close(p[P_READ]);
	close(p[P_WRITE]);
	return (clon);
}
