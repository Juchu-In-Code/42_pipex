/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:14:33 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/05 23:37:50 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static ssize_t	open_input_file(char *av)
{
	if (access(av, R_OK) == 0)
		return (open(av, O_RDONLY));
	call_error ("Invalid input file", "file not found or cannot be read from.");
	return (-1);
}

static ssize_t	open_output_file(char *av)
{
	ssize_t	file_output;

	file_output = open(av, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (access(av, W_OK) < 0)
	{
		call_error ("Invalid output file", "cannot be written to.");
		return (-1);
	}
	return (file_output);
}

void	open_files(t_pipex *pipex, int ac, char **av)
{
	pipex->file_in = open_input_file(av[1]);
	pipex->file_out = open_output_file(av[ac - 1]);
	if (pipex->file_in < 0 || pipex->file_out < 0)
	{
		if (pipex->file_in >= 0)
			close(pipex->file_in);
		if (pipex->file_out >= 0)
			close(pipex->file_out);
		exit(1);
	}
}
