/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:35:08 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/09 14:59:45 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	cleanup(t_pipex *pipex)
{
	free(pipex->clon);
	ft_free_matrix((void **)pipex->path);
}

static void	wait_for_everyone(t_pipex *pipex, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
		waitpid(pipex->clon[i++], NULL, 0);
}

static void	spawn_clones_to_work(t_pipex *px, char **av)
{
	int		cmd_count;
	int		i;

	i = -1;
	cmd_count = px->ac - 3 - px->heredoc;
	px->clon = ft_calloc(cmd_count, sizeof(int));
	while (++i < cmd_count - 1)
		px->clon[i] = exec_through_pipes_and_forks(px, av[2 + px->heredoc + i]);
	px->clon[i] = exec_writes_to_outfile(px, av[px->ac - 2]);
	wait_for_everyone(px, cmd_count);
	cleanup(px);
}

static void	setup(t_pipex *pipex, int ac, char **av, char **env)
{
	open_files(pipex, ac, av);
	pipex->ac = ac;
	pipex->vars = env;
	pipex->path = create_path_env(env);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (!av || !av[1] || !env)
		exit_error("Pipex", "Invalid or non-sufficient arguments.", 0);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		pipex.heredoc = 1;
	else
		pipex.heredoc = 0;
	if (ac < 5 || (pipex.heredoc && ac < 6))
		exit_error("Pipex", "incorrect number of arguments", 1);
	if (pipex.heredoc && (!av[2] || !av[2][0]))
		exit_error("Pipex", "incorrect here_doc delimiter", 8);
	setup(&pipex, ac, av, env);
	spawn_clones_to_work(&pipex, av);
	return (0);
}
