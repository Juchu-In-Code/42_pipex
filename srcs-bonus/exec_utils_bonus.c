/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:39:39 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/09 19:16:04 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	process_cleanup(t_pipex *pipex, int *p, char *av, int errno)
{
	ft_free_matrix((void **)pipex->path);
	close(pipex->file_in);
	close(pipex->file_out);
	free(pipex->clon);
	pipex->clon = NULL;
	if (pipex->heredoc)
		unlink(".heredoc");
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

static int	prep_and_exec_cmd(char *command_to_prep, t_pipex *pipex)
{
	char	**sliced_cmd;
	char	*cmd_path;

	if (!*command_to_prep || !command_to_prep)
		return (0);
	sliced_cmd = command_split(command_to_prep);
	if (!sliced_cmd)
		return (0);
	cmd_path = get_valid_path_for_cmd(sliced_cmd[0], pipex->path);
	if (!cmd_path || execve(cmd_path, sliced_cmd, pipex->vars) == -1)
	{
		free(cmd_path);
		cmd_path = NULL;
		ft_free_matrix((void **)sliced_cmd);
		sliced_cmd = NULL;
	}
	return (0);
}

pid_t	exec_through_pipes_and_forks(t_pipex *pipex, char *av)
{
	pid_t	clon;
	int		p[2];

	if (pipe(p) < 0)
		process_cleanup(pipex, p, NULL, 3);
	clon = fork();
	if (clon < 0)
		process_cleanup(pipex, p, NULL, 4);
	if (clon == 0)
	{
		if (dup2(pipex->file_in, STDIN_FILENO) < 0
			|| dup2(p[P_WRITE], STDOUT_FILENO) < 0)
			process_cleanup(pipex, p, NULL, 5);
		close(p[P_READ]);
		close(p[P_WRITE]);
		close(pipex->file_in);
		if (!prep_and_exec_cmd(av, pipex))
			process_cleanup(pipex, p, av, 6);
	}
	if (pipex->heredoc)
		unlink(".heredoc");
	close(p[P_WRITE]);
	close(pipex->file_in);
	pipex->file_in = p[P_READ];
	return (clon);
}

pid_t	exec_writes_to_outfile(t_pipex *pipex, char *av)
{
	pid_t	clon;

	clon = fork();
	if (clon < 0)
		process_cleanup(pipex, NULL, NULL, 4);
	if (clon == 0)
	{
		if (dup2(pipex->file_in, STDIN_FILENO) < 0
			|| dup2(pipex->file_out, STDOUT_FILENO) < 0)
			process_cleanup(pipex, NULL, NULL, 5);
		close(pipex->file_in);
		close(pipex->file_out);
		if (!prep_and_exec_cmd(av, pipex))
			process_cleanup(pipex, NULL, av, 6);
	}
	close(pipex->file_in);
	close(pipex->file_out);
	return (clon);
}
