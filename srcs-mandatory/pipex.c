/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:39:39 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/06 00:30:59 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cleanup(t_pipex *pipex, int *p)
{
	if (pipex->file_in >= 0)
		close(pipex->file_in);
	if (pipex->file_out >= 0)
		close(pipex->file_out);
	if (p[P_READ] >= 0)
		close(p[P_READ]);
	if (p[P_WRITE] >= 0)
		close(p[P_WRITE]);
	ft_free_matrix((void **)pipex->path);
}

static void	wait_for_everyone(t_pipex *pipex)
{
	waitpid(pipex->clon[0], NULL, 0);
	waitpid(pipex->clon[1], NULL, 0);
}

static void	spawn_clones_to_work(t_pipex *px, char **av)
{
	int		p[2];

	if (pipe(p) < 0)
	{
		ft_free_matrix((void **)px->path);
		close(px->file_in);
		close(px->file_out);
		exit_error("Pipex", "pipe creation failed", 3);
	}
	px->clon[0] = exec_takes_inputfile(px, av[2], p);
	px->clon[1] = exec_writes_to_outfile(px, av[px->ac - 2], p);
	wait_for_everyone(px);
	cleanup(px, p);
}

static void	setup(t_pipex *pipex, int ac, char **av, char **env)
{
	open_files(pipex, ac, av);
	pipex->ac = ac;
	pipex->vars = env;
	pipex->path = create_path_env(env);
	pipex->clon[0] = 0;
	pipex->clon[1] = 0;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (!av || !av[1] || !env)
		exit_error("Pipex", "Invalid or non-sufficient arguments.", 1);
	if (ac != 5)
		exit_error("Pipex", "incorrect number of arguments", 1);
	setup(&pipex, ac, av, env);
	spawn_clones_to_work(&pipex, av);
	return (0);
}
